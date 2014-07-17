//--------------------------------------------------------------------- defines

#define CLASS   1
#define PATTERN 2

//------------------------------------------------------------------- variables

private nosave mapping channels = ([
    "chat" : ([
        CLASS   : "channel:chat",
        PATTERN : HIC"【傳說】%s：%s\n"NOR,
    ]),
]);

private nosave mapping last_message = ([]);
private nosave mapping last_message_time = ([]);

//------------------------------------------------------------------- functions

int do_channel(object who, string verb, string arg) {
    int now;
    mapping channel;
    object *receivers;
    string id, msg, sender;

    channel = channels[verb];

    if (!channel) {
        return 0;
    }

    arg = arg ? trim(arg) : "...";
    id = who->query_id();
    now = time_millis();

    if (now - 1000 < last_message_time[id]) {
        return notify_fail("用交談頻道無法連續說話。\n");
    }

    if (last_message[id] == arg) {
        return notify_fail("用交談頻道說話請不要重複相同的訊息。\n");
    }

    last_message[id] = arg;
    last_message_time[id] = now;

    sender = who->query("name") + "(" + id + ")";
    receivers = users();
    msg = sprintf(channel[PATTERN], sender, arg);

    message(channel[CLASS], msg, receivers);

    return 1;
}

//-----------------------------------------------------------------------------
