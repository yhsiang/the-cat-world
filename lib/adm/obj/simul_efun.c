//------------------------------------------------------------------ prototypes

string trim(string);

//------------------------------------------------------------------- variables

private nosave mixed null;

//------------------------------------------------------------------- functions

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
