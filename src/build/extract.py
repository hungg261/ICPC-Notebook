import os
import re
from pathlib import Path

def get_hash(s):
    s_clean = "".join(s.split())
    h = 14695981039346656037
    for c in s_clean:
        h = h ^ ord(c)
        h = (h * 1099511628211) & 0xFFFFFFFFFFFFFFFF
    return f"{h & 0xFFFFFFFF:08X}"

def run():
    p_lst = r"\\begin\{lstlisting\}((?:\[.*?\])?)(.*?)\\end\{lstlisting\}"
    p_inp = r"\\lstinputlisting\{contents/.*?/codes/([^}]+)\.cpp\}"
    goc = Path(__file__).resolve().parent.parent

    for f in goc.rglob("*.tex"):
        if "codes" in f.parts or "build" in f.parts:
            continue

        txt = f.read_text(encoding="utf-8")
        d_codes = (f.parent / "codes").resolve()
        p_name = f.parent.name
        vld = set()

        for m in re.finditer(p_inp, txt):
            f_name = f"{m.group(1)}.cpp"
            f_cpp = d_codes / f_name
            if f_cpp.exists():
                vld.add(f_name)
                src = f_cpp.read_text(encoding="utf-8")
                if src.startswith("/* Hash:"):
                    lns = src.splitlines()
                    if lns: lns.pop(0)
                    src = "\n".join(lns)
                if src.startswith("\n"): src = src[1:]
                h = get_hash(src)
                f_cpp.write_text(f"/* Hash: {h} */\n{src}", encoding="utf-8")

        m_lst = list(re.finditer(p_lst, txt, re.DOTALL))
        if m_lst:
            moi = ""
            idx = 0
            file_counter = 1
            for m in m_lst:
                cfg = m.group(1).strip()
                src = m.group(2)
                if "[" in cfg:
                    moi += txt[idx : m.end()]
                    idx = m.end()
                    continue
                
                while f"{f.stem}_{file_counter}.cpp" in vld:
                    file_counter += 1
                
                name = f"{f.stem}_{file_counter}.cpp"
                file_counter += 1
                vld.add(name)

                d_codes.mkdir(parents=True, exist_ok=True)
                if src.startswith("\n"): src = src[1:]
                h = get_hash(src)
                (d_codes / name).write_text(f"/* Hash: {h} */\n{src}", encoding="utf-8")

                path_ltx = f"contents/{p_name}/codes/{name}"
                moi += txt[idx : m.start()] + f"\\lstinputlisting{{{path_ltx}}}"
                idx = m.end()
            moi += txt[idx:]
            f.write_text(moi, encoding="utf-8")

        if d_codes.exists():
            for cur in d_codes.glob(f"{f.stem}_*.cpp"):
                if cur.name not in vld:
                    cur.unlink()
            if not any(d_codes.iterdir()):
                d_codes.rmdir()

if __name__ == "__main__":
    run()
