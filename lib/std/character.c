//-------------------------------------------------------------------- inherits

inherit F_DBASE;

//------------------------------------------------------------------ prototypes

varargs string name(int);
string query_id();

private int command_hook(object, int, string);
private string query_short(int);

//------------------------------------------------------------------- functions

void enable_character() {
    int privilege;
    object me = this_object();

    if (userp(me)) {
        privilege = SECURITY_D->query_user_level(me) + 1;

        if (privilege > 1) {
            enable_wizard();
        }
    }

    enable_commands();
    add_action((: command_hook, me, privilege :), "", 1);
    enable_commands(1);
}

//-----------------------------------------------------------------------------

varargs string short(int raw) {
    if (raw) {
        return query_short(1);
    } else {
        string applied = query_temp("apply/short");

        if (!applied) {
            applied = query_short(0);
            set_temp("apply/short", applied);
        }

        return applied;
    }
}

//----------------------------------------------------------- private functions

private int command_hook(object me, int privilege, string arg) {
    object command;
    string verb = query_verb();

    command = COMMAND_D->find_command(privilege, verb);

    if (command && command->main(me, arg)) {
        return 1;
    }

    return CHANNEL_D->do_channel(me, verb, arg);
}

//-----------------------------------------------------------------------------

private string query_short(int raw) {
    string id, name, nickname, title;

    id = query_id();
    name = name(raw);
    nickname = query("nickname");
    title = default_value(query("title"), "");

    if (strlen(nickname)) {
        return title + "「" + nickname + "」" + name + "(" + id + ")";
    } else if (strlen(title)) {
        return title + " " + name + "(" + id + ")";
    } else {
        return name + "(" + id + ")";
    }
}

//-----------------------------------------------------------------------------
