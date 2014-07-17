//------------------------------------------------------------------- functions

string creator_file(string filename) {
    string *path = explode(filename, "/");

    switch (path[0]) {
        case "adm":
        case "cmds":
            return ROOT_UID;
    }

    return SYSTEM_UID;
}

//----------------------------------------------------------- private functions

private object connect() {
    return new(LOGIN_OB);
}

//-----------------------------------------------------------------------------

private string *epilog(int load_empty) {
    return read_config(CONFIG_DIR"preload");
}

//-----------------------------------------------------------------------------

private string get_bb_uid() {
    return BACKBONE_UID;
}

//-----------------------------------------------------------------------------

private string get_root_uid() {
    return ROOT_UID;
}

//-----------------------------------------------------------------------------

private void preload(string filename) {
    load_object(filename);
}

//-----------------------------------------------------------------------------

private int valid_seteuid(object ob, string euid) {
    if (euid) {
        string uid = getuid(ob);

        if (uid != euid && uid != ROOT_UID) {
            return 0;
        }
    }

    return 1;
}

//-----------------------------------------------------------------------------
