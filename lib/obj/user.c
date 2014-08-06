//-------------------------------------------------------------------- inherits

inherit CHARACTER;
inherit F_SAVE;

//----------------------------------------------------------------- constructor

protected void create() {
    seteuid(0);
}

//------------------------------------------------------------------- functions

int id(string id) {
    return (id == getuid());
}

//-----------------------------------------------------------------------------

string long() {
    return short(1) + "。\n";
}

//-----------------------------------------------------------------------------

varargs string name(int raw) {
    if (!raw) {
        string applied = query_temp("apply/name");

        if (applied) {
            return applied;
        }
    }

    return query("name");
}

//-----------------------------------------------------------------------------

string query_id() {
    return getuid();
}

//-----------------------------------------------------------------------------

string query_save_file() {
    string uid = getuid();

    return (DATA_DIR"user/" + uid[0..0] + "/" + uid);
}

//-----------------------------------------------------------------------------

void setup() {
    seteuid(getuid());
    enable_character();
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

private void receive_message(string class, string message) {
    receive(message);
}

//-----------------------------------------------------------------------------
