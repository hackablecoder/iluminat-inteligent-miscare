
CREATE TABLE IF NOT EXISTS evenimente_miscare (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data_ora TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    topic TEXT NOT NULL,
    mesaj TEXT NOT NULL
);
