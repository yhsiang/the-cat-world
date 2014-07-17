//-------------------------------------------------------------------- inherits

inherit CHARACTER;
inherit F_SAVE;

//----------------------------------------------------------------- constructor

protected void create() {
    seteuid(0);
}

//------------------------------------------------------------------- functions

string query_save_file() {
    string uid = getuid();

    return (DATA_DIR"user/" + uid[0..0] + "/" + uid);
}

//-----------------------------------------------------------------------------

void setup() {
    seteuid(getuid());
}

//----------------------------------------------------------- private functions

private void net_dead() {
    object ob = query_temp("link_ob");

    if (ob) {
        destruct(ob);
    }

    log_file("usage", getuid() + " disconnected");
}

//-----------------------------------------------------------------------------
