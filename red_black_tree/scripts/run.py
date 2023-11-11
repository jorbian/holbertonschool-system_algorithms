#!/usr/bin/python3

import json
import sys

from pathlib import Path

manifest = json.loads(Path("file_manifest.json").read_text())

if (len(sys.argv) < 2):
    error_message = "USAGE: {} <SOURCE_FILE>".format(sys.argv[0])
else:
    filename = manifest.get(sys.argv[0])
    error_message = (
        "FILE NOT INCLUDED IN MANIFEST" if (not manifest.get(filename)) else ""
    )
if (error_message):
    print(error_message, file=sys.stderr)
    exit(1)
