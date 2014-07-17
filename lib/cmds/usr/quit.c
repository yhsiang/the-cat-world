//------------------------------------------------------------------- functions

int main(object me, string arg) {
    object ob = me->query_temp("link_ob");

    if (ob) {
        destruct(ob);
    }

    me->save();

    if (interactive(me)) {
        write("歡迎下次再來！\n");
    }

    log_file("usage", getuid(me) + " quitted");

    destruct(me);

    return 1;
}

//-----------------------------------------------------------------------------
