//-------------------------------------------------------------------- inherits

inherit F_DBASE;
inherit F_SAVE;

//------------------------------------------------------------------- functions

varargs void input(string property, int flag) {
    assert_caller(LOGIN_D);

    input_to((: call_other, LOGIN_D, "receipt", property :), flag ? 3 : 2);
}

//-----------------------------------------------------------------------------

string query_save_file() {
    string uid = getuid();

    return (DATA_DIR"login/" + uid[0..0] + "/" + uid);
}

//----------------------------------------------------------- private functions

private void logon() {
    function logon_time_out = (: call_other, LOGIN_D, "logon_time_out" :);
    string encoding = LOGIN_D->probe_client_encoding();

    if (encoding) {
        set_encoding(encoding);
    }

    set_temp("logon_time_out_handle", call_out(logon_time_out, 300));

    LOGIN_D->logon();
}

//-----------------------------------------------------------------------------

private void net_dead() {
    destruct();
}

//-----------------------------------------------------------------------------
