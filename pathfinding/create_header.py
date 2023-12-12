#!/usr/bin/python3

import re

from pathlib import Path

class Header:

    FIND_MACRO_NAME = " ([A-Z1-9_]+)"

    directive_names = ("define", "undef", "include", "ifndef", "endif")
    directive_search = (
        f'{FIND_MACRO_NAME}\s+(\S+).*',
        FIND_MACRO_NAME,
        ' [<|"](.*)[>|"].*',
        FIND_MACRO_NAME,
        FIND_MACRO_NAME
    )
    PP_DIRECTIVES = {
        f'{name}': re.compile(
            f'#{name}{search_patt}$', re.MULTILINE
        ) for (name, search_patt)
            in  zip(directive_names, directive_search)
    }

    NAME_PATTERN = "_{}_H"
    COMMENT = "/* {} */"
    NEEDS_ESCAPED = (chr(42), chr(92), chr(47))
    LINE_ANCHORS = ("ifndef", "define", "endif")

    def __init__(self, *args, **kwargs):
        self.create_new_file(args[0])

    def create_new_file(self, name, code="", file_ext=".h"):

        header_file = Path(name)
        if (header_file.suffix != file_ext):
            header_file = Path(f'{header_file.stem}{file_ext}')

        if header_file.exists():
            raise Exception()
        
        setattr(self, "file_obj", header_file)
        setattr(self, "code", self.generate_code(name, code))

        self.file_obj.write_text(self.code)

    @classmethod
    def add_escape_chars(cls, string, escape=NEEDS_ESCAPED):
        """ADD ESCAPE CHARACTERS TO STRING FOR CREATING REGEX"""
        if (len(escape) == 0):
            return (string)
        else:
            return (
                cls.add_escape_chars(
                    string.replace(
                        escape[0],
                        (chr(92) + escape[0])
                    ),
                    escape[1:]
                )
            )
        
    @classmethod
    def template(cls, name_patt=NAME_PATTERN):
        """DYNAMICALLY GENERATE THE TEMPLATE FOR THE FILE OUTLINE"""
        template_lines = [
            f'#{x} {name_patt}\n' for x in cls.LINE_ANCHORS
        ]
        template_lines[-1] = template_lines[-1].replace(
            name_patt,
            cls.COMMENT.format(
                name_patt
            )
        )
        template_lines.insert(-1, "{}\n")

        return ("".join(template_lines))

    @classmethod
    def generate_code(cls, name, code=""):
        """GENERATES THE NECESSARY C CODE FOR HEADER"""
        details = [name.upper() for x in range(0,3)]
        details.insert(-1, code)

        return (
            cls.template().format(*details)
        )
    
    @classmethod
    def find_subheader_names(cls, file):

        file = Path(file)

        code = file.read_text()

        return (
            re.findall(cls.PP_DIRECTIVES['include'], code
        )
)
    
test_file = Path("/usr/include/endian.h")


print(Header.find_subheader_names(test_file))