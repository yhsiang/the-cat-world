//------------------------------------------------------------------ prototypes

varargs string file_name(object, int);
string trim(string);

//------------------------------------------------------------------- variables

private nosave mixed null;

//------------------------------------------------------------------- functions

object assert_caller(mixed file) {
    object caller = previous_object(1);

    if (stringp(file)) {
        if (file == file_name(caller, 1)) {
            return caller;
        }
    } else if (objectp(file)) {
        if (file == caller) {
            return caller;
        }
    }

    error("illegal function caller.");
}

//-----------------------------------------------------------------------------

mixed default_value(mixed value, mixed default_value) {
    return value ? value : default_value;
}

//-----------------------------------------------------------------------------

varargs string file_name(object ob, int flag) {
    if (ob) {
        string name = efun::file_name(ob);

        if (flag && clonep(ob)) {
            return name[0..(strsrch(name, '#', -1) - 1)];
        } else {
            return name;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

int is_chinese(string text) {
    if (text) {
        int width = strwidth(text);

        if (width) {
            int words = 0;

            foreach (int code in str_to_arr(text)) {
                if (0x4E00 <= code && code <= 0x9FA5) {
                    ++words;
                } else {
                    break;
                }
            }

            return (words == width) ? words : 0;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

void log_file(string file, string text) {
    int *now = localtime(time());

    text = sprintf("%d-%02d-%02d %02d:%02d:%02d  %s\n",
                   now[LT_YEAR],
                   now[LT_MON] + 1,
                   now[LT_MDAY],
                   now[LT_HOUR],
                   now[LT_MIN],
                   now[LT_SEC],
                   text);

    write_file(LOG_DIR + file, text);
}

//-----------------------------------------------------------------------------

string *split(string text, string delimiter) {
    return text ? explode(text, delimiter) : ({});
}

//-----------------------------------------------------------------------------

varargs string *strip(string *text, mixed comment) {
    if (text) {
        for (int i = sizeof(text) - 1; i >= 0; --i) {
            text[i] = trim(text[i]);

            if (comment && strsrch(text[i], comment) == 0) {
                text[i] = 0;
            }
        }

        text -= ({ 0, "" });
    }

    return text;
}

//-----------------------------------------------------------------------------

string trim(string text) {
    if (strlen(text)) {
        int code = text[0], start = 0;

        while (code == 0x20 || (0x0d >= code && code >= 0x09)) {
            ++start;
            code = text[start];
        }

        if (code) {
            int end = 1;

            code = text[<1];

            while (code == 0x20 || (0x0d >= code && code >= 0x09)) {
                ++end;
                code = text[<end];
            }

            if (start || end > 1) {
                return text[start..<end];
            }
        } else {
            return "";
        }
    }

    return text;
}

//-----------------------------------------------------------------------------

mixed undefined_value() {
    return null;
}

//-----------------------------------------------------------------------------
