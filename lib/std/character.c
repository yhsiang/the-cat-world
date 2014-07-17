//-------------------------------------------------------------------- inherits

inherit F_DBASE;

//------------------------------------------------------------------ prototypes

private int command_hook(object, string);

//------------------------------------------------------------------- variables

private nosave string *paths = ({});

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

    return command ? command->main(me, arg) : 0;
}

//-----------------------------------------------------------------------------
