import os
import os.path

dirs = os.listdir()
in_files = list(filter(lambda x: x[-1] == 'n', dirs))
out_files = list(filter(lambda x: x[-1] == 't', dirs))
for i, v in enumerate(in_files):
    os.rename(v, f"{i + 1}.in")
for i, v in enumerate(out_files):
    os.rename(v, f"{i + 1}.out")