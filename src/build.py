import os
import glob
import re

def get_sort_key(name):
    match = re.match(r"^(\d+)", name)
    if match:
        return (0, int(match.group(1)), name)
    return (1, 0, name)

def build_contents():
    with open("src/contents.tex", "w", encoding="utf-8") as f:
        raw_categories = [d for d in os.listdir("src/contents") if os.path.isdir(os.path.join("src/contents", d))]
        categories = sorted(raw_categories, key=get_sort_key)
        
        for category in categories:
            cat_path = os.path.join("src/contents", category)
            
            clean_category = re.sub(r"^\d+_", "", category).replace("_", " ")
            f.write(f"\\section{{{clean_category}}}\n")
            
            raw_tex_files = glob.glob(os.path.join(cat_path, "*.tex"))
            tex_files = sorted(raw_tex_files, key=lambda x: get_sort_key(os.path.basename(x)))
            
            for tex_file in tex_files:
                base_name = os.path.splitext(os.path.basename(tex_file))[0]
                title = re.sub(r"^\d+_", "", base_name).replace("_", " ")
                
                try:
                    with open(tex_file, "r", encoding="utf-8") as tf:
                        first_line = tf.readline().strip()
                        if first_line.startswith("%"):
                            extracted_title = first_line.lstrip("%").strip()
                            if extracted_title:
                                title = extracted_title
                except IOError:
                    pass
                
                clean_path = f"contents/{category}/{os.path.basename(tex_file)}"
                
                f.write(f"\\subsection{{{title}}}\n")
                f.write(f"\\input{{{clean_path}}}\n")

if __name__ == "__main__":
    build_contents()
    os.chdir("src")
