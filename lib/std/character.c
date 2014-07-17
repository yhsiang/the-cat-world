//-------------------------------------------------------------------- inherits

inherit F_DBASE;

//------------------------------------------------------------------ prototypes

private int command_hook(object, int, string);

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
