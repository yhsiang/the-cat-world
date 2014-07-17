//------------------------------------------------------------------ prototypes

private int illegal_id(string);
private int illegal_name(string);

//------------------------------------------------------------------- functions

void logon() {
    object who = assert_caller(LOGIN_OB);

    write(read_file(CONFIG_DIR"issue"));
    write("\n您的英文名字：");

    who->input("id");
}

//-----------------------------------------------------------------------------

void logon_time_out() {
    object who = assert_caller(LOGIN_OB);

    if (interactive(who)) {
        write("\n登入程序逾時，自動斷線中……\n");
    }

    destruct(who);
}

//-----------------------------------------------------------------------------

string probe_client_encoding() {
    return "Big5-HKSCS//IGNORE";
}

//-----------------------------------------------------------------------------

void receipt(string property, string value) {
    object who = assert_caller(LOGIN_OB);

    call_other(this_object(), "receipt_" + property, who, trim(value));
}

//--------------------------------------------------------- protected functions

protected void receipt_id(object who, string id) {
    id = lower_case(id);

    if (illegal_id(id)) {
        write("\n您的英文名字：");
        who->input("id");
        return;
    }

    write("您的中文名字：");
    who->set_temp("pending_uid", id);
    who->input("name");
}

//-----------------------------------------------------------------------------

protected void receipt_name(object who, string name) {
    if (illegal_name(name)) {
        write("\n您的中文名字：");
        who->input("name");
        return;
    }

    who->set("name", name);

    remove_call_out(who->query_temp("logon_time_out_handle"));
}

//----------------------------------------------------------- private functions

private int illegal_id(string id) {
    int num = strlen(id);

    if (num < 3 || 12 < num) {
        write("對不起，您的英文名字必須是 3 到 12 個英文字母。\n");
        return 1;
    }

    foreach (num in id) {
        if (num < 'a' || 'z' < num) {
            write("對不起，您的英文名字必須是 3 到 12 個英文字母。\n");
            return 1;
        }
    }

    foreach (object ob in children(LOGIN_OB)) {
        if (interactive(ob) && ob->query_temp("pending_uid") == id) {
            write("對不起，這個英文名字暫時無法使用。\n");
            return 1;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

private int illegal_name(string name) {
    int num = is_chinese(name);

    if (num < 2 || 6 < num) {
        write("對不起，您的中文名字必須是 2 到 6 個中文字。\n");
        return 1;
    }

    return 0;
}

//-----------------------------------------------------------------------------
