---
created: 
modified: 2025-10-25 23:17:51
aliases: []
Hidden: false
tags:
  - TEST_TAG_4
  - TEST_TAG_3
  - TEST_TAG_2
---

When the database schema is the source of truth

- ORM or models are generated from that existing schema.

### Steps
1. Designing tables, columns, constraints, and relationship directly in the database (via SQL migrations, an admin tool, or a DBA)
2. ORM introspects that schema to create corresponding code models
