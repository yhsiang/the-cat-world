//------------------------------------------------------------------- functions

int move(mixed to) {
    object me;

    if (!objectp(to)) {
        if (stringp(to)) {
            to = load_object(to);

            if (!to) {
                return 0;
            }
        } else {
            return 0;
        }
    }

    me = this_object();

    if (to->increase_encumbrance(me)) {
        object from = environment();

        move_object(to);

        if (from) {
            from->decrease_encumbrance(me);
        }

        return 1;
    }

    return 0;
}

//-----------------------------------------------------------------------------
