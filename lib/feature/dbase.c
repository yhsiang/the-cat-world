//------------------------------------------------------------------ prototypes

#include <dbase.h>

private mapping _find(mapping, string ref, int);
private mixed _query(mapping, string, int);

//------------------------------------------------------------------- variables

private mapping dbase = ([]);
private nosave mapping temp_dbase;
private nosave mixed default_object;

//------------------------------------------------------------------- functions

void add(string path, mixed data) {
    mixed previous = query(path, 1);

    set(path, previous ? (previous + data) : data);
}

//-----------------------------------------------------------------------------

void add_temp(string path, mixed data) {
    mapping db;
    mixed previous;

    if (!temp_dbase) {
        temp_dbase = ([]);
    }

    db = _find(temp_dbase, ref path, 1);
    previous = db[path];
    db[path] = previous ? (previous + data) : data;
}

//-----------------------------------------------------------------------------

void delete(string path) {
    mapping db = _find(dbase, ref path, 0);

    if (db) {
        map_delete(db, path);
    }
}

//-----------------------------------------------------------------------------

void delete_temp(string path) {
    if (temp_dbase) {
        mapping db = _find(temp_dbase, ref path, 0);

        if (db) {
            map_delete(db, path);
        }
    }
}

//-----------------------------------------------------------------------------

varargs mixed query(string path, int raw) {
    mixed data = _query(dbase, path, raw);

    if (undefinedp(data) && default_object) {
        return default_object->query(path, raw);
    }

    return data;
}

//-----------------------------------------------------------------------------

mixed query_default_object() {
    return default_object;
}

//-----------------------------------------------------------------------------

mapping query_entire_dbase() {
    return dbase;
}

//-----------------------------------------------------------------------------

mapping query_entire_temp_dbase() {
    return temp_dbase;
}

//-----------------------------------------------------------------------------

varargs mixed query_temp(string path, int raw) {
    return temp_dbase ? _query(temp_dbase, path, raw) : NULL;
}

//-----------------------------------------------------------------------------

void set(string path, mixed data) {
    mapping db = _find(dbase, ref path, 1);

    db[path] = data;
}

//-----------------------------------------------------------------------------

void set_default_object(mixed ob) {
    default_object = ob;
}

//-----------------------------------------------------------------------------

void set_temp(string path, mixed data) {
    mapping db;

    if (!temp_dbase) {
        temp_dbase = ([]);
    }

    db = _find(temp_dbase, ref path, 1);
    db[path] = data;
}

//----------------------------------------------------------- private functions

private mapping _find(mapping db, string ref path, int flag) {
    int offset = strsrch(path, '/');

    if (offset >= 0) {
        mixed node;
        string name;

        while (1) {
            name = offset ? path[0..(offset - 1)] : "";
            node = db[name];

            if (!mapp(node)) {
                if (flag) {
                    node = ([]);
                    db[name] = node;
                } else {
                    return 0;
                }
            }

            db = node;
            path = path[(offset + 1)..];
            offset = strsrch(path, '/');

            if (offset < 0) {
                break;
            }
        }
    }

    return db;
}

//-----------------------------------------------------------------------------

private mixed _query(mapping db, string path, int raw) {
    db = _find(db, ref path, 0);

    if (db) {
        mixed current = db[path];
        int flag = functionp(current);

        if (!flag || raw) {
            return current;
        } else if (~flag & FP_OWNER_DESTED) {
            return evaluate(current, this_object());
        }
    }

    return NULL;
}

//-----------------------------------------------------------------------------
