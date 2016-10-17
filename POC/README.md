Will have to think how to differ between function calls.

Can't send many arguments to `String_initialize`, because there is none defined in `StringMetaClass`, and should use the Object MetaClass. 

May be somemethod calls should receive va_args, and other the named argument functions? May be it's a better idea to receive always `va_args`.
