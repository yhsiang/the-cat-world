//------------------------------------------------------------------- variables

private nosave mapping tables = ([]);

//------------------------------------------------------------------- functions

object find_command(string verb, string *paths) {
    mapping table;
    object command;

    foreach (string path in paths) {
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
