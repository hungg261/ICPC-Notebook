import os
import subprocess

response = input("Do you want to generate? (y/n): ").strip().lower()
if response == 'y':
    original_dir = os.getcwd()
    try:
        os.chdir("src")
        subprocess.run(["latexmk", "-pdf", "-jobname=notebook", "-outdir=..", "main.tex"])
    finally:
        os.chdir(original_dir)
    
    extensions_to_remove = [".aux", ".fdb_latexmk", ".fls", ".log", ".toc"]
    for ext in extensions_to_remove:
        file_path = f"notebook{ext}"
        if os.path.exists(file_path):
            os.remove(file_path)
