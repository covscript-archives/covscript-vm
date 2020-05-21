# Reserved Names

Reserved names are some identifiers that are used in special cases.
A reserved name always begins with a '<' ('\u003c').

Epoch VM has the following reserved names:

## \<class-init\>
This name of **class constructor** and is only used as a field name.
The type of the field should only be `FIELD_clo`,
and that closure should take no argument and return `Unit`.

## \<main\>
This name is only used as a field name which indicates that
the field name `<main>` is the entrance function of a epoch file.

# Special Names

## constructor
The name of the object constructor, which is defined by user.
This name is only used as a field name.
The type of the field should only be `FIELD_clo`,
and that closure should return `Unit`.

