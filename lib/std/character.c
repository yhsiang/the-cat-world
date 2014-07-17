//-------------------------------------------------------------------- inherits

inherit F_DBASE;

//------------------------------------------------------------------ prototypes

private int command_hook(object, string);

//------------------------------------------------------------------- variables

private nosave string *paths = ({ "usr" });

//------------------------------------------------------------------- functions

void enable_character() {
    enable_commands();
    add_action((: command_hook, this_object() :), "", 1);
    enable_commands(1);
}

//----------------------------------------------------------- private functions

private int command_hook(object me, string arg) {
    object command;
    string verb = query_verb();

    command = COMMAND_D->find_command(verb, paths);

    if (command && command->main(me, arg)) {
        return 1;
    }

    return CHANNEL_D->do_channel(me, verb, arg);
}

//-----------------------------------------------------------------------------
