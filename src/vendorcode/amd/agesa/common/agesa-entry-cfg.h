#ifndef AGESA_ENTRY_CFG_H
#define AGESA_ENTRY_CFG_H


#if defined(__PRE_RAM__)

#define AGESA_ENTRY_INIT_RESET		TRUE
#define AGESA_ENTRY_INIT_EARLY		TRUE
#define AGESA_ENTRY_INIT_POST		TRUE

#define AGESA_ENTRY_INIT_RESUME		IS_ENABLED(CONFIG_HAVE_ACPI_RESUME)

#if IS_ENABLED(CONFIG_AGESA_LEGACY_WRAPPER)
#define AGESA_ENTRY_INIT_ENV		TRUE
#define AGESA_ENTRY_INIT_LATE_RESTORE	IS_ENABLED(CONFIG_HAVE_ACPI_RESUME)
#endif

#else

#if !IS_ENABLED(CONFIG_AGESA_LEGACY_WRAPPER)
#define AGESA_ENTRY_INIT_ENV		TRUE
#define AGESA_ENTRY_INIT_LATE_RESTORE	IS_ENABLED(CONFIG_HAVE_ACPI_RESUME)
#endif

#define AGESA_ENTRY_INIT_MID		TRUE
#define AGESA_ENTRY_INIT_LATE		TRUE
#define AGESA_ENTRY_INIT_S3SAVE 	IS_ENABLED(CONFIG_HAVE_ACPI_RESUME)

#endif

/* Not required. */
#define AGESA_ENTRY_INIT_GENERAL_SERVICES FALSE

/* Required for any multi-core. */
#define AGESA_ENTRY_LATE_RUN_AP_TASK    TRUE

/* Deprecated, reference source is removed from the tree. */
#define AGESA_ENTRY_INIT_RECOVERY                    FALSE

/* Defaults below. */

/*  Process user desired AGESA entry points  */
#ifndef AGESA_ENTRY_INIT_RESET
  #define AGESA_ENTRY_INIT_RESET                     FALSE
#endif

#ifndef AGESA_ENTRY_INIT_EARLY
  #define AGESA_ENTRY_INIT_EARLY                     FALSE
#endif

#ifndef AGESA_ENTRY_INIT_POST
  #define AGESA_ENTRY_INIT_POST                      FALSE
#endif

#ifndef AGESA_ENTRY_INIT_ENV
  #define AGESA_ENTRY_INIT_ENV                       FALSE
#endif

#ifndef AGESA_ENTRY_INIT_MID
  #define AGESA_ENTRY_INIT_MID                       FALSE
#endif

#ifndef AGESA_ENTRY_INIT_LATE
  #define AGESA_ENTRY_INIT_LATE                      FALSE
#endif

#ifndef AGESA_ENTRY_INIT_S3SAVE
  #define AGESA_ENTRY_INIT_S3SAVE                    FALSE
#endif

#ifndef AGESA_ENTRY_INIT_RESUME
  #define AGESA_ENTRY_INIT_RESUME                    FALSE
#endif

#ifndef AGESA_ENTRY_INIT_LATE_RESTORE
  #define AGESA_ENTRY_INIT_LATE_RESTORE              FALSE
#endif

#ifndef AGESA_ENTRY_INIT_GENERAL_SERVICES
  #define AGESA_ENTRY_INIT_GENERAL_SERVICES          FALSE
#endif

#ifndef AGESA_ENTRY_LATE_RUN_AP_TASK
  #define AGESA_ENTRY_LATE_RUN_AP_TASK               TRUE
#endif

#endif /* AGESA_ENTRY_CFG_H */
