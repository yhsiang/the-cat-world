//------------------------------------------------------------------ prototypes

private void bind_uid(object, string);
private void enter_world(object, object, int);
private object find_body(string);
private int illegal_id(string);
private int illegal_name(string);
private object make_body(object);

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

protected void receipt_confirm_password(object who, string confirm_password) {
    string password = who->query("password");

    if (password != crypt(confirm_password, password)) {
        write("\n\n您兩次輸入的密碼並不一致，請重新設定一次密碼：");
        who->input("new_password", 1);
        return;
    }

    write("\n");
    enter_world(who, make_body(who), 0);
}

//-----------------------------------------------------------------------------

protected void receipt_id(object who, string id) {
    id = lower_case(id);

    if (illegal_id(id)) {
        write("\n您的英文名字：");
        who->input("id");
        return;
    }

    bind_uid(who, id);

    if (file_size(who->query_save_file() + __SAVE_EXTENSION__) < 1) {
        write("使用 " + id + " 這個英文名字"
              "將會創造一個新的人物，您確定嗎(y/n)？");
        who->set_temp("pending_uid", id);
        who->input("new_user");
    } else if (who->restore()) {
        write("請輸入密碼：");
        who->input("password", 1);
    } else {
        write("您的人物檔案出了一些問題，請通報巫師處理。\n");
        destruct(who);
    }
}

//-----------------------------------------------------------------------------

protected void receipt_name(object who, string name) {
    if (illegal_name(name)) {
        write("\n您的中文名字：");
        who->input("name");
        return;
    }

    write("\n請設定您的密碼：");
    who->set("name", name);
    who->input("new_password", 1);
}

//-----------------------------------------------------------------------------

protected void receipt_new_password(object who, string password) {
    if (strwidth(password) < 5) {
        write("\n\n密碼的長度至少要 5 個字，請重新設定您的密碼：");
        who->input("new_password", 1);
        return;
    }

    write("\n請再輸入一次您的密碼，以確認您沒記錯：");
    who->set("password", crypt(password, 0));
    who->input("confirm_password", 1);
}

//-----------------------------------------------------------------------------

protected void receipt_new_user(object who, string answer) {
    answer = lower_case(answer);

    if (answer == "n") {
        write("\n好吧，那麼請重新輸入您的英文名字：");
        bind_uid(who, master()->creator_file(LOGIN_OB));
        who->delete_temp("pending_uid");
        who->input("id");
        return;
    }

    if (answer != "y") {
        write("使用 " + getuid(who) + " 這個英文名字"
              "將會創造一個新的人物，您確定嗎(y/n)？");
        who->input("new_user");
        return;
    }

    write("\n請您想一個有氣質，有個性，又不會太奇怪的中文名字，特別要提醒"
          "\n您的是， 本 MUD 是一個以古中國與東方為背景的世界，請不要取一"
          "\n些不雅或是容易造成他人困擾的名字，這個名字將代表你的人物，請"
          "\n務必慎重。\n"
          "\n您的中文名字：");
    who->input("name");
}

//-----------------------------------------------------------------------------

protected void receipt_password(object who, string confirm_password) {
    object body;
    string password = who->query("password");

    if (password != crypt(confirm_password, password)) {
        write("\n密碼錯誤！\n");
        destruct(who);
        return;
    }

    write("\n");

    body = find_body(getuid(who));

    if (body) {
        object current = body->query_temp("link_ob");

        if (current) {
            tell_object(body, "\n有人從別處 (" + query_ip_number(who) +
                              ") 連線取代您所控制的人物。\n");
            exec(current, body);
            destruct(current);
        }

        enter_world(who, body, 1);
    } else {
        body = new(USER_OB);

        bind_uid(body, getuid(who));

        if (body->restore()) {
            enter_world(who, body, 0);
        } else {
            write("您的人物檔案出了一些問題，請通報巫師處理。\n");
            destruct(body);
            destruct(who);
        }
    }
}

//----------------------------------------------------------- private functions

private void bind_uid(object ob, string id) {
    seteuid(id);
    export_uid(ob);
    seteuid(getuid());
}

//-----------------------------------------------------------------------------

private void enter_world(object who, object body, int reconnect) {
    string msg;

    who->setup();
    who->set_temp("body_ob", body);
    body->set_temp("link_ob", who);

    exec(body, who);

    if (reconnect) {
        msg = "%s reconnected from %s";
        write("重新連線完畢。\n");
    } else {
        body->setup();
        write(read_file(CONFIG_DIR"motd"));

        if (who->query_temp("pending_uid")) {
            msg = "%s created by %s";
        } else {
            msg = "%s connected from %s";
        }
    }

    remove_call_out(who->query_temp("logon_time_out_handle"));

    log_file("usage", sprintf(msg, getuid(body), query_ip_number(body)));
}

//-----------------------------------------------------------------------------

private object find_body(string uid) {
    object body = find_player(uid);

    if (!body) {
        foreach (object ob in children(USER_OB)) {
            if (getuid(ob) == uid && userp(ob)) {
                return ob;
            }
        }
    }

    return body;
}

//-----------------------------------------------------------------------------

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

private object make_body(object who) {
    object body = new(USER_OB);

    body->set("name", who->query("name"));

    bind_uid(body, getuid(who));

    who->save();
    body->save();

    return body;
}

//-----------------------------------------------------------------------------
