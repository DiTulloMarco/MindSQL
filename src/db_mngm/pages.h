#ifndef PAGES
#define PAGES

#define PAGE_SIZE 4096

/* TYPES DEFINITION */

typedef struct {
  uint8_t data[PAGE_SIZE]; 
} Page;

typedef enum {
  DB_HEADER = 0x01;
  TABLE_DATA = 0x02;
  SCHEMA = 0x03;
} PAGE_TYPE;

typedef struct {
  uint8_t page_type;
  PAGE_TYPE page_number;
  uint16_t free_space;
  uint16_t num_slots;
} PageHeader;

typedef struct {
  uint16_t offset;
  uint16_t length;
} Slot;

/* METHOD SIGNATURES DEFINITION */

int populate_header(const char* db_name);

PageHeader read_header();

#endif
