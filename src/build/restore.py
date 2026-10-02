import re
import shutil
from pathlib import Path

def normalize_src(src):
    if src.startswith("\r\n"):
        src = src[2:]
    elif src.startswith("\n") or src.startswith("\r"):
        src = src[1:]
    if src.endswith("\r\n"):
        src = src[:-2]
    elif src.endswith("\n") or src.endswith("\r"):
        src = src[:-1]
    return src

def run():
    p_inp = r"\\lstinputlisting\{contents/.*?/codes/([^}]+)\.h\}"
    goc = Path(__file__).resolve().parent.parent

    tex_by_dir = {}
    for f in goc.rglob("*.tex"):
        if "codes" in f.parts or "build" in f.parts:
            continue
        tex_by_dir.setdefault(f.parent, []).append(f)

    for parent, tex_files in tex_by_dir.items():
        d_codes = (parent / "codes").resolve()

        for f in tex_files:
            txt = f.read_text(encoding="utf-8")
            matches = list(re.finditer(p_inp, txt))
            if not matches:
                continue

            moi = ""
            idx = 0

            for m in matches:
                full_name = m.group(1)
                base_name = full_name.rsplit('_', 1)[0] if '_' in full_name else full_name
                f_cpp = d_codes / f"{full_name}.h"
                
                if not f_cpp.exists() and d_codes.exists():
                    for alt_f in d_codes.glob(f"{base_name}_*.h"):
                        f_cpp = alt_f
                        break

                if f_cpp.exists():
                    src = f_cpp.read_text(encoding="utf-8")
                    if src.startswith("/* Hash:"):
                        lns = src.splitlines()
                        if lns: lns.pop(0)
                        src = "\n".join(lns)
                    src = normalize_src(src)
                    lst_block = f"\\begin{{lstlisting}}\n{src}\n\\end{{lstlisting}}"
                    moi += txt[idx : m.start()] + lst_block
                else:
                    moi += txt[idx : m.end()]
                idx = m.end()

            moi += txt[idx:]
            f.write_text(moi, encoding="utf-8")

        if d_codes.exists() and d_codes.is_dir():
            shutil.rmtree(d_codes)

if __name__ == "__main__":
    run()
