//------------------------------------------------------------------ prototypes

string query_save_file();

//------------------------------------------------------------------- functions

int restore() {
    int result;
    string file = query_save_file();

    if (strlen(file)) {
        catch(result = restore_object(file));
    }

    return result;
}

//-----------------------------------------------------------------------------

int save() {
    string file = query_save_file();

    return strlen(file) ? save_object(file) : 0;
}

//-----------------------------------------------------------------------------
