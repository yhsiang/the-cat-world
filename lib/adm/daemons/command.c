//------------------------------------------------------------------- variables

private nosave mapping tables = ([]);

private nosave string *paths = ({
    "std",
    "usr",
    "apr",
    "wiz",
    "arch",
    "adm",
});

//------------------------------------------------------------------- functions

object find_command(int privilege, string verb) {
    mapping table;
    object command;
    string path;

    for (int i = privilege; i >= 0; --i) {
        path = paths[i];
        table = tables[path];

        if (!table) {
            string *files = get_dir("/cmds/" + path + "/*.c");

            table = ([]);

            if (files) {
                foreach (string file in files) {
                    table[file[0..<3]] = 0;
                }
            }

            tables[path] = table;
        }

        command = table[verb];

        if (!command) {
            if (undefinedp(command)) {
                continue;
            } else {
                command = load_object("/cmds/" + path + "/" + verb);
                table[verb] = command;
            }
        }

        return command;
    }

    return 0;
}

//-----------------------------------------------------------------------------
