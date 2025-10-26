When the database schema is the source of truth

- ORM or models are generated from that existing schema.

### Steps
1. Designing tables, columns, constraints, and relationship directly in the database (via SQL migrations, an admin tool, or a DBA)
2. ORM introspects that schema to create corresponding code models