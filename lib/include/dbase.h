#ifndef ___DBASE_H___
#define ___DBASE_H___

//-------------------------------------------------------------- default object

mixed query_default_object();
void set_default_object(mixed);

//----------------------------------------------------------------------- dbase

void add(string, mixed);
void delete(string);
varargs mixed query(string, int);
mapping query_entire_dbase();
void set(string, mixed);

//------------------------------------------------------------- temporary dbase

void add_temp(string, mixed);
void delete_temp(string);
mapping query_entire_temp_dbase();
varargs mixed query_temp(string, int);
void set_temp(string, mixed);

//-----------------------------------------------------------------------------

#endif
