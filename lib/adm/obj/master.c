//------------------------------------------------------------------- functions

string creator_file(string filename) {
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
