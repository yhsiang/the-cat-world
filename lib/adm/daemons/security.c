
//--------------------------------------------------------------------- defines

#define WIZLIST CONFIG_DIR"wizlist"

//------------------------------------------------------------------- variables

private nosave string *groups = ({
    "(player)",
    "(apprentice)",
    "(wizard)",
    "(arch)",
    "(admin)",
});

private nosave mapping wiz_list = ([]);

//------------------------------------------------------------------- functions

string query_user_group(mixed ob) {
    string group;

    if (objectp(ob)) {
        group = wiz_list[getuid(ob)];
    } else if (stringp(ob)) {
        group = wiz_list[ob];
    }

    return group ? group : "(player)";
}

//-----------------------------------------------------------------------------

int query_user_level(mixed ob) {
    return member_array(query_user_group(ob), groups);
}

//----------------------------------------------------------- private functions

private void create() {
    string id, group;

    foreach (string config in read_config(WIZLIST)) {
        if (sscanf(config, "%s %s", id, group) == 2) {
            wiz_list[id] = group;
        }
    }
}

//-----------------------------------------------------------------------------
