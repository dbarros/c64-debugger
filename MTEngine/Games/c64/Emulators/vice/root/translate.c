/*
 * translate.c - Global internationalization routines.
 *
 * Written by
 *  Marco van den Heuvel <blackystardust68@yahoo.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmdline.h"

#ifdef HAS_TRANSLATION
#include "intl.h"
#endif

#include "lib.h"
#include "log.h"
#include "resources.h"
#include "translate_languages.h"
#include "translate.h"
#include "util.h"

#define countof(array) (sizeof(array) / sizeof((array)[0]))

typedef struct translate_s {
    int resource_id;
    char *text;
} translate_t;

#ifdef HAS_TRANSLATION
char *current_language = NULL;
int current_language_index = 0;
#endif

/* GLOBAL STRING ID TEXT TABLE */

///

/*
 * translate_text.c - Translation texts to be included in translate.c
 *
 * Written by
 *  Marco van den Heuvel <blackystardust68@yahoo.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

translate_t string_table[] = {
	
	/* autostart.c */
	/* en */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE,    N_("Cannot load snapshot file.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_DA, "Kunne ikke indlÊse snapshot-fil."},
	/* de */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_DE, "Kann Snapshot Datei nicht laden."},
	/* es */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_ES, "No puedo cargar fichero volcado memoria"},
	/* fr */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_FR, "Impossible de charger l'instantanÈ."},
	/* hu */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_HU, "Nem siker¸lt betˆlteni a pillanatkÈp f·jlt."},
	/* it */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_IT, "Non Ë possibile caricare il file di snapshot."},
	/* ko */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_NL, "Kan momentopnamebestand niet laden."},
	/* pl */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_PL, "Nie moøna wczytaÊ pliku zrzutu."},
	/* ru */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_RU, "Cannot load snapshot file."},
	/* sv */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_SV, "Kan inte l‰sa in ˆgonblicksbildfil."},
	/* tr */ {IDGS_CANNOT_LOAD_SNAPSHOT_FILE_TR, "Anl˝k gˆr¸nt¸ dosyas˝ y¸klenemedi."},
#endif
	
	/* debug.c */
	/* en */ {IDGS_PLAYBACK_ERROR_DIFFERENT,    N_("Playback error: %s different from line %d of file debug%06d")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_PLAYBACK_ERROR_DIFFERENT_DA, "Afspilningsfejl: %s forskellig fra linje %d i filen debug%06d"},
	/* de */ {IDGS_PLAYBACK_ERROR_DIFFERENT_DE, "Wiedergabe Fehler: %s ist unterschiedlich von Zeile %d in Datei debug%06d"},
	/* es */ {IDGS_PLAYBACK_ERROR_DIFFERENT_ES, "Error de reproducciÛn: %s diferente desde linea %d del fichero de depuraciÛn%06d"},
	/* fr */ {IDGS_PLAYBACK_ERROR_DIFFERENT_FR, "Erreur de lecture: %s diffÈrent de la ligne %d du fichier debug%06d"},
	/* hu */ {IDGS_PLAYBACK_ERROR_DIFFERENT_HU, "Visszaj·tsz·si hiba: %s k¸lˆnbˆzik a %d. sorban a debug%06d f·jl esetÈn"},
	/* it */ {IDGS_PLAYBACK_ERROR_DIFFERENT_IT, "Errore di riproduzione: %s Ë differente dalla linea %d del file di debug %06d"},
	/* ko */ {IDGS_PLAYBACK_ERROR_DIFFERENT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_PLAYBACK_ERROR_DIFFERENT_NL, "Afspeelfout: %s is anders dan regel %d van bestand debug%06d"},
	/* pl */ {IDGS_PLAYBACK_ERROR_DIFFERENT_PL, "B≥±d otwarzania: %s rÛøni siÍ od linii %d pliku debug%06d"},
	/* ru */ {IDGS_PLAYBACK_ERROR_DIFFERENT_RU, "Playback error: %s different from line %d of file debug%06d"},
	/* sv */ {IDGS_PLAYBACK_ERROR_DIFFERENT_SV, "≈terspelningsfel: %s inte lika som rad %d i filen debug%06d"},
	/* tr */ {IDGS_PLAYBACK_ERROR_DIFFERENT_TR, "Kay˝ttan y¸r¸tme hatas˝: %s dosyan˝n %d sat˝r˝ndan farkl˝ (hata ay˝klama%06d)"},
#endif
	
	/* event.c */
	/* en */ {IDGS_CANNOT_CREATE_IMAGE,    N_("Cannot create image file!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_CREATE_IMAGE_DA, "Kunne ikke oprette image-fil!"},
	/* de */ {IDGS_CANNOT_CREATE_IMAGE_DE, "Kann Imagedatei nicht erzeugen!"},
	/* es */ {IDGS_CANNOT_CREATE_IMAGE_ES, "°No puedo crear fichero imagen!"},
	/* fr */ {IDGS_CANNOT_CREATE_IMAGE_FR, "Impossible de crÈer le fichier image!"},
	/* hu */ {IDGS_CANNOT_CREATE_IMAGE_HU, "Nem siker¸lt a kÈpm·s f·jlt lÈtrehozni!"},
	/* it */ {IDGS_CANNOT_CREATE_IMAGE_IT, "Non Ë possibile creare il file immagine!"},
	/* ko */ {IDGS_CANNOT_CREATE_IMAGE_KO, "¿ÃπÃ¡ˆ ∆ƒ¿œ¿ª ª˝º∫«“ºˆ æ¯Ω¿¥œ¥Ÿ!"},
	/* nl */ {IDGS_CANNOT_CREATE_IMAGE_NL, "Kan bestand niet maken!"},
	/* pl */ {IDGS_CANNOT_CREATE_IMAGE_PL, "Nie moøna utworzyÊ pliku obrazu!"},
	/* ru */ {IDGS_CANNOT_CREATE_IMAGE_RU, "Ω’ „‘–’‚·Ô ·ﬁ◊‘–‚Ï ‰–Ÿ€ ﬁ—‡–◊–!"},
	/* sv */ {IDGS_CANNOT_CREATE_IMAGE_SV, "Kan inte skapa avbildningsfil!"},
	/* tr */ {IDGS_CANNOT_CREATE_IMAGE_TR, "Imaj dosyas˝ yarat˝lamad˝!"},
#endif
	
	/* event.c */
	/* en */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S,    N_("Cannot write image file %s")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_DA, "Kunne ikks skrive image-fil %s"},
	/* de */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_DE, "Kann Datei %s nicht schreiben"},
	/* es */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_ES, "No puedo grabar fichero imagen %s"},
	/* fr */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_FR, "Impossible d'Ècrire le fichier image %s"},
	/* hu */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_HU, "Nem siker¸lt a %s kÈpm·s f·jlba Ìrni"},
	/* it */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_IT, "Non Ë possibile scrivere l'immagine %s"},
	/* ko */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_NL, "Kan niet schrijven naar bestand %s"},
	/* pl */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_PL, "Nie moøna zapisaÊ pliku obrazu %s"},
	/* ru */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_RU, "Cannot write image file %s"},
	/* sv */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_SV, "Kan inte skriva avbildningsfil %s"},
	/* tr */ {IDGS_CANNOT_WRITE_IMAGE_FILE_S_TR, "%s imaj dosyas˝na yaz˝lamad˝"},
#endif
	
	/* event.c */
	/* en */ {IDGS_CANNOT_FIND_MAPPED_NAME_S,    N_("Cannot find mapped name for %s")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_DA, "Kunne ikke finde mappet navn for %s"},
	/* de */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_DE, "Kann zugeordneten Namen f¸r `%s' nicht finden."},
	/* es */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_ES, "No puedo encontrar nombre mapeado para %s"},
	/* fr */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_FR, "Impossible de trouver le nom correspondant ‡ %s"},
	/* hu */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_HU, "A VICE %s lekÈpzett nevÈt nem tal·lja"},
	/* it */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_IT, "Non Ë possibile trovare il nome mappato per %s"},
	/* ko */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_NL, "Kan vertaalde naam voor %s niet vinden"},
	/* pl */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_PL, "Nie moøna znaleºÊ zmapowanej nazwy %s"},
	/* ru */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_RU, "Cannot find mapped name for %s"},
	/* sv */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_SV, "Kan inte kopplat namn fˆr %s"},
	/* tr */ {IDGS_CANNOT_FIND_MAPPED_NAME_S_TR, "%s iÁin e˛le˛me ismi bulunamad˝"},
#endif
	
	/* event.c */
	/* en */ {IDGS_CANT_CREATE_START_SNAP_S,    N_("Could not create start snapshot file %s.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANT_CREATE_START_SNAP_S_DA, "Kunne ikke oprette start-snapshot-filen %s."},
	/* de */ {IDGS_CANT_CREATE_START_SNAP_S_DE, "Kann Start Snapshot Datei nicht erzeugen: %s"},
	/* es */ {IDGS_CANT_CREATE_START_SNAP_S_ES, "No puedo crear inicio fichero volcado memoria %s."},
	/* fr */ {IDGS_CANT_CREATE_START_SNAP_S_FR, "Impossible de crÈer l'instantanÈ de dÈpart %s."},
	/* hu */ {IDGS_CANT_CREATE_START_SNAP_S_HU, "Nem siker¸lt a %s kezdeti pillanatkÈp f·jlt lÈtrehozni."},
	/* it */ {IDGS_CANT_CREATE_START_SNAP_S_IT, "Non Ë possibile creare il file di inizio snapshot %s."},
	/* ko */ {IDGS_CANT_CREATE_START_SNAP_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANT_CREATE_START_SNAP_S_NL, "Kon het start momentopnamebestand %s niet maken."},
	/* pl */ {IDGS_CANT_CREATE_START_SNAP_S_PL, "Nie moøna utworzyÊ pocz±tkowego pliku zrzutu %s."},
	/* ru */ {IDGS_CANT_CREATE_START_SNAP_S_RU, "Could not create start snapshot file %s."},
	/* sv */ {IDGS_CANT_CREATE_START_SNAP_S_SV, "Kunde inte skapa startˆgonblicksbildfilen %s."},
	/* tr */ {IDGS_CANT_CREATE_START_SNAP_S_TR, "Anl˝k gˆr¸nt¸ dosyas˝ %s yarat˝lamad˝."},
#endif
	
	/* event.c */
	/* en */ {IDGS_ERROR_READING_END_SNAP_S,    N_("Error reading end snapshot file %s.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ERROR_READING_END_SNAP_S_DA, "Fejl under lÊsning af slut-snapshot %s."},
	/* de */ {IDGS_ERROR_READING_END_SNAP_S_DE, "Kann Ende Snapshot Datei nicht lesen: %s"},
	/* es */ {IDGS_ERROR_READING_END_SNAP_S_ES, "Error leyendo final fichero volcado memoria %s."},
	/* fr */ {IDGS_ERROR_READING_END_SNAP_S_FR, "Erreur de lecture de l'instantanÈ de fin %s."},
	/* hu */ {IDGS_ERROR_READING_END_SNAP_S_HU, "Hiba az utolsÛ %s pillanatkÈp f·jl Ìr·sakor."},
	/* it */ {IDGS_ERROR_READING_END_SNAP_S_IT, "Errore durante la lettura del file di fine snapshot %s."},
	/* ko */ {IDGS_ERROR_READING_END_SNAP_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ERROR_READING_END_SNAP_S_NL, "Fout bij het lezen van het eind van het momentopnamebestand %s."},
	/* pl */ {IDGS_ERROR_READING_END_SNAP_S_PL, "B≥±d odczytu koÒcowego pliku zrzutu %s."},
	/* ru */ {IDGS_ERROR_READING_END_SNAP_S_RU, "Error reading end snapshot file %s."},
	/* sv */ {IDGS_ERROR_READING_END_SNAP_S_SV, "Fel vid l‰sning av slutˆgonblicksbildfilen %s."},
	/* tr */ {IDGS_ERROR_READING_END_SNAP_S_TR, "Anl˝k gˆr¸nt¸ dosyas˝ %s okuma hatas˝."},
#endif
	
	/* event.c */
	/* en */ {IDGS_CANT_CREATE_END_SNAP_S,    N_("Could not create end snapshot file %s.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANT_CREATE_END_SNAP_S_DA, "Kunne ikke oprette slut-snapshot-filen %s."},
	/* de */ {IDGS_CANT_CREATE_END_SNAP_S_DE, "Kann Ende Snapshot Datei nicht erzeugen: %s"},
	/* es */ {IDGS_CANT_CREATE_END_SNAP_S_ES, "No puedo crear fin fichero volcado memoria %s."},
	/* fr */ {IDGS_CANT_CREATE_END_SNAP_S_FR, "Impossible de crÈer l'instantanÈ de fin %s."},
	/* hu */ {IDGS_CANT_CREATE_END_SNAP_S_HU, "Nem siker¸lt a %s befejezı pillanatkÈp f·jlt lÈtrehozni."},
	/* it */ {IDGS_CANT_CREATE_END_SNAP_S_IT, "Non Ë possibile creare il file di fine snapshot %s."},
	/* ko */ {IDGS_CANT_CREATE_END_SNAP_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANT_CREATE_END_SNAP_S_NL, "Kon het eind momentopnamebestand %s niet maken."},
	/* pl */ {IDGS_CANT_CREATE_END_SNAP_S_PL, "Nie moøna utworzyÊ koÒcowego pliku zrzutu %s."},
	/* ru */ {IDGS_CANT_CREATE_END_SNAP_S_RU, "Could not create end snapshot file %s."},
	/* sv */ {IDGS_CANT_CREATE_END_SNAP_S_SV, "Kunde inte skapa slutˆgonblicksbildfilen %s."},
	/* tr */ {IDGS_CANT_CREATE_END_SNAP_S_TR, "Son anl˝k gˆr¸nt¸ dosyas˝ %s yarat˝lamad˝."},
#endif
	
	/* event.c */
	/* en */ {IDGS_CANT_OPEN_END_SNAP_S,    N_("Could not open end snapshot file %s.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANT_OPEN_END_SNAP_S_DA, "Kunne ikke Âbne slut-snapshot-filen %s."},
	/* de */ {IDGS_CANT_OPEN_END_SNAP_S_DE, "Kann Ende Snapshot Datei nicht ˆffnen: %s"},
	/* es */ {IDGS_CANT_OPEN_END_SNAP_S_ES, "No puedo abrir fin fichero volcado memoria %s."},
	/* fr */ {IDGS_CANT_OPEN_END_SNAP_S_FR, "Impossible d'ouvrir l'instantanÈ de fin %s."},
	/* hu */ {IDGS_CANT_OPEN_END_SNAP_S_HU, "Nem siker¸lt az utolsÛ %s pillanatkÈp f·jlt megnyitni."},
	/* it */ {IDGS_CANT_OPEN_END_SNAP_S_IT, "Non Ë possibile aprire il file di fine snapshot %s."},
	/* ko */ {IDGS_CANT_OPEN_END_SNAP_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANT_OPEN_END_SNAP_S_NL, "Kon het eind momentopnamebestand %s niet openen."},
	/* pl */ {IDGS_CANT_OPEN_END_SNAP_S_PL, "Nie moøna otworzyÊ koÒcowego pliku zrzutu %s."},
	/* ru */ {IDGS_CANT_OPEN_END_SNAP_S_RU, "Could not open end snapshot file %s."},
	/* sv */ {IDGS_CANT_OPEN_END_SNAP_S_SV, "Kunde inte ˆppna slutˆgonblicksbildfilen %s."},
	/* tr */ {IDGS_CANT_OPEN_END_SNAP_S_TR, "Son anl˝k gˆr¸nt¸ dosyas˝ %s aÁ˝lamad˝."},
#endif
	
	/* event.c */
	/* en */ {IDGS_CANT_FIND_SECTION_END_SNAP,    N_("Could not find event section in end snapshot file.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANT_FIND_SECTION_END_SNAP_DA, "Kunne ikke finde hÊndelses-sektionen i slut-snapshot-filen."},
	/* de */ {IDGS_CANT_FIND_SECTION_END_SNAP_DE, "Kann Sektion in Ende Snapshotdatei nicht finden."},
	/* es */ {IDGS_CANT_FIND_SECTION_END_SNAP_ES, "No puedo encontrar secciÛn eventos en fin fichero volcado memoria."},
	/* fr */ {IDGS_CANT_FIND_SECTION_END_SNAP_FR, "Impossible de trouver la section event dans l'instantanÈ de fin."},
	/* hu */ {IDGS_CANT_FIND_SECTION_END_SNAP_HU, "Nem tal·ltam esemÈny rÈszt az utolsÛ pillanatkÈp f·jlban."},
	/* it */ {IDGS_CANT_FIND_SECTION_END_SNAP_IT, "Non Ë possibile trovare la sezione eventi nel file di fine snapshot."},
	/* ko */ {IDGS_CANT_FIND_SECTION_END_SNAP_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANT_FIND_SECTION_END_SNAP_NL, "Kon de gebeurtenis sectie in eind momentopnamebestand niet vinden."},
	/* pl */ {IDGS_CANT_FIND_SECTION_END_SNAP_PL, "Nie znaleziono sekcji zdarzeÒ w pliku koÒcowym zrzutu"},
	/* ru */ {IDGS_CANT_FIND_SECTION_END_SNAP_RU, "Could not find event section in end snapshot file."},
	/* sv */ {IDGS_CANT_FIND_SECTION_END_SNAP_SV, "Kunde inte hinna h‰ndelsedelen i slutˆgonblicksbilden."},
	/* tr */ {IDGS_CANT_FIND_SECTION_END_SNAP_TR, "Son anl˝k gˆr¸nt¸ dosyas˝nda olay bˆl¸m¸ bulunamad˝."},
#endif
	
	/* event.c */
	/* en */ {IDGS_ERROR_READING_START_SNAP_TRIED,    N_("Error reading start snapshot file. Tried %s and %s")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ERROR_READING_START_SNAP_TRIED_DA, "Fejl under lÊsning af start-snapshot. Pr¯vede %s og %s"},
	/* de */ {IDGS_ERROR_READING_START_SNAP_TRIED_DE, "Fehler beim Lesen der Start Snapshot Datei. Versuch gescheitert bei %s und %s."},
	/* es */ {IDGS_ERROR_READING_START_SNAP_TRIED_ES, "Error leyendo inicio fichero volcaco memoria. Intentado %s y %s"},
	/* fr */ {IDGS_ERROR_READING_START_SNAP_TRIED_FR, "Erreur de lecture de l'instantanÈ de dÈpart. EssayÈ %s et %s"},
	/* hu */ {IDGS_ERROR_READING_START_SNAP_TRIED_HU, "Nem siker¸lt az elsı pillanatkÈp f·jl olvas·sa. KiprÛb·lva: %s Ès %s"},
	/* it */ {IDGS_ERROR_READING_START_SNAP_TRIED_IT, "Errore durante la lettura del file di inizio snapshot. Ho provato %s e %s"},
	/* ko */ {IDGS_ERROR_READING_START_SNAP_TRIED_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ERROR_READING_START_SNAP_TRIED_NL, "Fout bij het lezen van het start momentopnamebestand. Heb %s en %s geprobeerd"},
	/* pl */ {IDGS_ERROR_READING_START_SNAP_TRIED_PL, "B≥±d odczytu pocz±tkowego pliku zrzutu. WyprÛbowano %s i %s"},
	/* ru */ {IDGS_ERROR_READING_START_SNAP_TRIED_RU, "Error reading start snapshot file. Tried %s and %s"},
	/* sv */ {IDGS_ERROR_READING_START_SNAP_TRIED_SV, "Fel vid l‰sning av startˆgonblicksbildfil. Fˆrsˆkte med %s och %s"},
	/* tr */ {IDGS_ERROR_READING_START_SNAP_TRIED_TR, "Ba˛lang˝Á anl˝k gˆr¸nt¸ dosyas˝ okuma hatas˝. %s ve %s denendi"},
#endif
	
	/* event.c */
	/* en */ {IDGS_ERROR_READING_START_SNAP,    N_("Error reading start snapshot file.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ERROR_READING_START_SNAP_DA, "Fejl under lÊsning af start-snapshot."},
	/* de */ {IDGS_ERROR_READING_START_SNAP_DE, "Fehler beim Lesen der Start Snapshot Datei."},
	/* es */ {IDGS_ERROR_READING_START_SNAP_ES, "Error leyendo inicio fichero volcaco memoria."},
	/* fr */ {IDGS_ERROR_READING_START_SNAP_FR, "Erreur de lecture de l'instantanÈ de dÈpart."},
	/* hu */ {IDGS_ERROR_READING_START_SNAP_HU, "Nem siker¸lt az indÌtÛ pillanatkÈp f·jl olvas·sa."},
	/* it */ {IDGS_ERROR_READING_START_SNAP_IT, "Errore durante la lettura del file di inizio snapshot."},
	/* ko */ {IDGS_ERROR_READING_START_SNAP_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ERROR_READING_START_SNAP_NL, "Fout bij het lezen van het start momentopnamebestand."},
	/* pl */ {IDGS_ERROR_READING_START_SNAP_PL, "B≥±d odczytu pocz±tkowego pliku zrzutu."},
	/* ru */ {IDGS_ERROR_READING_START_SNAP_RU, "Error reading start snapshot file."},
	/* sv */ {IDGS_ERROR_READING_START_SNAP_SV, "Fel vid l‰sning av startˆgonblicksbildfil."},
	/* tr */ {IDGS_ERROR_READING_START_SNAP_TR, "Ba˛lang˝Á anl˝k gˆr¸nt¸ dosyas˝ okuma hatas˝."},
#endif
	
	/* screenshot.c */
	/* en */ {IDGS_SORRY_NO_MULTI_RECORDING,    N_("Sorry. Multiple recording is not supported.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SORRY_NO_MULTI_RECORDING_DA, "Kun en optagelse kan foretages ad gangen."},
	/* de */ {IDGS_SORRY_NO_MULTI_RECORDING_DE, "Eine Aufnahme ist zur Zeit aktiv. Mehrfache Aufnahme ist nicht mˆglich."},
	/* es */ {IDGS_SORRY_NO_MULTI_RECORDING_ES, "Lo siento, no estan soportadas las grabaciones m˙ltiples."},
	/* fr */ {IDGS_SORRY_NO_MULTI_RECORDING_FR, "DÈsolÈ. De multiples enregistrements ne sont pas supportÈ."},
	/* hu */ {IDGS_SORRY_NO_MULTI_RECORDING_HU, "Sajn·lom: tˆbbszˆrˆs felvÈtel nem t·mogatott."},
	/* it */ {IDGS_SORRY_NO_MULTI_RECORDING_IT, "Le registrazioni multiple non sono supportate."},
	/* ko */ {IDGS_SORRY_NO_MULTI_RECORDING_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SORRY_NO_MULTI_RECORDING_NL, "Sorry. Meerdere opnamen wordt niet ondersteund."},
	/* pl */ {IDGS_SORRY_NO_MULTI_RECORDING_PL, "Przepraszamy, wielo∂cieøkowy zapis nie jest obs≥ugiwany."},
	/* ru */ {IDGS_SORRY_NO_MULTI_RECORDING_RU, "Sorry. Multiple recording is not supported."},
	/* sv */ {IDGS_SORRY_NO_MULTI_RECORDING_SV, "Endast en inspelning kan gˆras Ât gÂngen."},
	/* tr */ {IDGS_SORRY_NO_MULTI_RECORDING_TR, "‹zg¸n¸z. «oklu kay˝t desteklenmiyor."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED,    N_("write to sound device failed.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_DA, "Kunne ikke skrive til lydenhed."},
	/* de */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_DE, "Schreiben auf Sound Ger‰t ist fehlgeschlagen."},
	/* es */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_ES, "Fallo en grabaciÛn perifÈrico sonido."},
	/* fr */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_FR, "impossible d'Ècrire sur le pÈriphÈrique son."},
	/* hu */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_HU, "Nem siker¸lt a hangeszkˆzre Ìrni"},
	/* it */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_IT, "scrittura sulla scheda audio fallita."},
	/* ko */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_NL, "schrijfactie naar geluidsapparaat is mislukt."},
	/* pl */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_PL, "Zapis do urz±dzenia dºwiÍku nie powiÛd≥ siÍ."},
	/* ru */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_RU, "write to sound device failed."},
	/* sv */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_SV, "misslyckades att skriva till ljudenhet."},
	/* tr */ {IDGS_WRITE_TO_SOUND_DEVICE_FAILED_TR, "ses ayg˝t˝na yazma ba˛ar˝s˝z oldu."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_CANNOT_OPEN_SID_ENGINE,    N_("Cannot open SID engine")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_OPEN_SID_ENGINE_DA, "Kunne ikke Âbne SID-motor"},
	/* de */ {IDGS_CANNOT_OPEN_SID_ENGINE_DE, "Kann SID Engine nicht ˆffnen"},
	/* es */ {IDGS_CANNOT_OPEN_SID_ENGINE_ES, "No puedo abrir motor SID"},
	/* fr */ {IDGS_CANNOT_OPEN_SID_ENGINE_FR, "Erreur d'ouverture de l'engin SID"},
	/* hu */ {IDGS_CANNOT_OPEN_SID_ENGINE_HU, "Nem siker¸lt a SID motort megnyitni"},
	/* it */ {IDGS_CANNOT_OPEN_SID_ENGINE_IT, "Non Ë possibile aprire il motore SID"},
	/* ko */ {IDGS_CANNOT_OPEN_SID_ENGINE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_OPEN_SID_ENGINE_NL, "Kan de SID kern niet openen"},
	/* pl */ {IDGS_CANNOT_OPEN_SID_ENGINE_PL, "Nie moøna otworzyÊ silnika SID"},
	/* ru */ {IDGS_CANNOT_OPEN_SID_ENGINE_RU, "Cannot open SID engine"},
	/* sv */ {IDGS_CANNOT_OPEN_SID_ENGINE_SV, "Kan inte ˆppna SID-motor"},
	/* tr */ {IDGS_CANNOT_OPEN_SID_ENGINE_TR, "SID motoru aÁ˝lam˝yor"},
#endif
	
	/* sound.c */
	/* en */ {IDGS_CANNOT_INIT_SID_ENGINE,    N_("Cannot initialize SID engine")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_INIT_SID_ENGINE_DA, "Kunne ikke initialisere SID-motor"},
	/* de */ {IDGS_CANNOT_INIT_SID_ENGINE_DE, "Kann SID Engine nicht initialisieren"},
	/* es */ {IDGS_CANNOT_INIT_SID_ENGINE_ES, "No puedo inicializar motor SID"},
	/* fr */ {IDGS_CANNOT_INIT_SID_ENGINE_FR, "Erreur d'initialisation de l'engin SID"},
	/* hu */ {IDGS_CANNOT_INIT_SID_ENGINE_HU, "Nem siker¸lt a SID motort elindÌtani"},
	/* it */ {IDGS_CANNOT_INIT_SID_ENGINE_IT, "Non Ë possibile inizializzare il motore SID"},
	/* ko */ {IDGS_CANNOT_INIT_SID_ENGINE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_INIT_SID_ENGINE_NL, "Kan de SID kern niet initialiseren"},
	/* pl */ {IDGS_CANNOT_INIT_SID_ENGINE_PL, "Nie moøna uruchomiÊ silnika SID"},
	/* ru */ {IDGS_CANNOT_INIT_SID_ENGINE_RU, "Cannot initialize SID engine"},
	/* sv */ {IDGS_CANNOT_INIT_SID_ENGINE_SV, "Kan inte initiera SID-motor"},
	/* tr */ {IDGS_CANNOT_INIT_SID_ENGINE_TR, "SID motorunun ba˛lang˝Á ayarlar˝ yap˝lam˝yor"},
#endif
	
	/* sound.c */
	/* en */ {IDGS_INIT_FAILED_FOR_DEVICE_S,    N_("initialization failed for device `%s'.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_INIT_FAILED_FOR_DEVICE_S_DA, "Initialisering fejlede for enhed \"%s\"."},
	/* de */ {IDGS_INIT_FAILED_FOR_DEVICE_S_DE, "Initialisierung von Ger‰t `%s' fehlgeschlagen."},
	/* es */ {IDGS_INIT_FAILED_FOR_DEVICE_S_ES, "Fallo inicializaciÛn para perifÈrico `%s'."},
	/* fr */ {IDGS_INIT_FAILED_FOR_DEVICE_S_FR, "erreur d'initialisation du pÈriphÈrique `%s'."},
	/* hu */ {IDGS_INIT_FAILED_FOR_DEVICE_S_HU, "A `%s' eszkˆzt nem siker¸lt elindÌtani."},
	/* it */ {IDGS_INIT_FAILED_FOR_DEVICE_S_IT, "inizializzazione fallita per il device `%s'."},
	/* ko */ {IDGS_INIT_FAILED_FOR_DEVICE_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_INIT_FAILED_FOR_DEVICE_S_NL, "initialisatie voor apparaat `%s' is mislukt."},
	/* pl */ {IDGS_INIT_FAILED_FOR_DEVICE_S_PL, "Inicjalizacja urz±dzenia `%s' nie powiod≥a siÍ."},
	/* ru */ {IDGS_INIT_FAILED_FOR_DEVICE_S_RU, "initialization failed for device `%s'."},
	/* sv */ {IDGS_INIT_FAILED_FOR_DEVICE_S_SV, "initiering misslyckades fˆr enhet \"%s\"."},
	/* tr */ {IDGS_INIT_FAILED_FOR_DEVICE_S_TR, "`%s' ayg˝t˝ iÁin ba˛lang˝Á ayarlar˝ ba˛ar˝s˝z oldu."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT,    N_("device '%s' not found or not supported.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_DA, "enhed \"%s\" ikke fundet eller underst¯ttet."},
	/* de */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_DE, "Ger‰t '%s' konnte nicht gefunden werden oder ist nicht unterst¸tzt."},
	/* es */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_ES, "PerifÈrico '%s' no encontrado o soportado."},
	/* fr */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_FR, "pÈriphÈrique '%s' non trouvÈ ou non supportÈ."},
	/* hu */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_HU, "A '%s' eszkˆz nem lÈtezik, vagy nem t·mogatott."},
	/* it */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_IT, "il device '%s' non Ë stato trovato oppure non Ë supportato."},
	/* ko */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_NL, "apparaat '%s' niet gevonden of wordt niet ondersteund"},
	/* pl */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_PL, "Nie znaleziono urz±dzenia '%s' lub jest ono niewspierane"},
	/* ru */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_RU, "device '%s' not found or not supported."},
	/* sv */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_SV, "enheten \"%s\" hittades eller stˆds ej."},
	/* tr */ {IDGS_DEVICE_S_NOT_FOUND_SUPPORT_TR, "'%s' ayg˝t˝ yok ya da desteklenmiyor."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_RECORD_DEVICE_S_NOT_EXIST,    N_("Recording device %s doesn't exist!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_DA, "Optageenheden %s findes ikke!"},
	/* de */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_DE, "Aufnahmeger‰t %s existiert nicht!"},
	/* es */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_ES, "No existe el perifÈrico %s de grabaciÛn "},
	/* fr */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_FR, "Le pÈriphÈrique d'enregistrement %s n'existe pas!"},
	/* hu */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_HU, "A %s felvevı eszkˆz nem lÈtezik!"},
	/* it */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_IT, "Il device di registrazione %s non esiste!"},
	/* ko */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_NL, "Opnameapparaat %s bestaat niet!"},
	/* pl */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_PL, "Urz±dzenie zapisu %s nie istnieje!"},
	/* ru */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_RU, "Recording device %s doesn't exist!"},
	/* sv */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_SV, "Inspelningsenhet %s finns inte!"},
	/* tr */ {IDGS_RECORD_DEVICE_S_NOT_EXIST_TR, "Kay˝t ayg˝t˝ %s mevcut deil!"},
#endif
	
	/* sound.c */
	/* en */ {IDGS_RECORD_DIFFERENT_PLAYBACK,    N_("Recording device must be different from playback device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_RECORD_DIFFERENT_PLAYBACK_DA, "Indspilningsenhed og optagelsesenhed skal vÊre forskellige"},
	/* de */ {IDGS_RECORD_DIFFERENT_PLAYBACK_DE, "Aufnahmeger‰t muss unterschiedlich vom Abspielger‰t sein"},
	/* es */ {IDGS_RECORD_DIFFERENT_PLAYBACK_ES, "Periferico de grabaciÛn y reproducciÛn tienen que ser diferentes"},
	/* fr */ {IDGS_RECORD_DIFFERENT_PLAYBACK_FR, "Le pÈriphÈrique de son d'enregistrement doivent Ítre diffÈrents"},
	/* hu */ {IDGS_RECORD_DIFFERENT_PLAYBACK_HU, "A felvevı Ès lej·tszÛ eszkˆzˆknek k¸lˆnbˆznie kell"},
	/* it */ {IDGS_RECORD_DIFFERENT_PLAYBACK_IT, "Il device di registrazione deve essere differente da quello di riproduzione"},
	/* ko */ {IDGS_RECORD_DIFFERENT_PLAYBACK_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_RECORD_DIFFERENT_PLAYBACK_NL, "Opnameapparaat moet anders zijn dan afspeelapparaat"},
	/* pl */ {IDGS_RECORD_DIFFERENT_PLAYBACK_PL, "Urz±dzenie zapisu musi byÊ inne niø urz±dzenie odtwarzania"},
	/* ru */ {IDGS_RECORD_DIFFERENT_PLAYBACK_RU, "√·‚‡ﬁŸ·‚“ﬁ ◊–ﬂÿ·ÿ ‘ﬁ€÷›ﬁ ﬁ‚€ÿÁ–‚Ï·Ô ﬁ‚ „·‚‡ﬁŸ·‚“– “ﬁ·ﬂ‡ﬁÿ◊“’‘’›ÿÔ"},
	/* sv */ {IDGS_RECORD_DIFFERENT_PLAYBACK_SV, "Inspelningsenhet och Âterspelningsenhet kan inte vara samma"},
	/* tr */ {IDGS_RECORD_DIFFERENT_PLAYBACK_TR, "Kay˝t ayg˝t˝ kay˝ttan y¸r¸tme ayg˝t˝ ile farkl˝ olmak zorundad˝r"},
#endif
	
	/* sound.c */
	/* en */ {IDGS_WARNING_RECORDING_REALTIME,    N_("Warning! Recording device %s seems to be a realtime device!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_WARNING_RECORDING_REALTIME_DA, "Advarsel! Optageenheden %s ser ud til at vÊre en realtidsenhed!"},
	/* de */ {IDGS_WARNING_RECORDING_REALTIME_DE, "Warnung! Aufnahmeger‰t %s scheint ein Echtzeitger‰t zu sein!"},
	/* es */ {IDGS_WARNING_RECORDING_REALTIME_ES, "°PrecauciÛn! perifÈrico de grabaciÛn %s parece ser un periferico en tiempo real"},
	/* fr */ {IDGS_WARNING_RECORDING_REALTIME_FR, "Attention! Le pÈriphÈrique d'enregistrement %s semble Ítre un pÈriphÈrique temps rÈel"},
	/* hu */ {IDGS_WARNING_RECORDING_REALTIME_HU, "Figyelem! A %s felvevı eszkˆz ˙gy t˚nik, valÛs idej˚ eszkˆz!"},
	/* it */ {IDGS_WARNING_RECORDING_REALTIME_IT, "Attenzione! Il device di registrazione %s sembra essere un dispositivo realtime!"},
	/* ko */ {IDGS_WARNING_RECORDING_REALTIME_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_WARNING_RECORDING_REALTIME_NL, "Waarschuwing! Opnameapparaat %s lijkt een realtime apparaat te zijn!"},
	/* pl */ {IDGS_WARNING_RECORDING_REALTIME_PL, "Ostrzeøenie! Urz±dzenie zapisu %s dzia≥a chyba w czasie rzeczywistym!"},
	/* ru */ {IDGS_WARNING_RECORDING_REALTIME_RU, "Warning! Recording device %s seems to be a realtime device!"},
	/* sv */ {IDGS_WARNING_RECORDING_REALTIME_SV, "Varning! Inspelningsenheten %s verkar vara en realtidsenhet!"},
	/* tr */ {IDGS_WARNING_RECORDING_REALTIME_TR, "Uyar˝! Kay˝t ayg˝t˝ %s gerÁek zamanl˝ bir ayg˝t gibi gˆr¸n¸yor!"},
#endif
	
	/* sound.c */
	/* en */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR,    N_("The recording device doesn't support current sound parameters")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_DA, "Optageenheden underst¯tter ikke de valgte lydparametre"},
	/* de */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_DE, "Aufnahmeger‰t unterst¸tzt derzeitige Soundeinstellungen nicht"},
	/* es */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_ES, "El perifÈrico de grabaciÛn no soporta los actuales parametros de sonido"},
	/* fr */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_FR, "Le pÈriphÈrique d'enregistrement ne supporte pas les paramËtres actuels"},
	/* hu */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_HU, "A felvevı eszkˆz nem t·mogatja az aktu·lis hangbe·llÌt·sokat"},
	/* it */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_IT, "Il device di registrazione non supporta i parametri attuali"},
	/* ko */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_NL, "Het opname apparaat ondersteunt de huidige geluid opties niet"},
	/* pl */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_PL, "Urz±dzenie zapisu nie obs≥uguje obecnych parametrÛw dºwiÍku"},
	/* ru */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_RU, "The recording device doesn't support current sound parameters"},
	/* sv */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_SV, "Inspelningsenheten stˆder inte aktuella ljudinst‰llningar"},
	/* tr */ {IDGS_RECORD_NOT_SUPPORT_SOUND_PAR_TR, "Kay˝t ayg˝t˝ geÁerli ses parametrelerini desteklemiyor"},
#endif
	
	/* sound.c */
	/* en */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE,    N_("Sound buffer overflow (cycle based)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_DA, "Lydbuffer overl¯b (cykelbaseret)"},
	/* de */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_DE, "Sound Puffer ‹berlauf (Zyklus basiert)"},
	/* es */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_ES, "Desbordamiento Buffer sonido (Base ciclos)"},
	/* fr */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_FR, "Erreur de dÈpassement de tampon son (cycle based)"},
	/* hu */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_HU, "Hangpuffer t˙lcsordul·s (ciklus alap˙)"},
	/* it */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_IT, "Overflow del buffer audio (cycle based)"},
	/* ko */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_NL, "Geluidsbuffer overloop (cyclus gebaseerd)"},
	/* pl */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_PL, "Przepe≥niony bufor dºwiÍku (cykliczny)"},
	/* ru */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_RU, "Sound buffer overflow (cycle based)"},
	/* sv */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_SV, "Fˆr mycket data i ljudbufferten (cykelbaserad)"},
	/* tr */ {IDGS_SOUND_BUFFER_OVERFLOW_CYCLE_TR, "Ses arabellek ta˛mas˝ (cycle bazl˝)"},
#endif
	
	/* sound.c */
	/* en */ {IDGS_SOUND_BUFFER_OVERFLOW,    N_("Sound buffer overflow.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SOUND_BUFFER_OVERFLOW_DA, "Lydbuffer overl¯b."},
	/* de */ {IDGS_SOUND_BUFFER_OVERFLOW_DE, "Sound Puffer ‹berlauf."},
	/* es */ {IDGS_SOUND_BUFFER_OVERFLOW_ES, "Desbordamiento Buffer sonido"},
	/* fr */ {IDGS_SOUND_BUFFER_OVERFLOW_FR, "Erreur de dÈpassement de tampon son."},
	/* hu */ {IDGS_SOUND_BUFFER_OVERFLOW_HU, "Hangpuffer t˙lcsordul·s."},
	/* it */ {IDGS_SOUND_BUFFER_OVERFLOW_IT, "Overflow del buffer audio."},
	/* ko */ {IDGS_SOUND_BUFFER_OVERFLOW_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SOUND_BUFFER_OVERFLOW_NL, "Geluidsbuffer overloop."},
	/* pl */ {IDGS_SOUND_BUFFER_OVERFLOW_PL, "Przepe≥niony bufor dºwiÍku."},
	/* ru */ {IDGS_SOUND_BUFFER_OVERFLOW_RU, "Sound buffer overflow."},
	/* sv */ {IDGS_SOUND_BUFFER_OVERFLOW_SV, "Fˆr mycket data i ljudbufferten."},
	/* tr */ {IDGS_SOUND_BUFFER_OVERFLOW_TR, "Ses arabellek ta˛mas˝."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_CANNOT_FLUSH,    N_("cannot flush.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_FLUSH_DA, "Kan ikke t¯mme."},
	/* de */ {IDGS_CANNOT_FLUSH_DE, "Entleerung nicht mˆglich."},
	/* es */ {IDGS_CANNOT_FLUSH_ES, "cannot flush."},
	/* fr */ {IDGS_CANNOT_FLUSH_FR, "impossible de vider."},
	/* hu */ {IDGS_CANNOT_FLUSH_HU, "nem siker¸lt ¸rÌteni a puffert."},
	/* it */ {IDGS_CANNOT_FLUSH_IT, "non Ë possibile svuotare."},
	/* ko */ {IDGS_CANNOT_FLUSH_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_FLUSH_NL, "kan niet spoelen."},
	/* pl */ {IDGS_CANNOT_FLUSH_PL, "Nie moøna oprÛøniÊ."},
	/* ru */ {IDGS_CANNOT_FLUSH_RU, "cannot flush."},
	/* sv */ {IDGS_CANNOT_FLUSH_SV, "kan inte tˆmma."},
	/* tr */ {IDGS_CANNOT_FLUSH_TR, "temizlenemedi."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_FRAGMENT_PROBLEMS,    N_("fragment problems.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_FRAGMENT_PROBLEMS_DA, "Fragmentproblem."},
	/* de */ {IDGS_FRAGMENT_PROBLEMS_DE, "Fragmentierungsproblem."},
	/* es */ {IDGS_FRAGMENT_PROBLEMS_ES, "Problema de fragmentaciÛn"},
	/* fr */ {IDGS_FRAGMENT_PROBLEMS_FR, "problËmes de fragments."},
	/* hu */ {IDGS_FRAGMENT_PROBLEMS_HU, "tˆredÈkrÈsz problÈm·k."},
	/* it */ {IDGS_FRAGMENT_PROBLEMS_IT, "problemi di frammentazione."},
	/* ko */ {IDGS_FRAGMENT_PROBLEMS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_FRAGMENT_PROBLEMS_NL, "fragment problemen."},
	/* pl */ {IDGS_FRAGMENT_PROBLEMS_PL, "Problemy z fragmentem"},
	/* ru */ {IDGS_FRAGMENT_PROBLEMS_RU, "fragment problems."},
	/* sv */ {IDGS_FRAGMENT_PROBLEMS_SV, "fragmentprogram."},
	/* tr */ {IDGS_FRAGMENT_PROBLEMS_TR, "parÁalara ay˝rma problemi."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_RUNNING_TOO_SLOW,    N_("running too slow.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_RUNNING_TOO_SLOW_DA, "K¯rer for langsomt."},
	/* de */ {IDGS_RUNNING_TOO_SLOW_DE, "Ablauf zu langsam."},
	/* es */ {IDGS_RUNNING_TOO_SLOW_ES, "Funciona demasiado lento."},
	/* fr */ {IDGS_RUNNING_TOO_SLOW_FR, "exÈcution trop lente."},
	/* hu */ {IDGS_RUNNING_TOO_SLOW_HU, "t˙l lassan megy."},
	/* it */ {IDGS_RUNNING_TOO_SLOW_IT, "esecuzione troppo lenta."},
	/* ko */ {IDGS_RUNNING_TOO_SLOW_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_RUNNING_TOO_SLOW_NL, "draait te langzaam."},
	/* pl */ {IDGS_RUNNING_TOO_SLOW_PL, "dzia≥a za wolno."},
	/* ru */ {IDGS_RUNNING_TOO_SLOW_RU, "running too slow."},
	/* sv */ {IDGS_RUNNING_TOO_SLOW_SV, "gÂr fˆr lÂngsamt."},
	/* tr */ {IDGS_RUNNING_TOO_SLOW_TR, "Áok yava˛ Áal˝˛˝yor."},
#endif
	
	/* sound.c */
	/* en */ {IDGS_STORE_SOUNDDEVICE_FAILED,    N_("store to sounddevice failed.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_STORE_SOUNDDEVICE_FAILED_DA, "skrivning til lydenhed fejlede."},
	/* de */ {IDGS_STORE_SOUNDDEVICE_FAILED_DE, "Speichern auf Sound Ger‰t ist fehlgeschlagen."},
	/* es */ {IDGS_STORE_SOUNDDEVICE_FAILED_ES, "Almacenamiento en perifÈrico de sonido fallido"},
	/* fr */ {IDGS_STORE_SOUNDDEVICE_FAILED_FR, "erreur d'enregistrement sur le pÈriphÈrique son."},
	/* hu */ {IDGS_STORE_SOUNDDEVICE_FAILED_HU, "a hangeszkˆzˆn tˆrtÈnı t·rol·s nem siker¸lt."},
	/* it */ {IDGS_STORE_SOUNDDEVICE_FAILED_IT, "memorizzazione sulla scheda audio fallita."},
	/* ko */ {IDGS_STORE_SOUNDDEVICE_FAILED_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_STORE_SOUNDDEVICE_FAILED_NL, "opslag naar geluidsapparaat is mislukt."},
	/* pl */ {IDGS_STORE_SOUNDDEVICE_FAILED_PL, "zapis do urz±dzenia dºwiÍku nie powiÛd≥ siÍ"},
	/* ru */ {IDGS_STORE_SOUNDDEVICE_FAILED_RU, "store to sounddevice failed."},
	/* sv */ {IDGS_STORE_SOUNDDEVICE_FAILED_SV, "misslyckades spara i ljudenheten."},
	/* tr */ {IDGS_STORE_SOUNDDEVICE_FAILED_TR, "ses ayg˝t˝na saklama ba˛ar˝s˝z oldu."},
#endif
	
	/* c64/c64export.c */
	/* en */ {IDGS_RESOURCE_S_BLOCKED_BY_S,    N_("Resource %s blocked by %s.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_RESOURCE_S_BLOCKED_BY_S_DA, "Resoursen %s er blokeret af %s."},
	/* de */ {IDGS_RESOURCE_S_BLOCKED_BY_S_DE, "Resource %s wird von %s blockiert."},
	/* es */ {IDGS_RESOURCE_S_BLOCKED_BY_S_ES, "Recursos %s bloqueados por %s."},
	/* fr */ {IDGS_RESOURCE_S_BLOCKED_BY_S_FR, "La ressource %s est bloquÈe par %s."},
	/* hu */ {IDGS_RESOURCE_S_BLOCKED_BY_S_HU, "A %s erıforr·st %s fogja."},
	/* it */ {IDGS_RESOURCE_S_BLOCKED_BY_S_IT, "Risorsa %s bloccata da %s."},
	/* ko */ {IDGS_RESOURCE_S_BLOCKED_BY_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_RESOURCE_S_BLOCKED_BY_S_NL, "Bron %s geblokeerd door %s."},
	/* pl */ {IDGS_RESOURCE_S_BLOCKED_BY_S_PL, "ZasÛb %s blokowany przez %s."},
	/* ru */ {IDGS_RESOURCE_S_BLOCKED_BY_S_RU, "Resource %s blocked by %s."},
	/* sv */ {IDGS_RESOURCE_S_BLOCKED_BY_S_SV, "Resursen %s blockeras av %s."},
	/* tr */ {IDGS_RESOURCE_S_BLOCKED_BY_S_TR, "Kaynak %s, %s taraf˝ndan blokland˝."},
#endif
	
#ifdef HAVE_NETWORK
	/* network.c */
	/* en */ {IDGS_TESTING_BEST_FRAME_DELAY,    N_("Testing best frame delay...")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_TESTING_BEST_FRAME_DELAY_DA, "Tester bedste billed-forsinkelse..."},
	/* de */ {IDGS_TESTING_BEST_FRAME_DELAY_DE, "Teste optimale Framerate..."},
	/* es */ {IDGS_TESTING_BEST_FRAME_DELAY_ES, "Probando mejor demora de cuadro..."},
	/* fr */ {IDGS_TESTING_BEST_FRAME_DELAY_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_TESTING_BEST_FRAME_DELAY_HU, ""},  /* fuzzy */
	/* it */ {IDGS_TESTING_BEST_FRAME_DELAY_IT, "Rileva il miglior ritardo tra frame..."},
	/* ko */ {IDGS_TESTING_BEST_FRAME_DELAY_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_TESTING_BEST_FRAME_DELAY_NL, "Beste framevertraging aan het testen..."},
	/* pl */ {IDGS_TESTING_BEST_FRAME_DELAY_PL, "Sprawdzam najlepsze opÛºnienie klatek..."},
	/* ru */ {IDGS_TESTING_BEST_FRAME_DELAY_RU, "Testing best frame delay..."},
	/* sv */ {IDGS_TESTING_BEST_FRAME_DELAY_SV, "Testar b‰sta ramfˆrdrˆjning..."},
	/* tr */ {IDGS_TESTING_BEST_FRAME_DELAY_TR, "En iyi frame bekleme s¸resi test ediliyor..."},
#endif
	
	/* network.c */
	/* en */ {IDGS_USING_D_FRAMES_DELAY,    N_("Using %d frames delay.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_USING_D_FRAMES_DELAY_DA, "Bruger %d billeders forsinkelse."},
	/* de */ {IDGS_USING_D_FRAMES_DELAY_DE, "Benutze %d Frameverzˆgerung."},
	/* es */ {IDGS_USING_D_FRAMES_DELAY_ES, "Usando %d cuadros de demora."},
	/* fr */ {IDGS_USING_D_FRAMES_DELAY_FR, "Utilisation d'un dÈlai de %d images."},
	/* hu */ {IDGS_USING_D_FRAMES_DELAY_HU, "%d kÈpkocka kÈsleltetÈs haszn·lata."},
	/* it */ {IDGS_USING_D_FRAMES_DELAY_IT, "Utilizzo %d frame di ritardo."},
	/* ko */ {IDGS_USING_D_FRAMES_DELAY_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_USING_D_FRAMES_DELAY_NL, "%d frames vertraging in gebruik."},
	/* pl */ {IDGS_USING_D_FRAMES_DELAY_PL, "Uøywam opÛºnienia klatek %d."},
	/* ru */ {IDGS_USING_D_FRAMES_DELAY_RU, "Using %d frames delay."},
	/* sv */ {IDGS_USING_D_FRAMES_DELAY_SV, "Anv‰nder %d ramars fˆrdrˆjning."},
	/* tr */ {IDGS_USING_D_FRAMES_DELAY_TR, "%d frame bekleme s¸resi kullan˝l˝yor."},
#endif
	
	/* network.c */
	/* en */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER,    N_("Cannot load snapshot file for transfer")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_DA, "Kunne ikke indlÊse snapshot til overf¯rsel."},
	/* de */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_DE, "Kann Snapshot Datei f¸r Transfer nicht laden"},
	/* es */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_ES, "No puedo cargar fichero volcado memoria para trasferencia"},
	/* fr */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_FR, "Impossible de charger l'instantanÈ pour le transfer"},
	/* hu */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_HU, "Nem siker¸lt az ·tk¸ldendı pillanatkÈp f·jlt betˆlteni"},
	/* it */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_IT, "Non Ë possibile caricare il file di snapshot per il trasferimento"},
	/* ko */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_NL, "Kan het momentopnamebestand voor versturen niet laden"},
	/* pl */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_PL, "Nie moøna wczytaÊ pliku zrzutu do transferu"},
	/* ru */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_RU, "Cannot load snapshot file for transfer"},
	/* sv */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_SV, "Kan inte l‰sa in ˆgonblicksbildfil fˆr ˆverfˆring."},
	/* tr */ {IDGS_CANNOT_LOAD_SNAPSHOT_TRANSFER_TR, "Transfer iÁin anl˝k gˆr¸nt¸ dosyas˝ y¸klenemedi"},
#endif
	
	/* network.c */
	/* en */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT,    N_("Sending snapshot to client...")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_DA, "Sender snapshot til klient..."},
	/* de */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_DE, "Sende Snapshot zu Client..."},
	/* es */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_ES, "Remitiendo volcado memoria a cliente..."},
	/* fr */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_HU, ""},  /* fuzzy */
	/* it */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_IT, "Invio snapshot al client in corso..."},
	/* ko */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_NL, "Momentopname wordt naar de andere computer verstuurd..."},
	/* pl */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_PL, "Wysy≥am zrzut do klienta..."},
	/* ru */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_RU, "Sending snapshot to client..."},
	/* sv */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_SV, "S‰nder ˆgonblicksbild till klient..."},
	/* tr */ {IDGS_SENDING_SNAPSHOT_TO_CLIENT_TR, "Anl˝k gˆr¸nt¸ dosyas˝ istemciye gˆnderiliyor..."},
#endif
	
	/* network.c */
	/* en */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT,    N_("Cannot send snapshot to client")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_DA, "Kunne ikke sende snapshot til klient"},
	/* de */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_DE, "Kann Snapshot Datei nicht senden"},
	/* es */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_ES, "No puedo remitir volcado memoria a cliente"},
	/* fr */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_FR, "Impossible d'envoyer l'instantanÈ au client"},
	/* hu */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_HU, "Nem siker¸lt pillanatkÈpet elk¸ldeni a klienshez"},
	/* it */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_IT, "Non Ë possibile inviare lo snapshot al client"},
	/* ko */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_NL, "Kan de momentopname niet naar de andere computer versturen"},
	/* pl */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_PL, "Nie moøna wys≥aÊ zrzutu do klienta"},
	/* ru */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_RU, "Cannot send snapshot to client"},
	/* sv */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_SV, "Kan inte s‰nda ˆgonblicksbild till klient"},
	/* tr */ {IDGS_CANNOT_SEND_SNAPSHOT_TO_CLIENT_TR, "Anl˝k gˆr¸nt¸ dosyas˝ istemciye gˆnderilemedi"},
#endif
	
	/* network.c */
	/* en */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S,    N_("Cannot create snapshot file %s")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_DA, "Kunne ikke oprette snapshot-fil %s"},
	/* de */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_DE, "Kann Snapshot Datei `%s' nicht erzeugen"},
	/* es */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_ES, "No puedo crear fichero volcado memoria %s"},
	/* fr */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_FR, "Impossible de crÈer l'instantanÈ %s"},
	/* hu */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_HU, "Nem siker¸lt a pillanatkÈpf·jlt lÈtrehozni (%s)"},
	/* it */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_IT, "Non Ë possibile creare il file di snapshot %s"},
	/* ko */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_NL, "Kan het momentopnamebestand %s niet maken"},
	/* pl */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_PL, "Nie moøna utworzyÊ pliku zrzutu %s"},
	/* ru */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_RU, "Cannot create snapshot file %s"},
	/* sv */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_SV, "Kan inte skapa ˆgonblicksbildfil %s"},
	/* tr */ {IDGS_CANNOT_CREATE_SNAPSHOT_FILE_S_TR, "Anl˝k gˆr¸nt¸ dosyas˝ %s yarat˝lamad˝"},
#endif
	
	/* network.c */
	/* en */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S,    N_("Cannot open snapshot file %s")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_DA, "Kunne ikke Âbne snapshot-fil %s"},
	/* de */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_DE, "Kann Snapshot Datei `%s' nicht ˆffnen."},
	/* es */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_ES, "No puedo abrir fichero volcaco memoria %s"},
	/* fr */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_FR, "Impossible d'ouvrir le fichier %s"},
	/* hu */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_HU, "Nem siker¸lt a pillanatkÈpf·jlt megnyitni (%s)"},
	/* it */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_IT, "Non Ë possibile aprire il file di snapshot %s"},
	/* ko */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_NL, "Kan het momentopnamebestand %s niet openen"},
	/* pl */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_PL, "Nie moøna otworzyÊ pliku zrzutu %s"},
	/* ru */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_RU, "Cannot open snapshot file %s"},
	/* sv */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_SV, "Kan inte ˆppna ˆgonblicksbildfil %s"},
	/* tr */ {IDGS_CANNOT_OPEN_SNAPSHOT_FILE_S_TR, "Anl˝k gˆr¸nt¸ dosyas˝ %s aÁ˝lamad˝"},
#endif
	
	/* network.c */
	/* en */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT,    N_("Server is waiting for a client...")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_DA, "Server venter pÂ en klient..."},
	/* de */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_DE, "Server wartet auf Client..."},
	/* es */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_ES, "El servidor est· esperando al cliente..."},
	/* fr */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_HU, ""},  /* fuzzy */
	/* it */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_IT, "Il server Ë in attesa di un client..."},
	/* ko */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_NL, "De server wacht op de andere computer..."},
	/* pl */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_PL, "Serwer czeka na klienta..."},
	/* ru */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_RU, "Server is waiting for a client..."},
	/* sv */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_SV, "Servern v‰ntar pÂ en klient..."},
	/* tr */ {IDGS_SERVER_IS_WAITING_FOR_CLIENT_TR, "Sunucu bir istemcinin balanmas˝ iÁin bekliyor..."},
#endif
	
	/* network.c */
	/* en */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT,    N_("Cannot create snapshot file. Select different history directory!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_DA, "Kunne ikke oprette snapshot-fil. VÊlg et andet historik-katalog!"},
	/* de */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_DE, "Kann Snapshot Datei nicht erzeugen. Verwende ein anderes Verzeichnis!"},
	/* es */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_ES, "No puedo crear fichero volcado memoria. °Seleccionar diferente directorio historico!"},
	/* fr */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_FR, "Impossible de crÈer le fichier d'instantanÈ. SÈlectionnez un rÈpertoire d'historique diffÈrent"},
	/* hu */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_HU, "Nem siker¸lt pillanatkÈp f·jlt lÈtrehozni. KÈrem v·lasszon m·s kˆnyvt·rat!"},
	/* it */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_IT, "Non Ë possibile creare il file di snapshot. Seleziona una directory diversa per la cronologia."},
	/* ko */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_NL, "Kan het momentopnamebestand niet maken. Selecteer een andere geschiedenisdirectory!"},
	/* pl */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_PL, "Nie moøna utworzyÊ pliku zrzutu. Wybierz inny katalog historii!"},
	/* ru */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_RU, "Cannot create snapshot file. Select different history directory!"},
	/* sv */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_SV, "Kan inte skapa ˆgonblicksbildfil. V‰lj en annan historikkatalog!"},
	/* tr */ {IDGS_CANNOT_CREATE_SNAPSHOT_S_SELECT_TR, "Anl˝k gˆr¸nt¸ dosyas˝ yarat˝lamad˝. Farkl˝ bir tarihÁe dizini seÁin!"},
#endif
	
	/* network.c */
	/* en */ {IDGS_CANNOT_RESOLVE_S,    N_("Cannot resolve %s")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_RESOLVE_S_DA, "Kan ikke opslÂ %s"},
	/* de */ {IDGS_CANNOT_RESOLVE_S_DE, "Kann %s nicht auflˆsen"},
	/* es */ {IDGS_CANNOT_RESOLVE_S_ES, "No puedo resolver %s"},
	/* fr */ {IDGS_CANNOT_RESOLVE_S_FR, "Impossible de rÈsoudre %s"},
	/* hu */ {IDGS_CANNOT_RESOLVE_S_HU, "Nem siker¸lt %s-t feloldani"},
	/* it */ {IDGS_CANNOT_RESOLVE_S_IT, "Non Ë possibile risolvere %s"},
	/* ko */ {IDGS_CANNOT_RESOLVE_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_RESOLVE_S_NL, "Onbekende host %s"},
	/* pl */ {IDGS_CANNOT_RESOLVE_S_PL, "Nie moøna znaleºÊ %s"},
	/* ru */ {IDGS_CANNOT_RESOLVE_S_RU, "Cannot resolve %s"},
	/* sv */ {IDGS_CANNOT_RESOLVE_S_SV, "Kan inte slÂ upp %s"},
	/* tr */ {IDGS_CANNOT_RESOLVE_S_TR, "%s Áˆz¸lemedi"},
#endif
	
	/* network.c */
	/* en */ {IDGS_CANNOT_CONNECT_TO_S,    N_("Cannot connect to %s (no server running on port %d).")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CANNOT_CONNECT_TO_S_DA, "Kan ikke forbinde til %s (ingen server pÂ port %d)."},
	/* de */ {IDGS_CANNOT_CONNECT_TO_S_DE, "Kann zu %s nicht verbinden (Kein Server aktiv auf Port %d)."},
	/* es */ {IDGS_CANNOT_CONNECT_TO_S_ES, "No puedo conectar a  %s (Ningu˙n servidor en puerto %d)."},
	/* fr */ {IDGS_CANNOT_CONNECT_TO_S_FR, "Impossible de se connecter ‡ %s (aucun serveur sur le port %d)."},
	/* hu */ {IDGS_CANNOT_CONNECT_TO_S_HU, "Nem siker¸lt %s-hez kapcsolÛdni (a %d porton nem fut kiszolg·lÛ)"},
	/* it */ {IDGS_CANNOT_CONNECT_TO_S_IT, "Non Ë possibile connettersi a %s (nessun server Ë attivo sulla porta %d)."},
	/* ko */ {IDGS_CANNOT_CONNECT_TO_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CANNOT_CONNECT_TO_S_NL, "Kan geen verbinding maken met %s (er is geen server aanwezig op poort %d)."},
	/* pl */ {IDGS_CANNOT_CONNECT_TO_S_PL, "Nie moøna pod≥±czyÊ do %s (na porcie %d nie dzia≥a øaden serwer)."},
	/* ru */ {IDGS_CANNOT_CONNECT_TO_S_RU, "Cannot connect to %s (no server running on port %d)."},
	/* sv */ {IDGS_CANNOT_CONNECT_TO_S_SV, "Kan inte ansluta till %s (ingen server igÂng pÂ port %d)."},
	/* tr */ {IDGS_CANNOT_CONNECT_TO_S_TR, "%s balant˝s˝ kurulamad˝ (port %d ¸zerinde Áal˝˛an sunucu yok)."},
#endif
	
	/* network.c */
	/* en */ {IDGS_RECEIVING_SNAPSHOT_SERVER,    N_("Receiving snapshot from server...")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_RECEIVING_SNAPSHOT_SERVER_DA, "Modtager snapshot fra server..."},
	/* de */ {IDGS_RECEIVING_SNAPSHOT_SERVER_DE, "Empfange Snapshot von Server..."},
	/* es */ {IDGS_RECEIVING_SNAPSHOT_SERVER_ES, "Recibiendo volcado memoria desde el servidor..."},
	/* fr */ {IDGS_RECEIVING_SNAPSHOT_SERVER_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_RECEIVING_SNAPSHOT_SERVER_HU, ""},  /* fuzzy */
	/* it */ {IDGS_RECEIVING_SNAPSHOT_SERVER_IT, "Ricezione dello snapshot dal server in corso..."},
	/* ko */ {IDGS_RECEIVING_SNAPSHOT_SERVER_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_RECEIVING_SNAPSHOT_SERVER_NL, "Momentopname van de server wordt ontvangen..."},
	/* pl */ {IDGS_RECEIVING_SNAPSHOT_SERVER_PL, "Odbieranie zrzutu z serwera..."},
	/* ru */ {IDGS_RECEIVING_SNAPSHOT_SERVER_RU, "Receiving snapshot from server..."},
	/* sv */ {IDGS_RECEIVING_SNAPSHOT_SERVER_SV, "Tar emot ˆgoblicksbild frÂn server..."},
	/* tr */ {IDGS_RECEIVING_SNAPSHOT_SERVER_TR, "Sunucudan anl˝k gˆr¸nt¸ al˝n˝yor..."},
#endif
	
	/* network.c */
	/* en */ {IDGS_NETWORK_OUT_OF_SYNC,    N_("Network out of sync - disconnecting.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_NETWORK_OUT_OF_SYNC_DA, "NetvÊrk ude af synk - afbryder forbindelsen."},
	/* de */ {IDGS_NETWORK_OUT_OF_SYNC_DE, "Netzwerksynchronisationsproblem - Trenne Verbindung."},
	/* es */ {IDGS_NETWORK_OUT_OF_SYNC_ES, "Red fuera de sincronia - desconentando."},
	/* fr */ {IDGS_NETWORK_OUT_OF_SYNC_FR, "Le rÈseau n'est pas synchronisÈ (out of sync error). DÈconnexion."},
	/* hu */ {IDGS_NETWORK_OUT_OF_SYNC_HU, "A h·lÛzat kiesett a szinkronbÛl - szÈtkapcsolÛd·s"},
	/* it */ {IDGS_NETWORK_OUT_OF_SYNC_IT, "Rete non sincronizzata - disconnesione in corso."},
	/* ko */ {IDGS_NETWORK_OUT_OF_SYNC_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_NETWORK_OUT_OF_SYNC_NL, "Netwerk niet synchroon - verbinding wordt verbroken."},
	/* pl */ {IDGS_NETWORK_OUT_OF_SYNC_PL, "Desynchronizacja sieci - roz≥±czam."},
	/* ru */ {IDGS_NETWORK_OUT_OF_SYNC_RU, "Network out of sync - disconnecting."},
	/* sv */ {IDGS_NETWORK_OUT_OF_SYNC_SV, "N‰tverket ur synk - kopplar frÂn."},
	/* tr */ {IDGS_NETWORK_OUT_OF_SYNC_TR, "A senkronizasyonu bozuldu - balant˝ kesiliyor."},
#endif
	
	/* network.c */
	/* en */ {IDGS_REMOTE_HOST_DISCONNECTED,    N_("Remote host disconnected.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_REMOTE_HOST_DISCONNECTED_DA, "Fjernmaskine afbrudt."},
	/* de */ {IDGS_REMOTE_HOST_DISCONNECTED_DE, "Entfernter Rechner getrennt."},
	/* es */ {IDGS_REMOTE_HOST_DISCONNECTED_ES, "Host Remoto desconectado."},
	/* fr */ {IDGS_REMOTE_HOST_DISCONNECTED_FR, "L'hÙte distant s'est dÈconnectÈ."},
	/* hu */ {IDGS_REMOTE_HOST_DISCONNECTED_HU, "A t·voli sz·mÌtogÈp lekapcsolÛdott."},
	/* it */ {IDGS_REMOTE_HOST_DISCONNECTED_IT, "Host remoto disconnesso."},
	/* ko */ {IDGS_REMOTE_HOST_DISCONNECTED_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_REMOTE_HOST_DISCONNECTED_NL, "Andere computer heeft de verbinding verbroken."},
	/* pl */ {IDGS_REMOTE_HOST_DISCONNECTED_PL, "Zdalny host roz≥±czy≥ siÍ."},
	/* ru */ {IDGS_REMOTE_HOST_DISCONNECTED_RU, "Remote host disconnected."},
	/* sv */ {IDGS_REMOTE_HOST_DISCONNECTED_SV, "FrÂnkopplad frÂn fj‰rrv‰rd."},
	/* tr */ {IDGS_REMOTE_HOST_DISCONNECTED_TR, "Uzak sunucu balant˝s˝ kesildi."},
#endif
	
	/* network.c */
	/* en */ {IDGS_REMOTE_HOST_SUSPENDING,    N_("Remote host suspending...")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_REMOTE_HOST_SUSPENDING_DA, "Fjernmaskine pauser..."},
	/* de */ {IDGS_REMOTE_HOST_SUSPENDING_DE, "Entfernter Rechner angehaltedn..."},
	/* es */ {IDGS_REMOTE_HOST_SUSPENDING_ES, "Host remoto suspendido..."},
	/* fr */ {IDGS_REMOTE_HOST_SUSPENDING_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_REMOTE_HOST_SUSPENDING_HU, ""},  /* fuzzy */
	/* it */ {IDGS_REMOTE_HOST_SUSPENDING_IT, "Sospesione host remoto in corso..."},
	/* ko */ {IDGS_REMOTE_HOST_SUSPENDING_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_REMOTE_HOST_SUSPENDING_NL, "Andere computer halt de netplay..."},
	/* pl */ {IDGS_REMOTE_HOST_SUSPENDING_PL, "Zawieszenie zdalnego hosta...."},
	/* ru */ {IDGS_REMOTE_HOST_SUSPENDING_RU, "Remote host suspending..."},
	/* sv */ {IDGS_REMOTE_HOST_SUSPENDING_SV, "FJ‰rrv‰rden pausar..."},
	/* tr */ {IDGS_REMOTE_HOST_SUSPENDING_TR, "Uzak sunucu ask˝da..."},
#endif
#endif
	
	/* gfxoutputdrv/ffmpegdrv.c */
	/* en */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM,    N_("ffmpegdrv: Cannot open video stream")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_DA, "ffmpegdrv: Kan ikke Âbne video-str¯m"},
	/* de */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_DE, "ffmpegdrv: Kann video stream nicht ˆffnen"},
	/* es */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_ES, "ffmpegdrv: no puedo abrir video stream"},
	/* fr */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_FR, "ffmpegdrv: Impossible d'ouvrir le flux vidÈo"},
	/* hu */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_HU, "ffmpegdrv: Nem siker¸lt megnyitni a videÛ adatfolyamot"},
	/* it */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_IT, "ffmpegdrv: Non Ë possibile aprire il flusso video"},
	/* ko */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_NL, "ffmpegdrv: Kan de videostroom niet openen"},
	/* pl */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_PL, "ffmpegdrv: Nie moøna otworzyÊ strumienia wideo"},
	/* ru */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_RU, "ffmpegdrv: Ω’ „‘–’‚·Ô ﬁ‚⁄‡Î‚Ï “ÿ‘’ﬁ ﬂﬁ‚ﬁ⁄"},
	/* sv */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_SV, "ffmpegdrv: Kan inte ˆppna videostrˆm"},
	/* tr */ {IDGS_FFMPEG_CANNOT_OPEN_VSTREAM_TR, "ffmpegdrv: Gˆr¸nt¸ ak˝˛˝ aÁ˝lamad˝"},
#endif
	
	/* gfxoutputdrv/ffmpegdrv.c */
	/* en */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM,    N_("ffmpegdrv: Cannot open audio stream")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_DA, "ffmpegdrv: Kan ikke Âbne lyd-str¯m"},
	/* de */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_DE, "ffmpegdrv: Kann audio stream nicht ˆffnen"},
	/* es */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_ES, "ffmpegdrv: No puedo abrir audio stream"},
	/* fr */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_FR, "ffmpegdrv: Impossible d'ouvrir le flux audio"},
	/* hu */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_HU, "ffmpegdrv: Nem siker¸lt megnyitni a audiÛ adatfolyamot"},
	/* it */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_IT, "ffmpegdrv: Non Ë possibile aprire il flusso audio"},
	/* ko */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_NL, "ffmpegdrv: Kan de audiostroom niet openen"},
	/* pl */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_PL, "ffmpegdrv: Nie moøna otworzyÊ strumienia audio"},
	/* ru */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_RU, "ffmpegdrv: Ω’ „‘–’‚·Ô ﬁ‚⁄‡Î‚Ï –„‘ÿﬁ ﬂﬁ‚ﬁ⁄"},
	/* sv */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_SV, "ffmpegdrv: Kan inte ˆppna ljudstrˆm"},
	/* tr */ {IDGS_FFMPEG_CANNOT_OPEN_ASTREAM_TR, "ffmpegdrv: Ses ak˝˛˝ aÁ˝lamad˝"},
#endif
	
	/* gfxoutputdrv/ffmpegdrv.c */
	/* en */ {IDGS_FFMPEG_CANNOT_OPEN_S,    N_("ffmpegdrv: Cannot open %s")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_FFMPEG_CANNOT_OPEN_S_DA, "ffmpegdrv: Kan ikke Âbne %s"},
	/* de */ {IDGS_FFMPEG_CANNOT_OPEN_S_DE, "ffmpegdrv: ÷ffnen von %s fehlgeschlagen"},
	/* es */ {IDGS_FFMPEG_CANNOT_OPEN_S_ES, "ffmpegdrv: No puedo abrir %s"},
	/* fr */ {IDGS_FFMPEG_CANNOT_OPEN_S_FR, "ffmpegdrv: Impossible d'ouvrir %s"},
	/* hu */ {IDGS_FFMPEG_CANNOT_OPEN_S_HU, "ffmpegdrv: Nem siker¸lt megnyitni: %s"},
	/* it */ {IDGS_FFMPEG_CANNOT_OPEN_S_IT, "ffmpegdrv: Non Ë possibile aprire %s"},
	/* ko */ {IDGS_FFMPEG_CANNOT_OPEN_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_FFMPEG_CANNOT_OPEN_S_NL, "ffmpegdrv: Kan %s niet openen"},
	/* pl */ {IDGS_FFMPEG_CANNOT_OPEN_S_PL, "ffmpegdrv: Nie moøna otworzyÊ %s"},
	/* ru */ {IDGS_FFMPEG_CANNOT_OPEN_S_RU, "ffmpegdrv: Cannot open %s"},
	/* sv */ {IDGS_FFMPEG_CANNOT_OPEN_S_SV, "ffmpegdrv: Kan inte ˆppna %s"},
	/* tr */ {IDGS_FFMPEG_CANNOT_OPEN_S_TR, "ffmpegdrv: %s aÁ˝lamad˝"},
#endif
	
	/* c64/c64io.c, vic20/vic20io.c */
	/* en */ {IDGS_IO_READ_COLL_AT_X_FROM,    N_("I/O read collision at %X from ")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_IO_READ_COLL_AT_X_FROM_DA, "I/O-lÊsekollision ved %X fra "},
	/* de */ {IDGS_IO_READ_COLL_AT_X_FROM_DE, "I/O Lese Kollision bei %X von "},
	/* es */ {IDGS_IO_READ_COLL_AT_X_FROM_ES, "Entrada/Salida real colisiÛn en %X para"},
	/* fr */ {IDGS_IO_READ_COLL_AT_X_FROM_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_IO_READ_COLL_AT_X_FROM_HU, ""},  /* fuzzy */
	/* it */ {IDGS_IO_READ_COLL_AT_X_FROM_IT, "Collisione di I/O in lettura a %X da "},
	/* ko */ {IDGS_IO_READ_COLL_AT_X_FROM_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_IO_READ_COLL_AT_X_FROM_NL, "I/O lees botsing op %X van "},
	/* pl */ {IDGS_IO_READ_COLL_AT_X_FROM_PL, "Kolizja odczytu we/wy w %X z"},
	/* ru */ {IDGS_IO_READ_COLL_AT_X_FROM_RU, "I/O read collision at %X from "},
	/* sv */ {IDGS_IO_READ_COLL_AT_X_FROM_SV, "I/O-l‰skollision vid %X frÂn "},
	/* tr */ {IDGS_IO_READ_COLL_AT_X_FROM_TR, "G/« okuma Áak˝˛mas˝ %X'de "},
#endif
	
	/* c64/c64io.c, vic20/vic20io.c */
	/* en */ {IDGS_AND,    N_(" and ")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_AND_DA, " og "},
	/* de */ {IDGS_AND_DE, " und "},
	/* es */ {IDGS_AND_ES, " y "},
	/* fr */ {IDGS_AND_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_AND_HU, ""},  /* fuzzy */
	/* it */ {IDGS_AND_IT, " e "},
	/* ko */ {IDGS_AND_KO, " ±◊∏Æ∞Ì "},
	/* nl */ {IDGS_AND_NL, " en "},
	/* pl */ {IDGS_AND_PL, "i"},
	/* ru */ {IDGS_AND_RU, "ÿ"},
	/* sv */ {IDGS_AND_SV, " och "},
	/* tr */ {IDGS_AND_TR, " ve "},
#endif
	
	/* c64/c64io.c, vic20/vic20io.c */
	/* en */ {IDGS_ALL_DEVICES_DETACHED,    N_(".\nAll the named devices will be detached.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ALL_DEVICES_DETACHED_DA, ".\nAlle de navngivne enheder vil blive frakoblet."},
	/* de */ {IDGS_ALL_DEVICES_DETACHED_DE, ".\nAlle genannten Ger‰te werden entfernt."},
	/* es */ {IDGS_ALL_DEVICES_DETACHED_ES, ".\nTodos los perifÈricos nombrados se desconectar·n."},
	/* fr */ {IDGS_ALL_DEVICES_DETACHED_FR, ".\nTous les pÈriphÈriques nommÈs vont Ítre dÈtachÈs."},
	/* hu */ {IDGS_ALL_DEVICES_DETACHED_HU, ".\nMinden megnevezett eszkˆz le lesz v·lasztva."},
	/* it */ {IDGS_ALL_DEVICES_DETACHED_IT, ".\nTutti i device specificati sarranno rimossi."},
	/* ko */ {IDGS_ALL_DEVICES_DETACHED_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ALL_DEVICES_DETACHED_NL, ".\nAlle genoemde apparaten zullen worden ontkoppeld."},
	/* pl */ {IDGS_ALL_DEVICES_DETACHED_PL, ".\nWszystkie wymienione urz±dzenia zostan± odmontowane."},
	/* ru */ {IDGS_ALL_DEVICES_DETACHED_RU, ".\nAll the named devices will be detached."},
	/* sv */ {IDGS_ALL_DEVICES_DETACHED_SV, ".\nAlla namngivna enheter kommer kopplas frÂn."},
	/* tr */ {IDGS_ALL_DEVICES_DETACHED_TR, ".\nT¸m isimlendirilmi˛ ayg˝tlar Á˝kart˝lacakt˝r."},
#endif
	
	/* c64/c64io.c, vic20/vic20io.c */
	/* en */ {IDGS_ALL_DEVICES_EXCEPT,    N_(".\nAll devices except ")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ALL_DEVICES_EXCEPT_DA, ".\nAlle enheder undtagen "},
	/* de */ {IDGS_ALL_DEVICES_EXCEPT_DE, ".\nAlle Ger‰te auﬂer "},
	/* es */ {IDGS_ALL_DEVICES_EXCEPT_ES, ".\nTodos los perifÈricos excepto"},
	/* fr */ {IDGS_ALL_DEVICES_EXCEPT_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ALL_DEVICES_EXCEPT_HU, ""},  /* fuzzy */
	/* it */ {IDGS_ALL_DEVICES_EXCEPT_IT, ".\nTutti i device tranne "},
	/* ko */ {IDGS_ALL_DEVICES_EXCEPT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ALL_DEVICES_EXCEPT_NL, ".\nAlle apparaten behalve "},
	/* pl */ {IDGS_ALL_DEVICES_EXCEPT_PL, ".\nWszystkie urz±dzenia, prÛcz"},
	/* ru */ {IDGS_ALL_DEVICES_EXCEPT_RU, ".\nAll devices except "},
	/* sv */ {IDGS_ALL_DEVICES_EXCEPT_SV, ".\nAlla enheter fˆrutom "},
	/* tr */ {IDGS_ALL_DEVICES_EXCEPT_TR, ".\nBunlar hariÁ t¸m cihazlar "},
#endif
	
	/* c64/c64io.c, vic20/vic20io.c */
	/* en */ {IDGS_WILL_BE_DETACHED,    N_(" will be detached.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_WILL_BE_DETACHED_DA, " vil blive frakoblet."},
	/* de */ {IDGS_WILL_BE_DETACHED_DE, " werden entfernt."},
	/* es */ {IDGS_WILL_BE_DETACHED_ES, "se desconectar·n"},
	/* fr */ {IDGS_WILL_BE_DETACHED_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_WILL_BE_DETACHED_HU, ""},  /* fuzzy */
	/* it */ {IDGS_WILL_BE_DETACHED_IT, "sarranno rimossi."},
	/* ko */ {IDGS_WILL_BE_DETACHED_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_WILL_BE_DETACHED_NL, " zullen worden ontkoppeld."},
	/* pl */ {IDGS_WILL_BE_DETACHED_PL, " zostanie roz≥±czone."},
	/* ru */ {IDGS_WILL_BE_DETACHED_RU, ""},  /* fuzzy */
	/* sv */ {IDGS_WILL_BE_DETACHED_SV, " kommer kopplas frÂn."},
	/* tr */ {IDGS_WILL_BE_DETACHED_TR, " haricindeki t¸m cihazlar Á˝kart˝lacakt˝r."},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDGS_NO_FILENAME,    N_("No filename!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_NO_FILENAME_DA, "Intet filnavn!"},
	/* de */ {IDGS_NO_FILENAME_DE, "Dateiname fehlt!"},
	/* es */ {IDGS_NO_FILENAME_ES, "°Sin nombre de fichero!"},
	/* fr */ {IDGS_NO_FILENAME_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_NO_FILENAME_HU, "Nincs f·jlnÈv!"},
	/* it */ {IDGS_NO_FILENAME_IT, "Nessun nome file!"},
	/* ko */ {IDGS_NO_FILENAME_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_NO_FILENAME_NL, "Geen bestandsnaam!"},
	/* pl */ {IDGS_NO_FILENAME_PL, "Brak nazwy pliku!"},
	/* ru */ {IDGS_NO_FILENAME_RU, "Ω’‚ ÿ‹’›ÿ ‰–Ÿ€–!"},
	/* sv */ {IDGS_NO_FILENAME_SV, "Filnamn saknas!"},
	/* tr */ {IDGS_NO_FILENAME_TR, "Dosya ismi yok!"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDGS_ILLEGAL_FILENAME,    N_("Illegal filename!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ILLEGAL_FILENAME_DA, "Ugyldigt filnavn!"},
	/* de */ {IDGS_ILLEGAL_FILENAME_DE, "Ung¸ltiger Dateiname!"},
	/* es */ {IDGS_ILLEGAL_FILENAME_ES, "°Nombre fichero ilegal!"},
	/* fr */ {IDGS_ILLEGAL_FILENAME_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ILLEGAL_FILENAME_HU, "…rvÈnytelen f·jlnÈv!"},
	/* it */ {IDGS_ILLEGAL_FILENAME_IT, "Nome file non valido!"},
	/* ko */ {IDGS_ILLEGAL_FILENAME_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ILLEGAL_FILENAME_NL, "Bestandsnaam ongeldig!"},
	/* pl */ {IDGS_ILLEGAL_FILENAME_PL, "Z≥a nazwa pliku!"},
	/* ru */ {IDGS_ILLEGAL_FILENAME_RU, "Illegal filename!"},
	/* sv */ {IDGS_ILLEGAL_FILENAME_SV, "Ogiltigt filnamn!"},
	/* tr */ {IDGS_ILLEGAL_FILENAME_TR, "Kural d˝˛˝ dosya ismi!"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDGS_ERROR_CREATING_FILE_S,    N_("Error creating file %s!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ERROR_CREATING_FILE_S_DA, "Fejl under oprettelse af filen %s!"},
	/* de */ {IDGS_ERROR_CREATING_FILE_S_DE, "Fehler beim Schreiben: %s."},
	/* es */ {IDGS_ERROR_CREATING_FILE_S_ES, "Error creando fichero %s!"},
	/* fr */ {IDGS_ERROR_CREATING_FILE_S_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ERROR_CREATING_FILE_S_HU, "Hiba %s f·jl lÈtrehoz·sa kˆzben!"},
	/* it */ {IDGS_ERROR_CREATING_FILE_S_IT, "Errore durante la creazione del file %s!"},
	/* ko */ {IDGS_ERROR_CREATING_FILE_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ERROR_CREATING_FILE_S_NL, "Fout bij het maken van bestand %s!"},
	/* pl */ {IDGS_ERROR_CREATING_FILE_S_PL, "B≥±d tworzenia pliku %s!"},
	/* ru */ {IDGS_ERROR_CREATING_FILE_S_RU, "Error creating file %s!"},
	/* sv */ {IDGS_ERROR_CREATING_FILE_S_SV, "Fel n‰r filen \"%s\" skulle skapas!"},
	/* tr */ {IDGS_ERROR_CREATING_FILE_S_TR, "%s dosyas˝ yarat˝l˝rken hata olu˛tu!"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDGS_ERROR_WRITING_TO_FILE_S,    N_("Error writing to file %s!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ERROR_WRITING_TO_FILE_S_DA, "Fejl ved skrivning til filen %s!"},
	/* de */ {IDGS_ERROR_WRITING_TO_FILE_S_DE, "Fehler bei Schreibzugriff: %s!"},
	/* es */ {IDGS_ERROR_WRITING_TO_FILE_S_ES, "Error grabando fichero %s!"},
	/* fr */ {IDGS_ERROR_WRITING_TO_FILE_S_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ERROR_WRITING_TO_FILE_S_HU, "Hiba %s f·jlba Ìr·s kˆzben!"},
	/* it */ {IDGS_ERROR_WRITING_TO_FILE_S_IT, "Errore durante la scrittura sul file %s!"},
	/* ko */ {IDGS_ERROR_WRITING_TO_FILE_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ERROR_WRITING_TO_FILE_S_NL, "Fout bij het schrijven naar bestand %s!"},
	/* pl */ {IDGS_ERROR_WRITING_TO_FILE_S_PL, "B≥±d zapisu do pliku %s!"},
	/* ru */ {IDGS_ERROR_WRITING_TO_FILE_S_RU, "Error writing to file %s!"},
	/* sv */ {IDGS_ERROR_WRITING_TO_FILE_S_SV, "Fel vid skrivning till filen %s!"},
	/* tr */ {IDGS_ERROR_WRITING_TO_FILE_S_TR, "%s dosyas˝na yaz˝l˝rken hata olu˛tu!"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDGS_DTV_ROM_CREATED,    N_("DTV ROM image created successfully")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DTV_ROM_CREATED_DA, "DTV-ROM-image oprettet med success"},
	/* de */ {IDGS_DTV_ROM_CREATED_DE, "DTV ROM Image erfolgreich erzeugt"},
	/* es */ {IDGS_DTV_ROM_CREATED_ES, "Imagen DTV ROM creada con Èxito"},
	/* fr */ {IDGS_DTV_ROM_CREATED_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_DTV_ROM_CREATED_HU, "DTV ROM kÈpm·s sikeresen lÈtrehozva"},
	/* it */ {IDGS_DTV_ROM_CREATED_IT, "Immagine ROM DTV creata con successo"},
	/* ko */ {IDGS_DTV_ROM_CREATED_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_DTV_ROM_CREATED_NL, "DTV ROM bestand gemaakt!"},
	/* pl */ {IDGS_DTV_ROM_CREATED_PL, "Z powodzeniem utworzono obraz ROM DTV"},
	/* ru */ {IDGS_DTV_ROM_CREATED_RU, "æ—‡–◊ DTV ROM ·ﬁ◊‘–› „·ﬂ’Ë›ﬁ"},
	/* sv */ {IDGS_DTV_ROM_CREATED_SV, "DTV-ROM-avbildning skapades framgÂngsrikt"},
	/* tr */ {IDGS_DTV_ROM_CREATED_TR, "DTV ROM imaj˝ ba˛ar˝yla olu˛turuldu"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_TYPE,    N_("Type")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_TYPE_DA, "Type"},
	/* de */ {IDGS_TYPE_DE, "Typ"},
	/* es */ {IDGS_TYPE_ES, "Tipo"},
	/* fr */ {IDGS_TYPE_FR, "type"},
	/* hu */ {IDGS_TYPE_HU, "TÌpus"},
	/* it */ {IDGS_TYPE_IT, "Tipo"},
	/* ko */ {IDGS_TYPE_KO, "¡æ∑˘"},
	/* nl */ {IDGS_TYPE_NL, "Soort"},
	/* pl */ {IDGS_TYPE_PL, "Typ"},
	/* ru */ {IDGS_TYPE_RU, "Type"},
	/* sv */ {IDGS_TYPE_SV, "Typ"},
	/* tr */ {IDGS_TYPE_TR, "Tip"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_COMMAND_S_UNKNOWN,    N_("Command `%s' unknown.\n")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_COMMAND_S_UNKNOWN_DA, "Ukendt kommando \"%s\".\n"},
	/* de */ {IDGS_COMMAND_S_UNKNOWN_DE, "Kommand `%s' ist unbekannt.\n"},
	/* es */ {IDGS_COMMAND_S_UNKNOWN_ES, "Comando `%s' desconocido.\n"},
	/* fr */ {IDGS_COMMAND_S_UNKNOWN_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_COMMAND_S_UNKNOWN_HU, "`%s' parancs ismeretlen.\n"},
	/* it */ {IDGS_COMMAND_S_UNKNOWN_IT, "Comando `%s' sconosciuto.\n"},
	/* ko */ {IDGS_COMMAND_S_UNKNOWN_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_COMMAND_S_UNKNOWN_NL, "Commando %s' is onbekent.\n"},
	/* pl */ {IDGS_COMMAND_S_UNKNOWN_PL, "Polecenie `%s' nieznane.\n"},
	/* ru */ {IDGS_COMMAND_S_UNKNOWN_RU, "Command `%s' unknown.\n"},
	/* sv */ {IDGS_COMMAND_S_UNKNOWN_SV, "Kommandot \"%s\" ‰r ok‰nt.\n"},
	/* tr */ {IDGS_COMMAND_S_UNKNOWN_TR, "`%s' komutu bilinmiyor.\n"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_NO_HELP_AVAILABLE_FOR_S,    N_("No help available for `%s'\n")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_NO_HELP_AVAILABLE_FOR_S_DA, "Ingen hjÊlp tilgÊngelig for \"%s\"\n"},
	/* de */ {IDGS_NO_HELP_AVAILABLE_FOR_S_DE, "Es ist keine Hilfe f¸r `%s' verf¸gbar\n"},
	/* es */ {IDGS_NO_HELP_AVAILABLE_FOR_S_ES, "Sin ayuda disponible para `%s'\n"},
	/* fr */ {IDGS_NO_HELP_AVAILABLE_FOR_S_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_NO_HELP_AVAILABLE_FOR_S_HU, "Nincs s˙gÛ a `%s' parancshoz\n"},
	/* it */ {IDGS_NO_HELP_AVAILABLE_FOR_S_IT, "Nessun help disponibile per `%s'\n"},
	/* ko */ {IDGS_NO_HELP_AVAILABLE_FOR_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_NO_HELP_AVAILABLE_FOR_S_NL, "Geen help beschikbaar voor `%s'\n"},
	/* pl */ {IDGS_NO_HELP_AVAILABLE_FOR_S_PL, "Pomoc dla '%s' niedostÍpna\n"},
	/* ru */ {IDGS_NO_HELP_AVAILABLE_FOR_S_RU, "No help available for `%s'\n"},
	/* sv */ {IDGS_NO_HELP_AVAILABLE_FOR_S_SV, "Hj‰lp saknas fˆr \"%s\"\n"},
	/* tr */ {IDGS_NO_HELP_AVAILABLE_FOR_S_TR, "`%s' iÁin mevcut bir yard˝m metni yok\n"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_SYNTAX_S_S,    N_("\nSyntax: %s %s\n")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SYNTAX_S_S_DA, "\nSyntax: %s %s\n"},
	/* de */ {IDGS_SYNTAX_S_S_DE, "\nSyntax: %s %s\n"},
	/* es */ {IDGS_SYNTAX_S_S_ES, "\nSintaxis: %s %s\n"},
	/* fr */ {IDGS_SYNTAX_S_S_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_SYNTAX_S_S_HU, "\nSzintaxis: %s %s\n"},
	/* it */ {IDGS_SYNTAX_S_S_IT, "\nSintassi: %s %s\n"},
	/* ko */ {IDGS_SYNTAX_S_S_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SYNTAX_S_S_NL, "\nSyntax: %s %s\n"},
	/* pl */ {IDGS_SYNTAX_S_S_PL, "\nSk≥adnia: %s %s\n"},
	/* ru */ {IDGS_SYNTAX_S_S_RU, "\nSyntax: %s %s\n"},
	/* sv */ {IDGS_SYNTAX_S_S_SV, "\nSyntax: %s %s\n"},
	/* tr */ {IDGS_SYNTAX_S_S_TR, "\nSˆzdizimi: %s %s\n"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_ABBREVIATION_S,    N_("Abbreviation: %s\n")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ABBREVIATION_S_DA, "Forkortelse: %s\n"},
	/* de */ {IDGS_ABBREVIATION_S_DE, "Abk¸rzung: %s\n"},
	/* es */ {IDGS_ABBREVIATION_S_ES, "AbreviaciÛn: %s\n"},
	/* fr */ {IDGS_ABBREVIATION_S_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ABBREVIATION_S_HU, "RˆvidÌtÈs: %s\n"},
	/* it */ {IDGS_ABBREVIATION_S_IT, "Abbreviazione: %s\n"},
	/* ko */ {IDGS_ABBREVIATION_S_KO, "√‡æ‡: %s\n"},
	/* nl */ {IDGS_ABBREVIATION_S_NL, "Afkorting: %s\n"},
	/* pl */ {IDGS_ABBREVIATION_S_PL, "SkrÛt: %s\n"},
	/* ru */ {IDGS_ABBREVIATION_S_RU, "Abbreviation: %s\n"},
	/* sv */ {IDGS_ABBREVIATION_S_SV, "Fˆrkortning: %s\n"},
	/* tr */ {IDGS_ABBREVIATION_S_TR, "K˝saltma: %s\n"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_AVAILABLE_COMMANDS_ARE,    N_("Available commands are:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_AVAILABLE_COMMANDS_ARE_DA, "TilgÊngelige kommandoer:"},
	/* de */ {IDGS_AVAILABLE_COMMANDS_ARE_DE, "Zul‰ssige Kommandos sind:"},
	/* es */ {IDGS_AVAILABLE_COMMANDS_ARE_ES, "Los comandos disponibles son:"},
	/* fr */ {IDGS_AVAILABLE_COMMANDS_ARE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_AVAILABLE_COMMANDS_ARE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_AVAILABLE_COMMANDS_ARE_IT, "I comandi disponibili sono:"},
	/* ko */ {IDGS_AVAILABLE_COMMANDS_ARE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_AVAILABLE_COMMANDS_ARE_NL, "Beschikbare commandos zijn:"},
	/* pl */ {IDGS_AVAILABLE_COMMANDS_ARE_PL, "DostÍpne opcje to:"},
	/* ru */ {IDGS_AVAILABLE_COMMANDS_ARE_RU, "Available commands are:"},
	/* sv */ {IDGS_AVAILABLE_COMMANDS_ARE_SV, "Tillg‰ngliga kommandon:"},
	/* tr */ {IDGS_AVAILABLE_COMMANDS_ARE_TR, "Kullan˝labilir komutlar:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MACHINE_STATE_COMMANDS,    N_("Machine state commands:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MACHINE_STATE_COMMANDS_DA, "Kommandoer for maskinstatus:"},
	/* de */ {IDGS_MACHINE_STATE_COMMANDS_DE, "Maschinen Zustandskommandos:"},
	/* es */ {IDGS_MACHINE_STATE_COMMANDS_ES, "Comandos estado m·quina:"},
	/* fr */ {IDGS_MACHINE_STATE_COMMANDS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MACHINE_STATE_COMMANDS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MACHINE_STATE_COMMANDS_IT, "Comandi di stato del computer:"},
	/* ko */ {IDGS_MACHINE_STATE_COMMANDS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MACHINE_STATE_COMMANDS_NL, "Machine status commandos:"},
	/* pl */ {IDGS_MACHINE_STATE_COMMANDS_PL, "Komendy stanu maszyny:"},
	/* ru */ {IDGS_MACHINE_STATE_COMMANDS_RU, "Machine state commands:"},
	/* sv */ {IDGS_MACHINE_STATE_COMMANDS_SV, "Kommandon fˆr maskinstatus:"},
	/* tr */ {IDGS_MACHINE_STATE_COMMANDS_TR, "Makine durum komutlar˝:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MEMSPACE,    N_("memspace")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MEMSPACE_DA, "huk.omrÂde"},
	/* de */ {IDGS_MEMSPACE_DE, "Speicherbereich"},
	/* es */ {IDGS_MEMSPACE_ES, "espacio de memoria"},
	/* fr */ {IDGS_MEMSPACE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MEMSPACE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MEMSPACE_IT, "spazio di memoria"},
	/* ko */ {IDGS_MEMSPACE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MEMSPACE_NL, "geheugenruimte"},
	/* pl */ {IDGS_MEMSPACE_PL, "memspace"},
	/* ru */ {IDGS_MEMSPACE_RU, "memspace"},
	/* sv */ {IDGS_MEMSPACE_SV, "minnesomrÂde"},
	/* tr */ {IDGS_MEMSPACE_TR, "bellekalan˝"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_BANKNAME,    N_("bankname")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_BANKNAME_DA, "banknavn"},
	/* de */ {IDGS_BANKNAME_DE, "Speicherbank"},
	/* es */ {IDGS_BANKNAME_ES, "Nombre de banco"},
	/* fr */ {IDGS_BANKNAME_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_BANKNAME_HU, ""},  /* fuzzy */
	/* it */ {IDGS_BANKNAME_IT, "nome banco"},
	/* ko */ {IDGS_BANKNAME_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_BANKNAME_NL, "bank naam"},
	/* pl */ {IDGS_BANKNAME_PL, "bankname"},
	/* ru */ {IDGS_BANKNAME_RU, "bankname"},
	/* sv */ {IDGS_BANKNAME_SV, "banknamn"},
	/* tr */ {IDGS_BANKNAME_TR, "bankismi"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_BANK_DESCRIPTION,    N_("If bankname is not given, print the possible banks for the memspace.\nIf bankname is given set the current bank in the memspace to the given\nbank.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_BANK_DESCRIPTION_DA, "Hvis banknavn ikke angives vises mulige banker for hukommelsesomrÂdet.\nHvis banknavn angives sÊttes aktuel bank i hukommelsesomrÂdet til den\nangivne bank."},
	/* de */ {IDGS_MON_BANK_DESCRIPTION_DE, "Falls `bankname' nicht angegeben wird, Ausgabe der mˆglichen B‰nke in `memspace'.\nFalls `bankname' angegeben wird, setze aktuelle Bank in `memspace' mit angegebener Bank."},
	/* es */ {IDGS_MON_BANK_DESCRIPTION_ES, "Si no se pone el nombre del banco, imprimir los bancos posivles para el espacio de memoria.\nSi se da el nombre de banco se susa como espacio de memoria actual \nbanco."},
	/* fr */ {IDGS_MON_BANK_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_BANK_DESCRIPTION_HU, "Ha a lap sz·ma nincs megadva, kiÌrja a lehetsÈges lapokat a memÛria tÈrbıl.\nHa meg van adva, az aktu·lis lap sz·mot a memÛria tÈrben a megadott lapra ·llÌtja."},
	/* it */ {IDGS_MON_BANK_DESCRIPTION_IT, "Se non viene specificato il nome del banco, stampa tutti i banchi\npossibili per lo spazio di memoria.\nSe viene specificato il nome del banco, imposta il banco attuale nello\nspazio di memoria specificato."},
	/* ko */ {IDGS_MON_BANK_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_BANK_DESCRIPTION_NL, "Als de banknaam niet is opgegeven worden de mogelijke banken voor de\ngeheugenruimte weergegeven. Als de banknaam is opgegeven dan wordt de\nhuidige bank in de geheugenruimte gezet volgens de opgegeven banknaam."},
	/* pl */ {IDGS_MON_BANK_DESCRIPTION_PL, "Je∂li nie podano nazwy banku, pokazuje moøliwe banki pamiÍci.\nJe∂li podano nazwÍ banku, ustawia obecny bank pamiÍci na\ndany bank."},
	/* ru */ {IDGS_MON_BANK_DESCRIPTION_RU, "If bankname is not given, print the possible banks for the memspace.\nIf bankname is given set the current bank in the memspace to the given\nbank."},
	/* sv */ {IDGS_MON_BANK_DESCRIPTION_SV, "Om banknamn inte anges, skriv ut mˆjliga bankar fˆr minnesomrÂdet.\nOm banknamn anges, s‰tt aktuell bank i minnesomrÂdet till den givna\nbanken."},
	/* tr */ {IDGS_MON_BANK_DESCRIPTION_TR, "Eer bank ismi verilmemi˛se, bellek alan˝ iÁin uygun banklar yazd˝r˝l˝r.\nEer bank ismi verilmi˛se, geÁerli bank bellek alan˝ iÁinde verilen\nbanka e˛itlenir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_BACKTRACE_DESCRIPTION,    N_("Print JSR call chain (most recent call first). Stack offset\nrelative to SP+1 is printed in parentheses. This is a best guess\nonly.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_BACKTRACE_DESCRIPTION_DA, "Vis JSR-kaldekÊde (seneste kald ¯verst). Stakafstand\nrelativ til SP+1 vises i parantes. Dette er kun et\ngÊt."},
	/* de */ {IDGS_MON_BACKTRACE_DESCRIPTION_DE, "Zeige JSR Aufrufkette (letzter Aufruf zuerst). Stack offset\nwird relative zu SP+1 in Klammern gezeigt. Dies ist jedoch nur\neine Sch‰tzung."},
	/* es */ {IDGS_MON_BACKTRACE_DESCRIPTION_ES, "Imprimir cadena de llamada JSR (la llamada m·s reciente primero). Stack offset\nrelativo a  SP+1 se imprime entre parentesis. Esta es una buena suposiciÛn\nsÛlo."},
	/* fr */ {IDGS_MON_BACKTRACE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_BACKTRACE_DESCRIPTION_HU, "JSR hÌv·s lista kiÌr·sa (legutÛbbi elıszˆr). A verem SP+1\nhelyen lÈvı tartalma z·rÛjelben. Ez csak\negy legjobb becslÈs."},
	/* it */ {IDGS_MON_BACKTRACE_DESCRIPTION_IT, "Stampa la catena di chiamate JSR (la chiamata pi˘ recente per prima).\nL'offset dello stack relativo a SP+1 Ë stampato tra parentesi. Questo Ë\nsolo l'ipotesi migliore."},
	/* ko */ {IDGS_MON_BACKTRACE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_BACKTRACE_DESCRIPTION_NL, "Toon JSR gebruik (meest recent gebruikt eerst). De stack\ncompensatie relatief ten opzichte van SP+1 zal worden getoont\nbinnen de aanhalingtekens. Dit is op basis van de beste gok."},
	/* pl */ {IDGS_MON_BACKTRACE_DESCRIPTION_PL, "Pokazuje ≥aÒcuch wezwaÒ JSR. WyrÛwnanie stosu relatywne\ndo SP+1 jest pokazane w nawiasach. Warto∂Ê jest szacowana."},
	/* ru */ {IDGS_MON_BACKTRACE_DESCRIPTION_RU, "Print JSR call chain (most recent call first). Stack offset\nrelative to SP+1 is printed in parentheses. This is a best guess\nonly."},
	/* sv */ {IDGS_MON_BACKTRACE_DESCRIPTION_SV, "Skriv JSR-anropskedja (senaste anrop fˆrst). StackavstÂnd\nrelativt till SP+1 visas inom parantes. Detta ‰r bara en\ngissning."},
	/* tr */ {IDGS_MON_BACKTRACE_DESCRIPTION_TR, "JSR Áar˝ zincirini yazd˝r (en son Áar˝lar ˆncelikli). Y˝˝t ofseti\nSP+1'e bal˝ olarak parantez iÁersinde yazd˝r˝l˝r. Bu yaln˝zca en iyi\ntahmindir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_CPU_DESCRIPTION,    N_("Specify the type of CPU currently used (6502/z80).")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_CPU_DESCRIPTION_DA, "Angiv typen af CPU der anvendes for ¯jeblikket (6502/z80)."},
	/* de */ {IDGS_MON_CPU_DESCRIPTION_DE, "CPU Typ setzen (6502/z80)"},
	/* es */ {IDGS_MON_CPU_DESCRIPTION_ES, "Especificar el tipo de CPU usada (6502/z80)."},
	/* fr */ {IDGS_MON_CPU_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_CPU_DESCRIPTION_HU, "A processzor tÌpus·nak megad·sa (6502/z80)."},
	/* it */ {IDGS_MON_CPU_DESCRIPTION_IT, "Specifica il tipo di CPU utilizzata al momento (6502/z80)."},
	/* ko */ {IDGS_MON_CPU_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_CPU_DESCRIPTION_NL, "Geef de soort CPU die op dit moment in gebruik is (6502/z80)."},
	/* pl */ {IDGS_MON_CPU_DESCRIPTION_PL, "Okre∂l typ obecnie uøywanego CPU (6502/z80)."},
	/* ru */ {IDGS_MON_CPU_DESCRIPTION_RU, "Specify the type of CPU currently used (6502/z80)."},
	/* sv */ {IDGS_MON_CPU_DESCRIPTION_SV, "Ange typ av CPU som anv‰nds fˆr n‰rvarande (6502/z80)."},
	/* tr */ {IDGS_MON_CPU_DESCRIPTION_TR, "ﬁu anda kullan˝lmakta olan CPU tipini belirleyin (6502/z80)."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_COUNT,    N_("count")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_COUNT_DA, "antal"},
	/* de */ {IDGS_COUNT_DE, "Z‰hler"},
	/* es */ {IDGS_COUNT_ES, "contador"},
	/* fr */ {IDGS_COUNT_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_COUNT_HU, ""},  /* fuzzy */
	/* it */ {IDGS_COUNT_IT, "contatore"},
	/* ko */ {IDGS_COUNT_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_COUNT_NL, "hoeveelheid"},
	/* pl */ {IDGS_COUNT_PL, "count"},
	/* ru */ {IDGS_COUNT_RU, "count"},
	/* sv */ {IDGS_COUNT_SV, "antal"},
	/* tr */ {IDGS_COUNT_TR, "adet"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_CPUHISTORY_DESCRIPTION,    N_("Show <count> last executed commands.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_CPUHISTORY_DESCRIPTION_DA, "Vis <antal> senest eksekverede instruktioner."},
	/* de */ {IDGS_MON_CPUHISTORY_DESCRIPTION_DE, "Zeige [<Z‰hler>] zuletzt ausgef¸hrte Kommandos"},
	/* es */ {IDGS_MON_CPUHISTORY_DESCRIPTION_ES, "Show <contador> ˙ltimo comando ejecutado."},
	/* fr */ {IDGS_MON_CPUHISTORY_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_CPUHISTORY_DESCRIPTION_HU, "<darab> utolj·ra vÈgrehajtott utasÌt·s mutat·sa."},
	/* it */ {IDGS_MON_CPUHISTORY_DESCRIPTION_IT, "Mostra gli ultimi <contatore> comandi eseguiti."},
	/* ko */ {IDGS_MON_CPUHISTORY_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_CPUHISTORY_DESCRIPTION_NL, "Toon <hoeveelheid> laatst uitgevoerde commandos."},
	/* pl */ {IDGS_MON_CPUHISTORY_DESCRIPTION_PL, "Pokazuje <ilo∂Ê> ostatnio wykonanych poleceÒ."},
	/* ru */ {IDGS_MON_CPUHISTORY_DESCRIPTION_RU, "Show <count> last executed commands."},
	/* sv */ {IDGS_MON_CPUHISTORY_DESCRIPTION_SV, "Visa <antal> senast exekverade kommandon."},
	/* tr */ {IDGS_MON_CPUHISTORY_DESCRIPTION_TR, "<adet> son Áal˝˛t˝r˝lan komutlar˝ gˆster."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_FILENAME,    N_("filename")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_FILENAME_DA, "filnavn"},
	/* de */ {IDGS_FILENAME_DE, "Dateiname"},
	/* es */ {IDGS_FILENAME_ES, "Nombre fichero"},
	/* fr */ {IDGS_FILENAME_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_FILENAME_HU, ""},  /* fuzzy */
	/* it */ {IDGS_FILENAME_IT, "nome file"},
	/* ko */ {IDGS_FILENAME_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_FILENAME_NL, "bestandsnaam"},
	/* pl */ {IDGS_FILENAME_PL, "filename"},
	/* ru */ {IDGS_FILENAME_RU, "ÿ‹Ô ‰–Ÿ€–"},
	/* sv */ {IDGS_FILENAME_SV, "filnamn"},
	/* tr */ {IDGS_FILENAME_TR, "dosyaismi"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DUMP_DESCRIPTION,    N_("Write a snapshot of the machine into the file specified.\nThis snapshot is compatible with a snapshot written out by the UI.\nNote: No ROM images are included into the dump.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DUMP_DESCRIPTION_DA, "Skriv et snapshot til den angivne fil.\nDette snapshot er kompatibelt med dem, der oprettes fra menuen.\nOBS: ROM-images inkluderes ikke i snapshot."},
	/* de */ {IDGS_MON_DUMP_DESCRIPTION_DE, "Schreibe eine Snapsho Datei der Maschine auf die angebene Datei.\nDieser Snapshot ist kompatible zu einem Snapshot initiiert aus dem Men¸.\nHinweis: Die ROM Images werden im Snapshot nicht inkludiert."},
	/* es */ {IDGS_MON_DUMP_DESCRIPTION_ES, "Grabar volcado memoria de la m·quina en el fichero especificado.\nEste volvado es compatible con el volcado grabado por el UI.\nNota: no se vuelca ninguna  imagen ROM."},
	/* fr */ {IDGS_MON_DUMP_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DUMP_DESCRIPTION_HU, "PillanatkÈp Ìr·sa a gÈprıl a megadott f·jlba. A pillanatkÈp\nkompatibilis azzal, amelyet a grafikus fel¸let hoz lÈtre.\nMegjegyzÈs: a ROM kÈpm·sok nem ker¸lnek bele."},
	/* it */ {IDGS_MON_DUMP_DESCRIPTION_IT, "Scrive uno snapshot del computer sul file specificato.\nQuesto snapshot Ë compatibile con uno snapshot scritto dall'IU.\nNota: Le immagini ROM non sono incluse nel dump."},
	/* ko */ {IDGS_MON_DUMP_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DUMP_DESCRIPTION_NL, "Schrijf een momentopname van de machine naar de opgegeven bestand.\nDeze momentopname is compatibel met een momentopname zoals geschreven van\nuit het menu.\nNB: ROM bestanden zijn niet opgenomen in de momentopname."},
	/* pl */ {IDGS_MON_DUMP_DESCRIPTION_PL, "Zapis zrzutu maszyny do danego pliku.\nZrzut ten jest kompatybilny ze zrzutami zapisywanymi przez UI.\nUwaga: W zrzucie nie s± zawarte øadne obrazy ROM."},
	/* ru */ {IDGS_MON_DUMP_DESCRIPTION_RU, "Write a snapshot of the machine into the file specified.\nThis snapshot is compatible with a snapshot written out by the UI.\nNote: No ROM images are included into the dump."},
	/* sv */ {IDGS_MON_DUMP_DESCRIPTION_SV, "Skriv en ˆgonblicksbild av maskinen till den angivna filen.\n÷gonblicksbilden ‰r kompatibel med de som skapas frÂn menyn.\nObservera: ROM-avbildningar inkluderas inte i bilden."},
	/* tr */ {IDGS_MON_DUMP_DESCRIPTION_TR, "Belirtilen dosya iÁersine makinenin anl˝k gˆr¸nt¸s¸n¸ yaz.\nBu anl˝k gˆr¸nt¸ UI d˝˛˝ndan yazd˝r˝lan anl˝k gˆr¸nt¸ ile uyumludur.\nNot: HiÁbir ROM imaj˝ dˆk¸m iÁersinde yer almaz."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_ADDRESS,    N_("address")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ADDRESS_DA, "adresse"},
	/* de */ {IDGS_ADDRESS_DE, "Adresse"},
	/* es */ {IDGS_ADDRESS_ES, "direcciÛn"},
	/* fr */ {IDGS_ADDRESS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ADDRESS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_ADDRESS_IT, "indirizzo"},
	/* ko */ {IDGS_ADDRESS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ADDRESS_NL, "adres"},
	/* pl */ {IDGS_ADDRESS_PL, "address"},
	/* ru */ {IDGS_ADDRESS_RU, ""},  /* fuzzy */
	/* sv */ {IDGS_ADDRESS_SV, "adress"},
	/* tr */ {IDGS_ADDRESS_TR, "adres"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_GOTO_DESCRIPTION,    N_("Change the PC to ADDRESS and continue execution")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_GOTO_DESCRIPTION_DA, "∆ndr programtÊlleren (PC) til ADRESSE og fortsÊt eksekvering"},
	/* de */ {IDGS_MON_GOTO_DESCRIPTION_DE, "Setze PC auf ADRESSE und setze Ausf¸hrung fort"},
	/* es */ {IDGS_MON_GOTO_DESCRIPTION_ES, "Cambiar el  PC con direcciÛn y continuar la ejecuciÛn"},
	/* fr */ {IDGS_MON_GOTO_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_GOTO_DESCRIPTION_HU, "A PC ·llÌt·sa ADDRESS cÌmre Ès folytat·s"},
	/* it */ {IDGS_MON_GOTO_DESCRIPTION_IT, "Cambia il PC in INDIRIZZO e continua l'esecuzione"},
	/* ko */ {IDGS_MON_GOTO_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_GOTO_DESCRIPTION_NL, "Zet de PC naar ADRES en ga door met de uitvoering van instructies."},
	/* pl */ {IDGS_MON_GOTO_DESCRIPTION_PL, "ZmieÒ PC na ADRES i wykonuj dalej"},
	/* ru */ {IDGS_MON_GOTO_DESCRIPTION_RU, "∑–‹’›ÿ‚Ï ø∫ ›– ∞¥¿µ¡ ÿ ﬂ‡ﬁ‘ﬁ€÷ÿ‚Ï “Îﬂﬁ€›’›ÿ’"},
	/* sv */ {IDGS_MON_GOTO_DESCRIPTION_SV, "ƒndra PC till ADRESS och forts‰tt exekveringen"},
	/* tr */ {IDGS_MON_GOTO_DESCRIPTION_TR, "PC'yi ADDRESS'e Áevirip Áal˝˛t˝rmaya devam edin"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_IO_DESCRIPTION,    N_("Print out the I/O area of the emulated machine.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_IO_DESCRIPTION_DA, "Udskriv I/O-omrÂdet for den emulerede maskine."},
	/* de */ {IDGS_MON_IO_DESCRIPTION_DE, "Zeige den I/O Bereich der emulierten Maschine."},
	/* es */ {IDGS_MON_IO_DESCRIPTION_ES, "Imprimir el area de entrada/salida de la m·quina emulada."},
	/* fr */ {IDGS_MON_IO_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_IO_DESCRIPTION_HU, "Az emul·lt gÈp I/O tartom·ny·nak mutat·sa."},
	/* it */ {IDGS_MON_IO_DESCRIPTION_IT, "Stampa l'area di I/O del computer emulato."},
	/* ko */ {IDGS_MON_IO_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_IO_DESCRIPTION_NL, "Toon de I/O geheugenruimte van de huidige machine."},
	/* pl */ {IDGS_MON_IO_DESCRIPTION_PL, "Pokaø obszar we/wy emulowanej maszyny."},
	/* ru */ {IDGS_MON_IO_DESCRIPTION_RU, "Print out the I/O area of the emulated machine."},
	/* sv */ {IDGS_MON_IO_DESCRIPTION_SV, "Skriv I/O-omrÂdet fˆr den emulerade maskinen."},
	/* tr */ {IDGS_MON_IO_DESCRIPTION_TR, "Em¸le edilen makinenin G/« alan˝n˝ yazd˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_EXPORT_DESCRIPTION,    N_("Print out list of attached expansion port devices.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_EXPORT_DESCRIPTION_DA, "Udskriv liste over tilsluttede udviddelsesportenheder"},
	/* de */ {IDGS_MON_EXPORT_DESCRIPTION_DE, "Zeige eine Liste der Ger‰te am Expansion Port."},
	/* es */ {IDGS_MON_EXPORT_DESCRIPTION_ES, "Imprimir lista perifÈricos insertados en puertos de expansiÛn."},
	/* fr */ {IDGS_MON_EXPORT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_EXPORT_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_EXPORT_DESCRIPTION_IT, "Stampa lista dei dispositivi collegati sulla porta di espansione."},
	/* ko */ {IDGS_MON_EXPORT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_EXPORT_DESCRIPTION_NL, "Druk een lijst van gekoppelde uitbreidingspoort apparaten af."},
	/* pl */ {IDGS_MON_EXPORT_DESCRIPTION_PL, "Wydrukuj listÍ pod≥±czonych urz±dzeÒ portÛw rozszerzeÒ."},
	/* ru */ {IDGS_MON_EXPORT_DESCRIPTION_RU, "Print out list of attached expansion port devices."},
	/* sv */ {IDGS_MON_EXPORT_DESCRIPTION_SV, "Skriv ut lista ˆver anslutna expansionsportsenheter."},
	/* tr */ {IDGS_MON_EXPORT_DESCRIPTION_TR, "Geni˛letme yuvas˝na tak˝l˝ ayg˝tlar˝n listesini yazd˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_NEXT_DESCRIPTION,    N_("Advance to the next instruction.  Subroutines are treated as\na single instruction.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_NEXT_DESCRIPTION_DA, "GÂ frem til nÊste instruktion. Subrutiner bliver behandlet som\nen enkelt instruktion."},
	/* de */ {IDGS_MON_NEXT_DESCRIPTION_DE, "Fahre bis zur n‰chsten Instruktion fort.\nUnterroutinen werden wie eine einzelne Instruktion behandelt."},
	/* es */ {IDGS_MON_NEXT_DESCRIPTION_ES, "Avanzar a la siguiente instrucciÛn.  Subrutinas ser·n tratadas como\ninstrucciones simples."},
	/* fr */ {IDGS_MON_NEXT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_NEXT_DESCRIPTION_HU, "A kˆvetkezı utasÌt·sra lÈpÈs.  A szubrutinokat egy\nutasÌt·snak tekinti."},
	/* it */ {IDGS_MON_NEXT_DESCRIPTION_IT, "Passa alla prossima istruzione. Le subrutine sono trattate come\nuna singola istruzione."},
	/* ko */ {IDGS_MON_NEXT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_NEXT_DESCRIPTION_NL, "Ga naar de volgende instructie. Subroutines worden behandled als een\nenkele instructie."},
	/* pl */ {IDGS_MON_NEXT_DESCRIPTION_PL, "Przechodzi do nastÍpnej instrukcji. Procedury s± traktowane\njak pojedyncze instrukcje."},
	/* ru */ {IDGS_MON_NEXT_DESCRIPTION_RU, "Advance to the next instruction.  Subroutines are treated as\na single instruction."},
	/* sv */ {IDGS_MON_NEXT_DESCRIPTION_SV, "GÂ till n‰sta instruktion. Underrutiner hanteras som en\nenda instruktion."},
	/* tr */ {IDGS_MON_NEXT_DESCRIPTION_TR, "Sonraki komuta ilerle.  Altrutinler tek bir komutmu˛\ngibi i˛lendi."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_REG_NAME,    N_("reg_name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_REG_NAME_DA, "regnavn"},
	/* de */ {IDGS_REG_NAME_DE, "Register Name"},
	/* es */ {IDGS_REG_NAME_ES, "Nombre registro"},
	/* fr */ {IDGS_REG_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_REG_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDGS_REG_NAME_IT, "nome registro"},
	/* ko */ {IDGS_REG_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_REG_NAME_NL, "register naam"},
	/* pl */ {IDGS_REG_NAME_PL, "reg_name"},
	/* ru */ {IDGS_REG_NAME_RU, "reg_name"},
	/* sv */ {IDGS_REG_NAME_SV, "regnamn"},
	/* tr */ {IDGS_REG_NAME_TR, "reg_ismi"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_NUMBER,    N_("number")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_NUMBER_DA, "nummer"},
	/* de */ {IDGS_NUMBER_DE, "Nummer"},
	/* es */ {IDGS_NUMBER_ES, "n˙mero"},
	/* fr */ {IDGS_NUMBER_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_NUMBER_HU, ""},  /* fuzzy */
	/* it */ {IDGS_NUMBER_IT, "numero"},
	/* ko */ {IDGS_NUMBER_KO, "º˝¿⁄"},
	/* nl */ {IDGS_NUMBER_NL, "nummer"},
	/* pl */ {IDGS_NUMBER_PL, "numer"},
	/* ru */ {IDGS_NUMBER_RU, "number"},
	/* sv */ {IDGS_NUMBER_SV, "nummer"},
	/* tr */ {IDGS_NUMBER_TR, "say˝"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_REGISTERS_DESCRIPTION,    N_("Assign respective registers.  With no parameters, display register\nvalues.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_REGISTERS_DESCRIPTION_DA, "Tildel vÊrdi til registre. Uden parametre vises nuvÊrende vÊrdier\ni registrene."},
	/* de */ {IDGS_MON_REGISTERS_DESCRIPTION_DE, "Zuweisung auf entsprechende Register. Ohne Parameter, zeige Register Werte."},
	/* es */ {IDGS_MON_REGISTERS_DESCRIPTION_ES, "Asignar registros respectivos. Sin parametros, mostrar valores\nregistros."},
	/* fr */ {IDGS_MON_REGISTERS_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_REGISTERS_DESCRIPTION_HU, "Megadott regiszterek be·llÌt·sa. ParamÈterek nÈlk¸l, a regiszterek\ntartalm·nak kiÌr·sa."},
	/* it */ {IDGS_MON_REGISTERS_DESCRIPTION_IT, "Assegna i rispettivi registri. Senza parametri, mostra i valori dei\nregistri."},
	/* ko */ {IDGS_MON_REGISTERS_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_REGISTERS_DESCRIPTION_NL, "Vul opgegeven registers met de toebehorende waarde. Zonder parameter, toon\nde huidige waarden in de registers."},
	/* pl */ {IDGS_MON_REGISTERS_DESCRIPTION_PL, "Przyporz±dkowuje odpowiednie rejestry. Bez podanych parametrÛw\npokazuje warto∂ci rejestrÛw."},
	/* ru */ {IDGS_MON_REGISTERS_DESCRIPTION_RU, "Assign respective registers.  With no parameters, display register\nvalues."},
	/* sv */ {IDGS_MON_REGISTERS_DESCRIPTION_SV, "Tilldela respektive register. Utan parametrar visas innehÂllet\ni registren."},
	/* tr */ {IDGS_MON_REGISTERS_DESCRIPTION_TR, "S˝rayla registerlara ata.  parametreler olmadan, register deerlerini\ngˆr¸nt¸le."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_RESET_DESCRIPTION,    N_("Reset the machine or drive. Type: 0 = soft, 1 = hard, 8-11 = drive.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_RESET_DESCRIPTION_DA, "Reset maskine eller diskettedrev. Type: 0 = bl¯d, 1 = hÂrd,\n8-11 = diskettedrev."},
	/* de */ {IDGS_MON_RESET_DESCRIPTION_DE, "Reset der Maschine oder des Laufwerks. Typ: 0 = soft, 1 = hart, 8-11 = Laufwerk."},
	/* es */ {IDGS_MON_RESET_DESCRIPTION_ES, "Reiniciar m·quina o unidad disco. Tipo: 0 = soft, 1 = hard, 8-11 = unidad disco."},
	/* fr */ {IDGS_MON_RESET_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_RESET_DESCRIPTION_HU, "A sz·mÌtÛgÈp vagy meghajtÛ ˙jraindÌt·sa. TÌpus: 0 = meleg, 1 = hideg, 8-11 = meghajtÛ."},
	/* it */ {IDGS_MON_RESET_DESCRIPTION_IT, "Resetta il computer o il drive. Tipo: 0 = soft, 1 = hard, 8-11 = drive."},
	/* ko */ {IDGS_MON_RESET_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_RESET_DESCRIPTION_NL, "Reset de machine of drive. Soort: 0 = zacht, 1 = hard, 8-11 = drive."},
	/* pl */ {IDGS_MON_RESET_DESCRIPTION_PL, "Reset maszyny lub napÍdu. Typ: 0 = miÍkki, 1 = twardy, 8-11 = napÍdu."},
	/* ru */ {IDGS_MON_RESET_DESCRIPTION_RU, "Reset the machine or drive. Type: 0 = soft, 1 = hard, 8-11 = drive."},
	/* sv */ {IDGS_MON_RESET_DESCRIPTION_SV, "≈terst‰ll maskinen eller diskettstationen. Typ: 0 = mjuk, 1 = hÂrd,\n8-11 = diskettstation."},
	/* tr */ {IDGS_MON_RESET_DESCRIPTION_TR, "Makine ya da s¸r¸c¸y¸ resetle. Tip: 0 = soft, 1 = hard, 8-11 = drive."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_RETURN_DESCRIPTION,    N_("Continues execution and returns to the monitor just before the next\nRTS or RTI is executed.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_RETURN_DESCRIPTION_DA, "FortsÊt eksekveringen og vend tilbage til monitoren lige inden nÊste\nRTS eller RTI udf¯res."},
	/* de */ {IDGS_MON_RETURN_DESCRIPTION_DE, "Setzt Ausf¸hrung fort und retourniert bevor der n‰chsten RTS oder RTI instruction."},
	/* es */ {IDGS_MON_RETURN_DESCRIPTION_ES, "Continuar ejecuciÛn y volver al monitor justo antes que la siguiente\nRTS o RTI sea ejecutada."},
	/* fr */ {IDGS_MON_RETURN_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_RETURN_DESCRIPTION_HU, "Folytatja a vÈgrehajt·st Ès visszatÈr a monitorba a kˆvetkezı\nRTS vagy RTI utasÌt·s elıtt."},
	/* it */ {IDGS_MON_RETURN_DESCRIPTION_IT, "Continua l'esecuzione e ritorna al monitor subito prima della prossima\nesecuzione di RTS o RTI."},
	/* ko */ {IDGS_MON_RETURN_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_RETURN_DESCRIPTION_NL, "Ga door met uitvoeren van instructies en kom terug naar de monitor net voor de\nvolgende RTS of RTI wordt uitgevoerd."},
	/* pl */ {IDGS_MON_RETURN_DESCRIPTION_PL, "Wykonuje dalej i wraca do monitora tuø przed wykonaniem\nnastÍpnego RTS lub RTI."},
	/* ru */ {IDGS_MON_RETURN_DESCRIPTION_RU, "Continues execution and returns to the monitor just before the next\nRTS or RTI is executed."},
	/* sv */ {IDGS_MON_RETURN_DESCRIPTION_SV, "Forts‰tt exekveringen och ÂtergÂ till monitorn precis innan n‰sta\nRTS eller RTI exekveras."},
	/* tr */ {IDGS_MON_RETURN_DESCRIPTION_TR, "«al˝˛maya devam eder ve sonraki RTS ya da RTI Áal˝˛t˝r˝lmadan hemen ˆnce\nmonitˆre geri dˆner."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_SCREEN_DESCRIPTION,    N_("Displays the contents of the screen.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_SCREEN_DESCRIPTION_DA, "Viser skÊrmens indhold."},
	/* de */ {IDGS_MON_SCREEN_DESCRIPTION_DE, "Zeigt Bildschirminhalt."},
	/* es */ {IDGS_MON_SCREEN_DESCRIPTION_ES, "Mostrar los contenidos de la pantalla."},
	/* fr */ {IDGS_MON_SCREEN_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_SCREEN_DESCRIPTION_HU, "A kÈpernyı tartalm·nak mutat·sa."},
	/* it */ {IDGS_MON_SCREEN_DESCRIPTION_IT, "Mostra il contenuto dello schermo."},
	/* ko */ {IDGS_MON_SCREEN_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_SCREEN_DESCRIPTION_NL, "Toont de inhoud van het scherm."},
	/* pl */ {IDGS_MON_SCREEN_DESCRIPTION_PL, "Pokazuje zawarto∂Ê ekranu."},
	/* ru */ {IDGS_MON_SCREEN_DESCRIPTION_RU, "æ‚ﬁ—‡–÷–’‚ ·ﬁ‘’‡÷–›ÿ’ Ì⁄‡–›–."},
	/* sv */ {IDGS_MON_SCREEN_DESCRIPTION_SV, "Visar sk‰rmens innehÂll."},
	/* tr */ {IDGS_MON_SCREEN_DESCRIPTION_TR, "Ekran iÁeriini gˆr¸nt¸ler."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_STEP_DESCRIPTION,    N_("Single-step through instructions.  COUNT allows stepping\nmore than a single instruction at a time.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_STEP_DESCRIPTION_DA, "GÂ skridtvis gennem instruktioner. Hvis ANTAL angives kan\nflere instruktioner udf¯res i hvert skridt."},
	/* de */ {IDGS_MON_STEP_DESCRIPTION_DE, "Einzelschritt Ausf¸hrung durch Instruktionen. COUNT erlaubt die Ausf¸hrung\nmehrerer Instruktionen auf einmal."},
	/* es */ {IDGS_MON_STEP_DESCRIPTION_ES, "Salto simple a traves de la instrucciÛn.  el CONTADOR permite el salto de\nm·s de una instrucciÛn a la vez."},
	/* fr */ {IDGS_MON_STEP_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_STEP_DESCRIPTION_HU, "LÈpkedÈs egyesÈvel az utasÌt·sokon.  A DARAB-bal be·llÌthatÛ,\nha tˆbb utasÌt·st kell ugrani egyszerre."},
	/* it */ {IDGS_MON_STEP_DESCRIPTION_IT, "Modalit‡ single step attraverso le istruzioni. Il CONTATORE permette\ndi attraversare pi˘ di una singola istruzione per volta."},
	/* ko */ {IDGS_MON_STEP_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_STEP_DESCRIPTION_NL, "Enkel-stap door de instructies. AANTAL zorgt ervoor dat er meerdere\ninstructies worden uitgevoerd in een keer."},
	/* pl */ {IDGS_MON_STEP_DESCRIPTION_PL, "Przechodzi przez instrukcje krok po kroku. COUNT pozwala\nprzechodziÊ przez wiÍcej niø jedn± instrukcjÍ na raz."},
	/* ru */ {IDGS_MON_STEP_DESCRIPTION_RU, "Single-step through instructions.  COUNT allows stepping\nmore than a single instruction at a time."},
	/* sv */ {IDGS_MON_STEP_DESCRIPTION_SV, "Stega genom instruktioner. ANTAL gˆr det mˆjligt att stega\ngenom mer ‰n en enkel instruktion i varje steg."},
	/* tr */ {IDGS_MON_STEP_DESCRIPTION_TR, "Komutlara doru tek-ad˝m.  COUNT bir defada birden fazla\nkomutu ad˝mlamaya izin verir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_STOPWATCH_DESCRIPTION,    N_("Print the CPU cycle counter of the current device. 'reset' sets the counter to 0.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_STOPWATCH_DESCRIPTION_DA, "Udskriv CPU-cyklus-tÊller for den nuvÊrende enhed. \"reset\" sÊtter tÊlleren til 0."},
	/* de */ {IDGS_MON_STOPWATCH_DESCRIPTION_DE, "Zeige CPU Zyklusz‰hler des aktuellen Ger‰ts. 'reset' setzt den Z‰hler\nauf 0."},
	/* es */ {IDGS_MON_STOPWATCH_DESCRIPTION_ES, "Imprimir contador de ciclos del perifÈrico actual. 'reset' pone el contador a 0."},
	/* fr */ {IDGS_MON_STOPWATCH_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_STOPWATCH_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_STOPWATCH_DESCRIPTION_IT, "Stampa il numero di cicli di CPU del device attuale. 'reset' imposta il contatore a 0."},
	/* ko */ {IDGS_MON_STOPWATCH_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_STOPWATCH_DESCRIPTION_NL, "Toon de CPY cycli teller voor het huidige apparaat. 'reset' zet de teller naar 0."},
	/* pl */ {IDGS_MON_STOPWATCH_DESCRIPTION_PL, "Pokaø licznik cykli CPU obecnego urz±dzenia. 'reset' zeruje licznik."},
	/* ru */ {IDGS_MON_STOPWATCH_DESCRIPTION_RU, "Print the CPU cycle counter of the current device. 'reset' sets the counter to 0."},
	/* sv */ {IDGS_MON_STOPWATCH_DESCRIPTION_SV, "Visa processorcykelr‰knaren fˆr aktuell enhet. \"reset\" s‰tter r‰knaren pÂ 0."},
	/* tr */ {IDGS_MON_STOPWATCH_DESCRIPTION_TR, "Mevcut cihaz˝n CPU cycle sayac˝n˝ yazd˝r. 'reset' sayac˝ 0'a getirir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_UNDUMP_DESCRIPTION,    N_("Read a snapshot of the machine from the file specified.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_UNDUMP_DESCRIPTION_DA, "IndlÊs snapshot af maskinen fra den angivne fil."},
	/* de */ {IDGS_MON_UNDUMP_DESCRIPTION_DE, "Lese einen Snapshot der Maschine aus der angegebenen Datei."},
	/* es */ {IDGS_MON_UNDUMP_DESCRIPTION_ES, "Leer volcado memoria de una m·quina desde el fichero especificado."},
	/* fr */ {IDGS_MON_UNDUMP_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_UNDUMP_DESCRIPTION_HU, "A pillanatkÈp betˆltÈse a megadott f·jlbÛl."},
	/* it */ {IDGS_MON_UNDUMP_DESCRIPTION_IT, "Legge lo snapshot del computer dal file specificato."},
	/* ko */ {IDGS_MON_UNDUMP_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_UNDUMP_DESCRIPTION_NL, "Lees een momentopname voor de machine van het opgegeven bestand."},
	/* pl */ {IDGS_MON_UNDUMP_DESCRIPTION_PL, "Odczytaj zrzut maszyny z okre∂lonego pliku."},
	/* ru */ {IDGS_MON_UNDUMP_DESCRIPTION_RU, "Read a snapshot of the machine from the file specified."},
	/* sv */ {IDGS_MON_UNDUMP_DESCRIPTION_SV, "L‰s en ˆgonblicksbild fˆr maskinen frÂn den angivna filen."},
	/* tr */ {IDGS_MON_UNDUMP_DESCRIPTION_TR, "Belirtilen dosyadan makinenin anl˝k gˆr¸nt¸s¸n¸ oku."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_SYMBOL_TABLE_COMMANDS,    N_("Symbol table commands:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SYMBOL_TABLE_COMMANDS_DA, "Symboltabel-kommandoer:"},
	/* de */ {IDGS_SYMBOL_TABLE_COMMANDS_DE, "Symbol Tabellen Kommandos:"},
	/* es */ {IDGS_SYMBOL_TABLE_COMMANDS_ES, "Tabla sÌmbolo comando:"},
	/* fr */ {IDGS_SYMBOL_TABLE_COMMANDS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_SYMBOL_TABLE_COMMANDS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_SYMBOL_TABLE_COMMANDS_IT, "Comandi tabella dei simboli:"},
	/* ko */ {IDGS_SYMBOL_TABLE_COMMANDS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SYMBOL_TABLE_COMMANDS_NL, "Symbool tabel commandos:"},
	/* pl */ {IDGS_SYMBOL_TABLE_COMMANDS_PL, "Polecenia tablicy symboli:"},
	/* ru */ {IDGS_SYMBOL_TABLE_COMMANDS_RU, "Symbol table commands:"},
	/* sv */ {IDGS_SYMBOL_TABLE_COMMANDS_SV, "Kommandon fˆr symboltabell:"},
	/* tr */ {IDGS_SYMBOL_TABLE_COMMANDS_TR, "Sembol tablosu komutlar˝:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_LABEL,    N_("label")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_LABEL_DA, "etiket"},
	/* de */ {IDGS_LABEL_DE, "Bezeichner"},
	/* es */ {IDGS_LABEL_ES, "Etiqueta"},
	/* fr */ {IDGS_LABEL_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_LABEL_HU, ""},  /* fuzzy */
	/* it */ {IDGS_LABEL_IT, "etichetta"},
	/* ko */ {IDGS_LABEL_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_LABEL_NL, "label"},
	/* pl */ {IDGS_LABEL_PL, "label"},
	/* ru */ {IDGS_LABEL_RU, "label"},
	/* sv */ {IDGS_LABEL_SV, "etikett"},
	/* tr */ {IDGS_LABEL_TR, "etiket"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_ADD_LABEL_DESCRIPTION,    N_("<memspace> is one of: C: 8: 9: 10: 11:\n<address>  is the address which should get the label.\n<label>    is the name of the label; it must start with a dot (\".\").\n\nMap a given address to a label.  This label can be used when entering\nassembly code and is shown during disassembly.  Additionally, it can\nbe used whenever an address must be specified.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_ADD_LABEL_DESCRIPTION_DA, "<huk.omrÂde>   er en af C: 8: 9: 10: eller 11:\n<adresse>      Er adressen som skal have etiketten.\n<etiket>       er navnet pÂ etiketten; skal starte med punktum (\".\").\n\nSÊt en etiket for en adresse. Etiketten kan angives nÂr der indtastes\nassemblerkode, og vises ved disassemblering. Desuden kan den bruges\nhvor en adresse skal angives."},
	/* de */ {IDGS_MON_ADD_LABEL_DESCRIPTION_DE, "<Speicherbereich> ist aus: C: 8: 9: 10: 11:\n<Adresse>         bezeichnet die Adresse welche mit dem Bezeichner assoziert werden soll.\n<Bezeichner>      Name des Bezeichners; Muss mit einem Punkt (\".\") starten.\n\nAssoziiert einen Bezeichner mit einer Adresse. Dieser Bezeichner kann \nbei der Eingabe von Asssmblercode benutzt werden und wird auch beim\nDisassemblieren gezeigt. Dar¸ber hinaus kann der Bezeichner ¸berall\ndort genutzt werden, wo eine Adresseingabe nˆtig ist."},
	/* es */ {IDGS_MON_ADD_LABEL_DESCRIPTION_ES, "<espacio memoria> es uno de: C: 8: 9: 10: 11:\n<direcciÛn>  es la direcciÛn donde estar· la etiquetal.\n<letiqueta>   es el nombre de la etiqueta; debe empezar con un punto (\".\").\n\nMapea la direcciÛn dada a una etiqueta que se usar· cuando se inserte\ncÛdigo ensamblador y se mostrar· durante el desensamblado.  Adicionalmente\npuede ser usada siempre que se deba especificar una direcciÛn."},
	/* fr */ {IDGS_MON_ADD_LABEL_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_ADD_LABEL_DESCRIPTION_HU, "A <memÛria tÈr> ezek kˆz¸l: C: 8: 9: 10: 11:\n<cÌm>  amelyik cÌmhez a cÌmkÈt rendelje.\n<cÌmke>    a cÌmke neve; ponttal kell kezdıdjˆn (\".\").\n\nAz adott cÌm rendelÈse a cÌmkÈhez.  Ez a cÌmke haszn·lhatÛ assembly\nprogram beÌr·sakor, Ès visszafejtÈskor megjelenik.  Mindig haszn·lhatÛ,\namikor valamilyen cÌmet kell megadni."},
	/* it */ {IDGS_MON_ADD_LABEL_DESCRIPTION_IT, "<spazio di memoria> Ë uno tra: C: 8: 9: 10: 11:\n<indirizzo> Ë l'indirizzo a cui deve essere associata l'etichettal.\n<etichetta> Ë il nome dell'etichetta; deve iniziare con un punto (\".\").\n\nAssocia l'indirizzo specificato all'etichetta. Questa etichetta puÚ\nessere usata quando si inserisce codice assembly ed Ë mostrata\nnella disassemblazione. In aggiunta, puÚ essere usata ogni volta che\ndeve essere specificato un indirizzo."},
	/* ko */ {IDGS_MON_ADD_LABEL_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_ADD_LABEL_DESCRIPTION_NL, "<geheugenruimte> is een van: C: 8: 9: 10: 11:\n<adres>          is het adres waaraan de label gekoppelt moet worden.\n<label>          is de naam van de label; de naam moet beginnen met een punt\n                 (\".\").\n\nKoppel een opgegeven adres aan een label. Dit label kan worden gebruikt bij\nhet invoeren van assembleer code en wordt getoont bij een disassemblering.\nTevens kan de label gebruikt worden in plaats van het adres."},
	/* pl */ {IDGS_MON_ADD_LABEL_DESCRIPTION_PL, "<memspace> to jeden z: C: 8: 9: 10: 11:\n<address> to adres, pod ktÛry ma i∂Ê notatka.\n<label> to nazwa notatki, musi zaczynaÊ siÍ kropk± (\".\").\n\nMapuje dany adres pod notatkÍ. Tej notatki moøna uøywaÊ\nprzy wprowadzaniu kodu asemblowania, a pokazywana jest\npodczas deasemblowania. Do tego moøna jest uøywaÊ\nzawsze gdy trzeba okre∂liÊ adres."},
	/* ru */ {IDGS_MON_ADD_LABEL_DESCRIPTION_RU, "<memspace> is one of: C: 8: 9: 10: 11:\n<address>  is the address which should get the label.\n<label>    is the name of the label; it must start with a dot (\".\").\n\nMap a given address to a label.  This label can be used when entering\nassembly code and is shown during disassembly.  Additionally, it can\nbe used whenever an address must be specified."},
	/* sv */ {IDGS_MON_ADD_LABEL_DESCRIPTION_SV, "<minnesomrÂde> ‰r en av: C: 8: 9: 10: 11:\n<adress>       ‰r adressen som ska fÂ etiketten.\n<etikett>      ‰r namnet pÂ etiketten; mÂste starta med punkt (\".\").\n\nKoppla en adress till en etikett. Etiketten kan anges n‰r assemblerkod\nmatas in och visas vid disassemblering. I till‰gg kan den anv‰ndas\nn‰rhelst en adress mÂste anges."},
	/* tr */ {IDGS_MON_ADD_LABEL_DESCRIPTION_TR, "<bellekalan˝> bunlardan biridir: C: 8: 9: 10: 11:\n<adres>       etiketin duraca˝ adresi belirler.\n<etiket>      etiketin ismidir; nokta karakteriyle ba˛lamal˝d˝r (\".\").\n\nEtiketi verilen adrese e˛le˛tir.  Bu etiket assembly kod girilirken kullan˝l˝r\nve disassembly s˝ras˝nda gˆsterilir.  Ek olarak, ne zaman bir adres\nbelirtilmesi gerekse kullan˝labilir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DELETE_LABEL_DESCRIPTION,    N_("<memspace> is one of: C: 8: 9: 10: 11:\n<label>    is the name of the label; it must start with a dot (\".\").\n\nDelete a previously defined label.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_DA, "<huk.omrÂde>   er en af C: 8: 9: 10: eller 11:\n<etiket>       er navnet pÂ etiketten; skal starte med punktum (\".\").\n\nFjern en tidligere oprettet etiket."},
	/* de */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_DE, "<Speicherbereich> ist aus: C: 8: 9: 10: 11:\n<Bezeichner>      Name des Bezeichners; Muss mit einem Punkt (\".\") starten.\n\nLˆscht einen zuvor definierten Bezeichner."},
	/* es */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_ES, "<espacio memoria> es uno de: C: 8: 9: 10: 11:\n<letiqueta>    es el nombre de la etiqueta; y debe comenzar por un punto (\".\").\n\nBorrar una etiqueta previamente definida."},
	/* fr */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_HU, "<memÛria tÈr> egy ezek kˆz¸l: C: 8: 9: 10: 11:\n<cÌmke>    a cÌmke neve; ponttal kell kezdıdjˆn (\".\").\n\nElızıleg megadott cÌmke tˆrlÈse."},
	/* it */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_IT, "<spazio di memoria> Ë uno tra: C: 8: 9: 10: 11:\n<etichetta> Ë il nome dell'etichetta; deve iniziare con un punto (\".\").\n\nCancella una etichetta definita precedentemente."},
	/* ko */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_NL, "<geheugenruimte> is een van: C: 8: 9: 10: 11:\n<label>          is de naam van de label; de naam moet beginnen met een\npunt (\".\").\n\nVerwijder een gekoppelde label."},
	/* pl */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_PL, "<memspace> to jeden z: C: 8: 9: 10: 11:\n<label> to nazwa notatki, musi zaczynaÊ siÍ kropk± (\".\").\n\nKasuje poprzednio zdefiniowan± notatkÍ."},
	/* ru */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_RU, "<memspace> is one of: C: 8: 9: 10: 11:\n<label>    is the name of the label; it must start with a dot (\".\").\n\nDelete a previously defined label."},
	/* sv */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_SV, "<minnesomrÂde> ‰r en av: C: 8: 9: 10: 11:\n<etikett>      ‰r namnet pÂ etiketten; mÂste starta med punkt (\".\").\n\nTa bort en tidigare angiven etikett."},
	/* tr */ {IDGS_MON_DELETE_LABEL_DESCRIPTION_TR, "<bellekalan˝> bunlardan biridir: C: 8: 9: 10: 11:\n<etiket>      etiketin ismidir; nokta karakteriyle ba˛lamal˝d˝r (\".\").\n\n÷nceden tan˝mlanm˝˛ bir etiketi sil."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_LOAD_LABELS_DESCRIPTION,    N_("Load a file containing a mapping of labels to addresses.  If no memory\nspace is specified, the default readspace is used.\n\nThe format of the file is the one written out by the `save_labels' command;\nit consists of some `add_label' commands, written one after the other.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_DA, "IndlÊs en fil som indeholder mapning fra labels til adresser.\nHvis der ikke angives hukommelsesomrÂde, anvendes det normale lÊseomrÂde.\n\nFormatet pÂ filen er det, som skrives af \"save_labels\"-kommandoen;\ndet bestÂr af \"add_label\"-kommandoer efter hinanden."},
	/* de */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_DE, "L‰dt eine Datei mit Zuordnung von Adressen zu Bezeichnern. Wenn kein \nSpeicherbereich angegeben wurde, wird der Standard Speicherplatz\nverwendet. Das Format der Datei wird durch das Kommande `save_lables'\ndefiniert. Es besteht aus eine Reihe von `add_label' Kommandos,\nhintereinander angeordnet."},
	/* es */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_ES, "Carga fichero conteniendo mapeado de etiquetas de direcciones.  Si no\nhay espacio de memoria especificado, se usa el espacio por defecto.\n\nEl formato de fichero es el usado por el comando grabar etiquetas;\nConsiste en algunos comandos`aÒadir etiquetal' , grabado uno despues del otro."},
	/* fr */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_HU, "CÌmkÈkrıl cÌmekre lekÈpezÈseket tartalmazÛ f·jl betˆltÈse.  Ha nincs memÛria\ntÈr megadva, az alap tÈr lesz haszn·lva.\n\nA f·jl form·tuma megegyezik a `save_labels' parancs ·ltal kiÌrtÈval;\nnÈh·ny egym·s ut·n Ìrt `add_label' parancsbÛl ·ll."},
	/* it */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_IT, "Carica un file che contiente l'associazione tra le etichette e gli indirizzi.\nSe non Ë specificato alcuno spazio di memoria, viene usato lo spazio\ndi lettura predefinito.\n\nIl formato del file Ë quello dato in output dal comando `save_labels';\nË composto da alcuni comandi `add_label', scritti uno di seguito all'altro."},
	/* ko */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_NL, "Laad een bestand met de koppelingen tussen labels en adressen. Als er geen\ngeheugenruimte is opgegeven zal de standaard geheugenruimte worden gebruikt.\nHet formaat van het bestand is die door het commando 'save_labels' wordt\ngeschreven; het bestaat uit een aantal 'add_label' commandos na elkaar."},
	/* pl */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_PL, "Wczytuje plik zawieraj±cy mapowanie notatek pod adresy. Je∂li nie\nokre∂lono zakresu pamiÍci, uøywany jest domy∂lny zakres pamiÍci.\n\nFormat pliku jest zapisywany komend±`save_labels',\nktÛra sk≥ada siÍ z komend `add_label', zapisanych jedna po drugiej."},
	/* ru */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_RU, "Load a file containing a mapping of labels to addresses.  If no memory\nspace is specified, the default readspace is used.\n\nThe format of the file is the one written out by the `save_labels' command;\nit consists of some `add_label' commands, written one after the other."},
	/* sv */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_SV, "L‰s in en fil som innehÂller koppling frÂn etiketter till adresser.\nOm inget minnesomrÂde anges anv‰ndas standard-l‰sadressen.\n\nFormatet pÂ filen ‰r samma som skrivs av \"save_labels\"-kommandot;\ndet bestÂr av nÂgra \"add_label\"-kommandon efter varandra."},
	/* tr */ {IDGS_MON_LOAD_LABELS_DESCRIPTION_TR, "Etiketleri adreslerle e˛le˛tirilmi˛ bir dosya y¸kleyin.  Eer bellek\nalan˝ belirtilmemi˛se, varsay˝lan okuma alan˝ kullan˝l˝r.\n\nDosyan˝n biÁimi `save_labels' komutu ile yaz˝lm˝˛ oland˝r;\nbu pe˛ pe˛e yaz˝lm˝˛ `add_label' komutlar˝ndan ibarettir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_SAVE_LABELS_DESCRIPTION,    N_("Save labels to a file.  If no memory space is specified, all of the\nlabels are saved.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_DA, "Gem etiketter til fil. Hvis der ikke angives et hukommelsesomrÂde\ngemmes alle etiketter."},
	/* de */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_DE, "Speichere Bezeichner in eine Datei. Wenn kein Speicherbereich\nangegeben wurde, werden alle Bezeichner gespeichert."},
	/* es */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_ES, "Grabar etiquetas en fichero. Si no se define espacio de memoria,\nse graban todas las etiquetas."},
	/* fr */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_HU, "CÌmkÈk mentÈse f·jlba.  Ha nincs memÛria tartom·ny megadva, az\nˆsszes cÌmkÈt menti."},
	/* it */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_IT, "Salva le etichette su file. Se non Ë specificato alcuno spazio di memoria,\nvengono salvate tutte le etichette."},
	/* ko */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_NL, "Sla de labels op in een bestand. Als er geen geheugenruimte is opgegeven\nworden alle labels opgeslagen."},
	/* pl */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_PL, "Zapisuje notatki do pliku. Je∂li nie okre∂lono obszaru pamiÍci,\nzapisywanie s± wszystkie notatki."},
	/* ru */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_RU, "Save labels to a file.  If no memory space is specified, all of the\nlabels are saved."},
	/* sv */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_SV, "Spara etiketter till en fil. Om inget minnesomrÂde anges sparas alla\netiketterna."},
	/* tr */ {IDGS_MON_SAVE_LABELS_DESCRIPTION_TR, "Etiketleri bir dosyaya kaydet.  Eer bellek alan˝ belirtilmemi˛se, t¸m\netiketler kaydedilir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_SHOW_LABELS_DESCRIPTION,    N_("Display current label mappings.  If no memory space is specified, show\nall labels.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_DA, "Vis aktuelle etiketter. Hvis der ikke angives et hukommelsesomrÂde vises\nalle etiketter."},
	/* de */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_DE, "Zeige aktuelle Bezeichner Zuordnungen. Wenn kein Speicherbereich angegeben\nwurde, werden alle Bezeichner gezeigt."},
	/* es */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_ES, "Muestra mapeado de etiquetas actual. Si no se especifica espacio de\nmemoria, muestra todas las etiquetas."},
	/* fr */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_HU, "Az aktu·lis cÌmke lekÈpezÈsek mutat·sa.  Ha nincs a memÛria tÈr megadva, az\nˆsszeset mutatja."},
	/* it */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_IT, "Mostra l'associazione delle etichette correnti. Se non Ë specificato alcun\nspazio di memoria, verranno mostrate tutte le etichette."},
	/* ko */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_NL, "Toon huidige label koppelingen. Als er geen geheugenruimte is opgegeven\nworden all labels getoont."},
	/* pl */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_PL, "Pokazuje obecne mapowania notatek. Je∂li nie okre∂lono obszaru pamiÍci,\npokazuje wszystkie notatki."},
	/* ru */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_RU, "Display current label mappings.  If no memory space is specified, show\nall labels."},
	/* sv */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_SV, "Visar aktuella etiketter. Om inget minnesomrÂde anges visas alla\netiketter."},
	/* tr */ {IDGS_MON_SHOW_LABELS_DESCRIPTION_TR, "GeÁerli etiket e˛le˛melerini gˆr¸nt¸le.  Eer bellek alan˝ belirtilmemi˛se,\nt¸m etiketleri gˆster."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS,    N_("Assembler and memory commands:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_DA, "Assembler- og hukommelseskommandoer:"},
	/* de */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_DE, "Assembler und Speicher Kommandos:"},
	/* es */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_ES, "Comandos Ensamblador y de memoria:"},
	/* fr */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_IT, "Comandi assembler e memoria:"},
	/* ko */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_NL, "Assembler en geheugen commandos:"},
	/* pl */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_PL, "Asembler i polecenia pamiÍci:"},
	/* ru */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_RU, "Assembler and memory commands:"},
	/* sv */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_SV, "Assembler- och minneskommandon:"},
	/* tr */ {IDGS_ASSEMBLER_AND_MEMORY_COMMANDS_TR, "Assembler ve bellek komutlar˝:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_DATA_LIST,    N_("data_list")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DATA_LIST_DA, "dataliste"},
	/* de */ {IDGS_DATA_LIST_DE, "Datenliste"},
	/* es */ {IDGS_DATA_LIST_ES, "lista datos"},
	/* fr */ {IDGS_DATA_LIST_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_DATA_LIST_HU, ""},  /* fuzzy */
	/* it */ {IDGS_DATA_LIST_IT, "lista di dati"},
	/* ko */ {IDGS_DATA_LIST_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_DATA_LIST_NL, "data_lijst"},
	/* pl */ {IDGS_DATA_LIST_PL, "data_list"},
	/* ru */ {IDGS_DATA_LIST_RU, "data_list"},
	/* sv */ {IDGS_DATA_LIST_SV, "datalista"},
	/* tr */ {IDGS_DATA_LIST_TR, "veri_listesi"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_WRITE_DESCRIPTION,    N_("Write the specified data at `address'.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_WRITE_DESCRIPTION_DA, "Gem angivne data pÂ \"adresse\"."},
	/* de */ {IDGS_MON_WRITE_DESCRIPTION_DE, "Schreibe das angegebene Datum auf `Adresse'."},
	/* es */ {IDGS_MON_WRITE_DESCRIPTION_ES, "Grabar el dato especificado en `direcciÛn'."},
	/* fr */ {IDGS_MON_WRITE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_WRITE_DESCRIPTION_HU, "A megadott adat `cÌm' helyre Ìr·sa."},
	/* it */ {IDGS_MON_WRITE_DESCRIPTION_IT, "Scrive il dato specificato all'indirizzo."},
	/* ko */ {IDGS_MON_WRITE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_WRITE_DESCRIPTION_NL, "Schrijf de opgegevem data op `adres'."},
	/* pl */ {IDGS_MON_WRITE_DESCRIPTION_PL, "Zapisuje okre∂lone dane w 'adresie'."},
	/* ru */ {IDGS_MON_WRITE_DESCRIPTION_RU, "Write the specified data at `address'."},
	/* sv */ {IDGS_MON_WRITE_DESCRIPTION_SV, "Skriv angiven data pÂ \"adress\"."},
	/* tr */ {IDGS_MON_WRITE_DESCRIPTION_TR, "`adres' bˆl¸m¸nde belirlenmi˛ bir veri yaz."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_INSTRUCTION,    N_("instruction")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_INSTRUCTION_DA, "instruktion"},
	/* de */ {IDGS_INSTRUCTION_DE, "Instruktion"},
	/* es */ {IDGS_INSTRUCTION_ES, "InstrucciÛn"},
	/* fr */ {IDGS_INSTRUCTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_INSTRUCTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_INSTRUCTION_IT, "istruzione"},
	/* ko */ {IDGS_INSTRUCTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_INSTRUCTION_NL, "instructie"},
	/* pl */ {IDGS_INSTRUCTION_PL, "instruction"},
	/* ru */ {IDGS_INSTRUCTION_RU, "instruction"},
	/* sv */ {IDGS_INSTRUCTION_SV, "instruktion"},
	/* tr */ {IDGS_INSTRUCTION_TR, "komut"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_ASSEMBLE_DESCRIPTION,    N_("Assemble instructions to the specified address.  If only one\ninstruction is specified, enter assembly mode (enter an empty line to\nexit assembly mode).")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_ASSEMBLE_DESCRIPTION_DA, "Skriv assemblerinstruktioner til adresse. Hvis kun en instruktion\nangives, skiftes til assembler-tilstand (indtast en tom linje for\nat afslutte assembler-tilstanden)."},
	/* de */ {IDGS_MON_ASSEMBLE_DESCRIPTION_DE, "Assmbler Instruktionen zur angebenen Adresse. Wenn nur eine Instruktion\nangegeben wurde, wird der assemblier Modus aktiviert (Eingabe einer leeren\nZeile beendet den assemblier Modus)."},
	/* es */ {IDGS_MON_ASSEMBLE_DESCRIPTION_ES, "Ensambla instrucciones en la direcciÛn especificada.  Si sÛlo se\nespecifica una instrucciÛn, entra en modo ensamblador, (entrar \nuna linea vacia para salir)."},
	/* fr */ {IDGS_MON_ASSEMBLE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_ASSEMBLE_DESCRIPTION_HU, "UtasÌt·sok fordÌt·sa a megadott cÌmre. Ha csak egy utasÌt·s\nvan, fordÌtÛ mÛdba lÈp (¸res sort kell beÌrni a kilÈpÈshez)."},
	/* it */ {IDGS_MON_ASSEMBLE_DESCRIPTION_IT, "Assembla le istruzioni a partire dall'indirizzo specificato. Se solo una\nistruzione Ë specificata, entra in modalit‡ assembly (inserire una\nlinea vuota per uscire da questa modalit‡)."},
	/* ko */ {IDGS_MON_ASSEMBLE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_ASSEMBLE_DESCRIPTION_NL, "Assembleer instructies naar het opgegeven adres. Als er alleen een instructie\nis opgegeven dan wordt de assembleer modus ingeschakelt (geef een lege regel\nin om de assembleer modus te verlaten)."},
	/* pl */ {IDGS_MON_ASSEMBLE_DESCRIPTION_PL, "Assembluje instrukcje pod podanym adresem. Je∂li podano tylko\njedn± instrukcjÍ, wchodzi w tryb asemblowania (pusta linia\nwychodzi z trybu asemblowania)."},
	/* ru */ {IDGS_MON_ASSEMBLE_DESCRIPTION_RU, "Assemble instructions to the specified address.  If only one\ninstruction is specified, enter assembly mode (enter an empty line to\nexit assembly mode)."},
	/* sv */ {IDGS_MON_ASSEMBLE_DESCRIPTION_SV, "Assemblera instruktioner till angiven adress. Om endast en\ninstruktion angavs, aktivera assemblerl‰ge (mata in en tom rad\nfˆr att avsluta assemblerl‰get)."},
	/* tr */ {IDGS_MON_ASSEMBLE_DESCRIPTION_TR, "Komutlar˝ belirlenmi˛ adrese Áevir.  Eer yaln˝zca bir\nkomut belirlenmi˛se, assembly moduna gir (assembly modundan Á˝kmak iÁin\nbo˛ bir sat˝r girin)."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_ADDRESS_RANGE,    N_("address_range")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ADDRESS_RANGE_DA, "adresseomrÂde"},
	/* de */ {IDGS_ADDRESS_RANGE_DE, "Adressbereich"},
	/* es */ {IDGS_ADDRESS_RANGE_ES, "Rango de direcciÛn"},
	/* fr */ {IDGS_ADDRESS_RANGE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ADDRESS_RANGE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_ADDRESS_RANGE_IT, "intervallo indirizzi"},
	/* ko */ {IDGS_ADDRESS_RANGE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ADDRESS_RANGE_NL, "adres_bereik"},
	/* pl */ {IDGS_ADDRESS_RANGE_PL, "address_range"},
	/* ru */ {IDGS_ADDRESS_RANGE_RU, "address_range"},
	/* sv */ {IDGS_ADDRESS_RANGE_SV, "adressomrÂde"},
	/* tr */ {IDGS_ADDRESS_RANGE_TR, "adres_aral˝˝"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_COMPARE_DESCRIPTION,    N_("Compare memory from the source specified by the address range to the\ndestination specified by the address.  The regions may overlap.  Any\nvalues that miscompare are displayed using the default displaytype.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_COMPARE_DESCRIPTION_DA, "Sammenlign hukommelse fra kilden, angivet ved adresseomrÂdet med\nmÂlet, angivet ved adresse. OmrÂderne kan overlappe. Alle vÊrdier\nsom er forskellige vil blive vist med standard visning."},
	/* de */ {IDGS_MON_COMPARE_DESCRIPTION_DE, "Vergleiche angegebenen Adressbereich mit der Zieladresse.\nDie Bereiche kˆnnen ¸berlappen. Ungleiche Werte werden mit dem\nStandardanzeigetyp gezeigt."},
	/* es */ {IDGS_MON_COMPARE_DESCRIPTION_ES, "Compara memoria desde la fuente especificada por el rango de direcciones\ndestino. La regiÛn puede estar superpuesta. Cualquier valor diferente se\nmostrar· usando el tipo de pantalla por defecto."},
	/* fr */ {IDGS_MON_COMPARE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_COMPARE_DESCRIPTION_HU, "A forr·s memÛriatartom·ny ˆsszehasonlÌt·sa a cÈllal megadott\nmemÛriatartom·nnyal. A tartom·nyok ·tfedÈse megengedett.  Minden\nmeg nem egyezı ÈrtÈket kiÌr az alap adat tÌpussal."},
	/* it */ {IDGS_MON_COMPARE_DESCRIPTION_IT, "Confronta la memoria della sorgente specificata dall'intervallo di\nindirizzi con la destinazione specificata dall'indirizzo. Le regioni possono\nsovrapporsi. Qualsiasi valore che non corrisponde Ë visualizzato\nutilizzando il tipo di dato predefinito."},
	/* ko */ {IDGS_MON_COMPARE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_COMPARE_DESCRIPTION_NL, "Vergelijk geheugen van de bron opgegeven door de adres reeks met het doel\nopgegeven door het adres. De reeksen mogen overlappen. De data die niet\ngelijk is zal worden getoont volgens de huidige toon soort."},
	/* pl */ {IDGS_MON_COMPARE_DESCRIPTION_PL, "PorÛwnuje pamiÍÊ z podanego zakresu adresÛw z podanym adresem.\nRejony mog± siÍ pokrywaÊ. Wszystkie niepasuj±ce warto∂ci s± pokazane\ndomy∂lnym typem danych."},
	/* ru */ {IDGS_MON_COMPARE_DESCRIPTION_RU, "Compare memory from the source specified by the address range to the\ndestination specified by the address.  The regions may overlap.  Any\nvalues that miscompare are displayed using the default displaytype."},
	/* sv */ {IDGS_MON_COMPARE_DESCRIPTION_SV, "J‰mfˆr minne frÂn k‰llan som anges av adressomrÂdet mot destinationen\nsom anges av adressen. OmrÂdena kan vara ˆverlappande. Alla v‰rden\nsom skiljer sig vid j‰mfˆrelsen visas med standardvisningss‰ttet."},
	/* tr */ {IDGS_MON_COMPARE_DESCRIPTION_TR, "Bellei adresle belirtilen kaynaktan adresle belirtilen hedefin bulunduu\naral˝kta kar˛˝la˛t˝r.  Bˆlgeler belki ¸st ¸ste binebilir.  Uyu˛mayan\nherhangi bir deer varsay˝lan gˆr¸nt¸leme tipine bal˝ olarak gˆr¸nt¸lenir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_CHECKNUM,    N_("checknum")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CHECKNUM_DA, "checknum"},
	/* de */ {IDGS_CHECKNUM_DE, "Checknummer"},
	/* es */ {IDGS_CHECKNUM_ES, "n˙mero comprobaciÛn"},
	/* fr */ {IDGS_CHECKNUM_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_CHECKNUM_HU, ""},  /* fuzzy */
	/* it */ {IDGS_CHECKNUM_IT, "checknum"},
	/* ko */ {IDGS_CHECKNUM_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CHECKNUM_NL, "checknum"},
	/* pl */ {IDGS_CHECKNUM_PL, "checknum"},
	/* ru */ {IDGS_CHECKNUM_RU, "checknum"},
	/* sv */ {IDGS_CHECKNUM_SV, "kontrollnr"},
	/* tr */ {IDGS_CHECKNUM_TR, "kontrolnumaras˝"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DELETE_DESCRIPTION,    N_("Delete checkpoint `checknum'.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DELETE_DESCRIPTION_DA, "Slet checkpoint \"checknum\"."},
	/* de */ {IDGS_MON_DELETE_DESCRIPTION_DE, "Lˆsche Checkpoint `Checknummer'."},
	/* es */ {IDGS_MON_DELETE_DESCRIPTION_ES, "Borrar punto comprobaciÛn `n˙mero comprobaciÛn'."},
	/* fr */ {IDGS_MON_DELETE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DELETE_DESCRIPTION_HU, "`ell_pont_sz·m' ellenırzÈsi pont tˆrlÈse."},
	/* it */ {IDGS_MON_DELETE_DESCRIPTION_IT, "Cancella il punto di controllo `checknum'."},
	/* ko */ {IDGS_MON_DELETE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DELETE_DESCRIPTION_NL, "Verwijder checkpunt `checknum'."},
	/* pl */ {IDGS_MON_DELETE_DESCRIPTION_PL, "UsuÒ punkt kontrolny `checknum'."},
	/* ru */ {IDGS_MON_DELETE_DESCRIPTION_RU, "Delete checkpoint `checknum'."},
	/* sv */ {IDGS_MON_DELETE_DESCRIPTION_SV, "Ta bort kontrollpunkt \"kontrollnr\"."},
	/* tr */ {IDGS_MON_DELETE_DESCRIPTION_TR, "`kontrolnumaras˝' kontrol noktas˝n˝ sil."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DISASS_DESCRIPTION,    N_("Disassemble instructions.  If two addresses are specified, they are\nused as a start and end address.  If only one is specified, it is\ntreated as the start address and a default number of instructions are\ndisassembled.  If no addresses are specified, a default number of\ninstructions are disassembled from the dot address.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DISASS_DESCRIPTION_DA, "DisassemblÈr instruktioner. Hvis der angives to adresser anvendes disse\nsom start- og slutadresse. Angives kun en adresse bruges denne som startadresse\nog et standard antal instruktioner disassembleres. Hvis ingen adresse\nangives disassembleres et standard antal instruktioner fra den aktuelle\nadresse."},
	/* de */ {IDGS_MON_DISASS_DESCRIPTION_DE, "Disassembliere Instruktionen. Wenn zwei Adressen angegeben werden,\nwerden diese als Start- und Zieladresse interpretiert. Wenn nur eine\nAdress angegeben wird, wird diese asl Startadresse interpretiert und\ndie Standardanzahl an Instruktionen werden disassembliert. Wenn keine\nAdresse angegeben wird, wird von der aktuellen Adresse disassembliert."},
	/* es */ {IDGS_MON_DISASS_DESCRIPTION_ES, "Desensamblar instrucciones. Si se especifican dos direcciones, se\nusan como direcciones de inicio y final. Si solo se suministra una, ser·\ntratada como direcciÛn de inicio y un n˙mero por defecto de  instrucciones\nser·n desensambladas. Si no se especifica ninguna direcciÛn, un n˙mero\npor defecto de instrucciones se desensamblaran desde la direcciÛn pre\ndefinida"},
	/* fr */ {IDGS_MON_DISASS_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DISASS_DESCRIPTION_HU, "UtasÌt·sok visszafejtÈse. Ha kÈt cÌm van megadva, elsı Ès utolsÛ\ncÌmkÈnt Èrtelmezi ıket. Ha csak egy, akkor elsı cÌmkÈnt, Ès az alap\nsz·m˙ utasÌt·s ker¸l visszafejtÈsre. Ha nincs cÌm megadva, az aktu·lis\ncÌmtıl kezdi a visszafejtÈst, Ès a szok·sos sz·m˙ utasÌt·st Ìr ki."},
	/* it */ {IDGS_MON_DISASS_DESCRIPTION_IT, "Disassembla le istruzioni. Se sono specificati due indirizzi, questi\nsono utilizzati come indirizzo di inizio e fine. Se ne viene specificato\nsolo uno, Ë usato come indirizzo di partenza e viene disassemblato\nil numero di istruzioni predefinito. Se non viene specificato nessun\nindirizzo, viene disassemblato il numero di istruzioni predefinito\ndall'indirizzo dot."},
	/* ko */ {IDGS_MON_DISASS_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DISASS_DESCRIPTION_NL, "Disassembleer instructies. Als er twee adressen zijn opgegeven dan worden\ndeze gebruikt als een start en eind adres. Als er maar een adres is\nopgegeven dan wordt deze gebruikt als het start adres en een standaard\naantal instructies zal worden gedisassembleerd. Als er geen adressen zijn\nopgegeven dan wordt een standaard aantal instructies gedisassembleerd vanaf\nhet huidige adres."},
	/* pl */ {IDGS_MON_DISASS_DESCRIPTION_PL, "Deasembluje instrukcje. Je∂li podano dwa adresy, uøywane s± jako\nadres pocz±tkowy i koÒcowy. Je∂li podano tylko jeden, jest uøywany\njako adres pocz±tkowy i deasemblowana jest domy∂lna liczba instrukcji\nz adresu dot."},
	/* ru */ {IDGS_MON_DISASS_DESCRIPTION_RU, "Disassemble instructions.  If two addresses are specified, they are\nused as a start and end address.  If only one is specified, it is\ntreated as the start address and a default number of instructions are\ndisassembled.  If no addresses are specified, a default number of\ninstructions are disassembled from the dot address."},
	/* sv */ {IDGS_MON_DISASS_DESCRIPTION_SV, "Disassemblera instruktioner. Om tvÂ adresser anges anv‰nds de som\nstart- och slutadress. Om endast en anges anv‰nds den som startadress\noch ett standardantal instruktioner disassembleras. Om ingen adress\nanges disassembleras ett standardantal instruktioner frÂn punktadressen."},
	/* tr */ {IDGS_MON_DISASS_DESCRIPTION_TR, "Komutlar˝ disassemble et.  Eer iki adres girildiyse, bunlar ba˛lang˝Á\nve biti˛ adresleri olarak kullan˝l˝r.  Eer tek adres girildiyse, bu\nadres ba˛lang˝Á adresi olarak kabul edilir ve varsay˝lan say˝da komutlar\ndisassemble edilir.  Eer hiÁ adres girilmediyse, varsay˝lan say˝da\nkomutlar nokta ba˛lang˝Á adresinden itibaren disassemble edilir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_FILL_DESCRIPTION,    N_("Fill memory in the specified address range with the data in\n<data_list>.  If the size of the address range is greater than the size\nof the data_list, the data_list is repeated.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_FILL_DESCRIPTION_DA, "Fyld hukommelsen i det angivne adresseomrÂde med data fra <dataliste>.\nHvis st¯rrelsen pÂ adresseomrÂdet er st¯rre end st¯rrelsen af dataliste\ngentages indholdet i dataliste."},
	/* de */ {IDGS_MON_FILL_DESCRIPTION_DE, "F¸lle den angegebenen Adressbereich mit den Daten aus <Datenliste>.\nWenn die Grˆﬂe des Adressbereichs grˆﬂer als <Datenliste> ist, werden\ndie Daten wiederholt."},
	/* es */ {IDGS_MON_FILL_DESCRIPTION_ES, "Rellenar memoria en el rango especificado con el dato contenido en\n <lista datos>. Si el tamaÒo del rango es mayor que el <lista datos>\nse repite lista datos."},
	/* fr */ {IDGS_MON_FILL_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_FILL_DESCRIPTION_HU, "A memÛria kitˆltÈse az <adat_lista> paramÈterben megadott adatokkal.\nHa a cÌmtartom·ny nagyobb, mint a lista, ismÈtelni fogja azt."},
	/* it */ {IDGS_MON_FILL_DESCRIPTION_IT, "Riempe la memoria nell'intervallo di indirizzi specificato con i dati\npresenti in <lista di dati>. Se la dimensione dell'intervallo Ë maggiore\ndella dimensione della lista di dati, la lista di dati Ë ripetuta."},
	/* ko */ {IDGS_MON_FILL_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_FILL_DESCRIPTION_NL, "Vul het geheugen van de opgegeven adres reeks op met de data in <data_lijst>.\nAls de grootte van de adres reeks groter is dan de grootte van de data_lijst\ndan zal de data_lijst worder herhaald."},
	/* pl */ {IDGS_MON_FILL_DESCRIPTION_PL, "Wype≥nia pamiÍÊ w danym zakresie adresÛw danymi z <lista_danych>.\nJe∂li wielko∂Ê zakresu adresÛw jest wiÍksza niø wielko∂Ê listy_danych,\nlista_danych jest powtarzana."},
	/* ru */ {IDGS_MON_FILL_DESCRIPTION_RU, "Fill memory in the specified address range with the data in\n<data_list>.  If the size of the address range is greater than the size\nof the data_list, the data_list is repeated."},
	/* sv */ {IDGS_MON_FILL_DESCRIPTION_SV, "Fyll minnet i det angivna omrÂdet med data i <datalista>.\nOm storleken pÂ adressomrÂdet ‰r stˆrre ‰n storleken pÂ datalistan\nrepeteras innehÂllet i datalistan."},
	/* tr */ {IDGS_MON_FILL_DESCRIPTION_TR, "<veri_listesi>'nde bulunan verilerle belirtilen bellek aral˝˝n˝ doldur.\nEer verilen adres aral˝˝ veri_listesi'nden b¸y¸kse, veri_listesi'nde\nyer alan veriler tekrar ettirilir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_HUNT_DESCRIPTION,    N_("Hunt memory in the specified address range for the data in\n<data_list>.  If the data is found, the starting address of the match\nis displayed.  The entire range is searched for all possible matches.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_HUNT_DESCRIPTION_DA, "S¯g i hukommelsen i det angivne dataomrÂde efter <dataliste>.\nHvis data findes vises startadressen for matchet. Hele\nomrÂdet gennems¯ges for at finde alle mulige match."},
	/* de */ {IDGS_MON_HUNT_DESCRIPTION_DE, "Suche in angebenen Adressbereich nach <Datenliste>. Wenn die Daten gefunden\nwurden, wird die Startadresse gezeigt. Der komplette Bereich wird alle\nVorkommnisse von <Datenliste> untersucht."},
	/* es */ {IDGS_MON_HUNT_DESCRIPTION_ES, "Buscar en memoria en el rango de direcciones especificado por\n<lista datos>. Si se encuentra, se muestra la direcciÛn del dato.\nSe busca en todo el rango buscando posibles concordancias."},
	/* fr */ {IDGS_MON_HUNT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_HUNT_DESCRIPTION_HU, "Az <adat_lista> adat keresÈse a memÛri·ban. Ha megtal·lja a sorozatot,\na kezdıcÌmÈt kiÌrja. Az egÈsz tartom·nyt vÈgignÈzi az ˆsszes lehetsÈges\ntal·lat felfedezÈsÈhez."},
	/* it */ {IDGS_MON_HUNT_DESCRIPTION_IT, "Cerca nell'intervallo di indirizzi specificato i dati nella <lista di dati>.\nSe il dato Ë trovato, viene visualizzato l'indirizzo iniziale della\ncorrispondenza. Tutto l'intervallo viene ricercato per tutte le possibili\ncorrispondenze."},
	/* ko */ {IDGS_MON_HUNT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_HUNT_DESCRIPTION_NL, "Zoek het adres bereik voor de data in <data_lijst>. Als de data is gevonden\ndan wordt het start adres getoont. Er zal door de hele reeks worden gezocht."},
	/* pl */ {IDGS_MON_HUNT_DESCRIPTION_PL, "Szukaj danych z <lista_danych> w pamiÍci w podanym zakresie\nadresÛw. Je∂li znaleziono dane, pokazany jest pocz±tkowy adres\ntrafienia. Ca≥y zakres jest przeszukiwany dla wszystkich moøliwych	rafieÒ."},
	/* ru */ {IDGS_MON_HUNT_DESCRIPTION_RU, "Hunt memory in the specified address range for the data in\n<data_list>.  If the data is found, the starting address of the match\nis displayed.  The entire range is searched for all possible matches."},
	/* sv */ {IDGS_MON_HUNT_DESCRIPTION_SV, "Sˆk i minnet i det angivna omrÂdet med data efter <datalista>.\nOm data pÂtr‰ffas visas startadressen fˆr tr‰ffen. Hela\nomrÂdet genomsˆks fˆr att hitta alla mˆjliga tr‰ffar."},
	/* tr */ {IDGS_MON_HUNT_DESCRIPTION_TR, "<veri_listesi>'nde bulunan veriler iÁin belirtilen bellek aral˝˝nda\narama yap.  Eer veri bulunursa, e˛le˛en adres aral˝˝n˝n ba˛lang˝Á\nadresi gˆr¸nt¸lenir.  T¸m alan m¸mk¸n olan e˛le˛meler iÁin aranacakt˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_ADDRESS_OPT_RANGE,    N_("address_opt_range")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_ADDRESS_OPT_RANGE_DA, "adresse_evt_omrÂde"},
	/* de */ {IDGS_ADDRESS_OPT_RANGE_DE, "Optionaler Adressbereich"},
	/* es */ {IDGS_ADDRESS_OPT_RANGE_ES, "Rango direcciÛn"},
	/* fr */ {IDGS_ADDRESS_OPT_RANGE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_ADDRESS_OPT_RANGE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_ADDRESS_OPT_RANGE_IT, "intervallo di indirizzi opzionale"},
	/* ko */ {IDGS_ADDRESS_OPT_RANGE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_ADDRESS_OPT_RANGE_NL, "optionele_adres_bereik"},
	/* pl */ {IDGS_ADDRESS_OPT_RANGE_PL, "address_opt_range"},
	/* ru */ {IDGS_ADDRESS_OPT_RANGE_RU, "address_opt_range"},
	/* sv */ {IDGS_ADDRESS_OPT_RANGE_SV, "adress_ev_omrÂde"},
	/* tr */ {IDGS_ADDRESS_OPT_RANGE_TR, "opsiyonel_adres_aral˝˝"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_I_DESCRIPTION,    N_("Display memory contents as PETSCII text.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_I_DESCRIPTION_DA, "Vis hukommelsesindhold som PETSCII-text."},
	/* de */ {IDGS_MON_I_DESCRIPTION_DE, "Zeige Speicherinhalt als PETSCII Text."},
	/* es */ {IDGS_MON_I_DESCRIPTION_ES, "Mostrar contenido memoria como texto PETSCII."},
	/* fr */ {IDGS_MON_I_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_I_DESCRIPTION_HU, "MemÛria tartalom mutat·sa PETSCII szˆvegkÈnt."},
	/* it */ {IDGS_MON_I_DESCRIPTION_IT, "Mostra il contenuto della memoria come testo PETSCII."},
	/* ko */ {IDGS_MON_I_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_I_DESCRIPTION_NL, "Toon geheugen inhoud als PETSCII tekst."},
	/* pl */ {IDGS_MON_I_DESCRIPTION_PL, "Pokaø zawarto∂Ê pamiÍci jako tekst PETSCII."},
	/* ru */ {IDGS_MON_I_DESCRIPTION_RU, "Display memory contents as PETSCII text."},
	/* sv */ {IDGS_MON_I_DESCRIPTION_SV, "Visa minnesinnehÂll som PETSCII-text."},
	/* tr */ {IDGS_MON_I_DESCRIPTION_TR, "Bellek iÁeriini PETSCII yaz˝ biÁiminde gˆr¸nt¸le."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_II_DESCRIPTION,    N_("Display memory contents as screen code text.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_II_DESCRIPTION_DA, "Vis hukommelses-indhold som skÊrm-koder."},
	/* de */ {IDGS_MON_II_DESCRIPTION_DE, "Zeige Speicherinhalt als Bildschirmcode Text."},
	/* es */ {IDGS_MON_II_DESCRIPTION_ES, "Mostrar contenidos de memoria con cÛdigo texto pantalla."},
	/* fr */ {IDGS_MON_II_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_II_DESCRIPTION_HU, "MemÛria tartalom megjelenÌtÈse kÈpernyı kÛd szˆvegkÈnt."},
	/* it */ {IDGS_MON_II_DESCRIPTION_IT, "Mostra il contenuto della memoria come testo screen code."},
	/* ko */ {IDGS_MON_II_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_II_DESCRIPTION_NL, "Toon geheugen inhoud als scherm code tekst."},
	/* pl */ {IDGS_MON_II_DESCRIPTION_PL, "Pokaø zawarto∂Ê pamiÍci jako tekst screen code."},
	/* ru */ {IDGS_MON_II_DESCRIPTION_RU, "Display memory contents as screen code text."},
	/* sv */ {IDGS_MON_II_DESCRIPTION_SV, "Visa minnesinnehÂll som sk‰rmkodstext."},
	/* tr */ {IDGS_MON_II_DESCRIPTION_TR, "Bellek iÁeriini ekran kodu yaz˝ biÁiminde gˆr¸nt¸le."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_DATA_TYPE,    N_("data_type")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DATA_TYPE_DA, "datatype"},
	/* de */ {IDGS_DATA_TYPE_DE, "Datentyp"},
	/* es */ {IDGS_DATA_TYPE_ES, "tipo datos"},
	/* fr */ {IDGS_DATA_TYPE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_DATA_TYPE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_DATA_TYPE_IT, "dati"},
	/* ko */ {IDGS_DATA_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_DATA_TYPE_NL, "data_soort"},
	/* pl */ {IDGS_DATA_TYPE_PL, "data_type"},
	/* ru */ {IDGS_DATA_TYPE_RU, "data_type"},
	/* sv */ {IDGS_DATA_TYPE_SV, "datatyp"},
	/* tr */ {IDGS_DATA_TYPE_TR, "veri_tipi"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_MEM_DESCRIPTION,    N_("Display the contents of memory.  If no datatype is given, the default\nis used.  If only one address is specified, the length of data\ndisplayed is based on the datatype.  If no addresses are given, the\n'dot' address is used.\nPlease note: due to the ambiguous meaning of 'b' and 'd' these data-\ntypes must be given in uppercase!")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_MEM_DESCRIPTION_DA, "Vis hukommelsens indhold. Hvis datatype ikke angives, bruges standard.\nHvis kun en adresse angives, justeres lÊngden pÂ visningen baseret\npÂ datatypen. Hvis der ikke angives nogen adresse anvendes \"punktum\"-adressen.\nNote: PÂ grund af tvetydighed for 'b' og 'd' skal disse datatyper\nangives med store bogstaver!"},
	/* de */ {IDGS_MON_MEM_DESCRIPTION_DE, "Zeige Speicherinhalt. Wenn kein Datentyp angegeben wurde, wird der\nStandarddatentyp verwendet. Wenn nur eine Adresse angegeben wird, h‰ngt\ndie L‰nge der Daten vom Datentyp ab. Wenn keine Adresse angeben wurde, \nwird die aktuelle Adresse verwendet.\nAchtung: Wegen der Mehrdeutigkeit von `b' und `d', m¸ssen die\nDatentypen in Groﬂbuchstaben angegeben werden!"},
	/* es */ {IDGS_MON_MEM_DESCRIPTION_ES, "Mostrar el contenido de memoria. Si no se da tipo de datos, se usa el\npor defecto. Si sÛlo se da una direcciÛn, la longitud de dato\nmostrado se basa en el tipo dato. Si no se dan direcciones, se \nusa la direcciÛn 'dot'Por favor, note que debido al ambiguo significado de 'b' y 'd' estos\ntipos de dato se mostrararn en may˙sculas."},
	/* fr */ {IDGS_MON_MEM_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_MEM_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_MEM_DESCRIPTION_IT, "Mostra il contenuto della memoria. Se non Ë specificato alcun tipo di\ndato, verr‡ utilizzato quello predefinito. Se Ë specificato solo un indirizzo,\nla lunghezza del dato visualizzato Ë basata sul tipo. Se non Ë specificato\nnessun indirizzo, varr‡ utilizzato l'indirizzo 'dot'.Nota bene: a causa del significato ambiguo di 'b' e 'd' questi tipi di dati\ndevono essere inseriti in maiuscolo!"},
	/* ko */ {IDGS_MON_MEM_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_MEM_DESCRIPTION_NL, "Toon de geheugen inhoud. Als er geen datasoort is opgegeven dan zal de standaard\nworden gebruikt. Als er maar een adres is opgegeven dan zal de lengte van de\ngetoonde data gebaseerd worden op de datasoort. Als er geen adres is opgegeven\ndan zal het huidige adres worden gebruikt. Door de onduidelijke betekenis \nvan 'b' en 'd' moeten deze datasoorten opgegeven worden in hoofdletters!"},
	/* pl */ {IDGS_MON_MEM_DESCRIPTION_PL, "Pokazuje zawarto∂Ê pamiÍci. Je∂li nie ustalono typu danych, jest\nuøywany domy∂lny. Je∂li okre∂lono tylko jeden adres, d≥ugo∂Ê\npokazanych danych zaleøy od ich typu. Je∂li nie podano adresu,\nuøywany jest adres 'kropka'. Uwaga: w zwi±zku z wieloznaczno∂ci± 'b' i 'd', te typy danych\nnaleøy podaÊ wielk± liter±!"},
	/* ru */ {IDGS_MON_MEM_DESCRIPTION_RU, "Display the contents of memory.  If no datatype is given, the default\nis used.  If only one address is specified, the length of data\ndisplayed is based on the datatype.  If no addresses are given, the\n'dot' address is used.\nPlease note: due to the ambiguous meaning of 'b' and 'd' these data-\ntypes must be given in uppercase!"},
	/* sv */ {IDGS_MON_MEM_DESCRIPTION_SV, "Visa minnets innehÂll. Om ingen datatyp anges, anv‰nds standard.\nOm endast en adress anges, justeras l‰ngden pÂ visad data baserat\npÂ datatypen. Om ingen adress anges anv‰nds \"punkt\"-adressen.\nObservera: pÂ grund av tvetydig betydelse av \"b\" och \"d\" mÂste dessa\ndatatyper anges med stora bokst‰ver!"},
	/* tr */ {IDGS_MON_MEM_DESCRIPTION_TR, "Bellek iÁeriini gˆster.  Eer veri tipi girilmemi˛se, varsay˝lan\nkullan˝l˝r.  Yaln˝zca bir adres belirtilmi˛se, gˆsterilen verinin\nuzunluu veri tipine bal˝d˝r.  Eer hiÁ adres girilmemi˛se, 'nokta'\nadresi kullan˝l˝r.\nL¸tfen dikkat: 'b' ve 'd'nin karma˛˝k anlamlar˝ndan ˆt¸r¸ bu veri\ntipleri b¸y¸kharf olarak verilmelidir!"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_MEMCHAR_DESCRIPTION,    N_("Display the contents of memory as character data.  If only one address\nis specified, only one character is displayed.  If no addresses are\ngiven, the ``dot'' address is used.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_MEMCHAR_DESCRIPTION_DA, "Vis hukommelsens indhold som tegndata. Hvis kun en adresse\nangives, vises kun et tegn. Hvis ingen adresse angives benyttes\n\"punktum\"-adressen."},
	/* de */ {IDGS_MON_MEMCHAR_DESCRIPTION_DE, "Zeige den Inhalt von Speicher als Character Daten. Wenn nur eine Adresse\nangegeben wurde, wird nur ein Zeichen gezeigt. Wenn keine Adresse angegeben\nwurde, wird die aktuelle Adresse verwendet."},
	/* es */ {IDGS_MON_MEMCHAR_DESCRIPTION_ES, "Mostrar el contenido de memoria como datos de caracter. Si sÛlo se una\ndirecciÛn es especificada, sÛlo se muestra un caracter. Si no se da\nninguna direcciÛn, se usa la direcciÛn 'dot'."},
	/* fr */ {IDGS_MON_MEMCHAR_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_MEMCHAR_DESCRIPTION_HU, "A memÛria tartalm·nak megjelenÌtÈse karakter grafikakÈnt.  Ha csak egy cÌm\nadott, egyetlen karakter rajzolÛdik ki.  Ha nincs cÌm megadva,\na ``pont'' cÌmet haszn·lja."},
	/* it */ {IDGS_MON_MEMCHAR_DESCRIPTION_IT, "Mosta il contenuto della memoria come dati caratteri. Se Ë specificato\nsolo un indirizzo, verr‡ visualizzato solo un carattere. Se non Ë\nspecificato alcun indirizzo, varr‡ utilizzato l'indirizzo ``dot'' ."},
	/* ko */ {IDGS_MON_MEMCHAR_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_MEMCHAR_DESCRIPTION_NL, "Toon de geheugen inhoud als karakter data. Als er maar een adres is\nopgegeven dan zal er maar een karakter worden weergegeven. Als er geen\nadres is opgegeven dan zal het huidige adres gebruikt worden."},
	/* pl */ {IDGS_MON_MEMCHAR_DESCRIPTION_PL, "Pokaø zawarto∂Ê pamiÍci jako dane znakowe. Je∂li podano tylko jeden\nadres, pokazany jest tylko jeden znak. Je∂li nie podano adresÛw, uøyty\njest adres 'kropka'."},
	/* ru */ {IDGS_MON_MEMCHAR_DESCRIPTION_RU, "Display the contents of memory as character data.  If only one address\nis specified, only one character is displayed.  If no addresses are\ngiven, the ``dot'' address is used."},
	/* sv */ {IDGS_MON_MEMCHAR_DESCRIPTION_SV, "Visa minnets innehÂll som teckendata. Om endast en adress\nanges, visas endast ett tecken. Om ingen adress anges anv‰nds\n\"punkt\"-adressen."},
	/* tr */ {IDGS_MON_MEMCHAR_DESCRIPTION_TR, "Bellek iÁeriini karakter verisi olarak gˆster.  Yaln˝zca bir adres\nbelirtilmi˛se, yaln˝zca tek karakter gˆr¸nt¸lenir.  Eer hiÁ adres\ngirilmemi˛se, 'nokta' adresi kullan˝l˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_FORMAT,    N_("Format")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_FORMAT_DA, "Format"},
	/* de */ {IDGS_FORMAT_DE, "Format"},
	/* es */ {IDGS_FORMAT_ES, "Formato"},
	/* fr */ {IDGS_FORMAT_FR, "Format"},
	/* hu */ {IDGS_FORMAT_HU, "Form·tum"},
	/* it */ {IDGS_FORMAT_IT, "Formato"},
	/* ko */ {IDGS_FORMAT_KO, "±∏º∫ πÊΩƒ"},
	/* nl */ {IDGS_FORMAT_NL, "Formaat"},
	/* pl */ {IDGS_FORMAT_PL, "Format"},
	/* ru */ {IDGS_FORMAT_RU, "ƒﬁ‡‹–‚"},
	/* sv */ {IDGS_FORMAT_SV, "Format"},
	/* tr */ {IDGS_FORMAT_TR, "BiÁim"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION,    N_("Save the memmap as a picture. Format is:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_DA, "Gem memmap som billede. Format:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* de */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_DE, "Speicher die memmap als Bilddaten. Formate:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* es */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_ES, "Graba mapa memoria como gr·fico. el formato es:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* fr */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_HU, "MemÛria tÈrkÈp mentÈse kÈpkÈnt. A form·tum:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* it */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_IT, "Salva la mappa di memoria come immagine. I Formati sono:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* ko */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_NL, "Sla de memmap op als een afbeelding. Formaat is:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* pl */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_PL, "Zapisz mapÍ pamiÍci jako obrazek. Format:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* ru */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_RU, "Save the memmap as a picture. Format is:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* sv */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_SV, "Sparar minneskartan som en bild. Format:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* tr */ {IDGS_MON_MEMMAPSAVE_DESCRIPTION_TR, "Bellek haritas˝n˝ resim olarak kaydet. BiÁim:\n0 = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MASK,    N_("mask")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MASK_DA, "maske"},
	/* de */ {IDGS_MASK_DE, "Maske"},
	/* es */ {IDGS_MASK_ES, "m·scara"},
	/* fr */ {IDGS_MASK_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MASK_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MASK_IT, "maschera"},
	/* ko */ {IDGS_MASK_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MASK_NL, "masker"},
	/* pl */ {IDGS_MASK_PL, "mask"},
	/* ru */ {IDGS_MASK_RU, "mask"},
	/* sv */ {IDGS_MASK_SV, "mask"},
	/* tr */ {IDGS_MASK_TR, "maske"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION,    N_("Show the memmap. The mask can be specified to show only those\nlocations with accesses of certain type(s). The mask is a number\nwith the bits \"ioRWXrwx\", where RWX are for ROM and rwx for RAM.\nOptionally, an address range can be specified.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_DA, "Vis memmap. Masken kan angives for kun at vise de celler, som\ner tilgÂet med valgte typer tilgang. Masken er et tal med\nbitsne \"ioRWXrwx\", hvor RWX er ROM og rwx er RAM.\nEt adresseomrÂde kan eventuelt angives."},
	/* de */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_DE, "Zeige die memmap. Die Maske kann so definiert werden, dass nur jene Orte\nmit Zugriff auf spezifische Typ(en) gezeigt werden. Die Maske ist eine Nummer\nmit Bits \"ioRWXrwx\", wobei RWX f¸r ROM und rwx f¸r RAM steht.\nOptional kann ein Adressbereich definiert werden."},
	/* es */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_ES, "Mostrar el mapa de memoria. La mascara puede definirse para mostrar\nsÛlo aquellas localizaciones con un determinado tipo(s). La m·scara es\nun n˙mero con bits \"ioRVXrvx\", donde RWX son para ROM y rwx son\npara RAM. Opcionalmente, se puede especificar un rango de direcciones."},
	/* fr */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_HU, "A memÛria tÈrkÈp mutat·sa. A maszk ˙gy ·llÌthatÛ, hogy csak azokat a\nhelyeket mutassa, amelyek a megadott elÈrÈssel rendelkeznek. A maszk\negy sz·m az \"ioRWXrwx\" bitekkel, ahol az RWX a ROM-ra, az rwx a RAM-ra\nvonatkozik. TetszÈs szerint egy cÌmtartom·ny is megadhatÛ."},
	/* it */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_IT, "Mostra la mappa di memoria. La maschera puÚ essere specificata per\nmostrare solo quelle locazioni con accessi un un certo tipo. La maschera\nË un numero con i bit \"ioRWXrwx\", dove RWX sono per la ROM e\nrwx per la RAM.\nOpzionalmente, puÚ essere specificato anche un intervallo di indirizzi."},
	/* ko */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_NL, "Toon de memmap. Het masker kan worden opgegeven zodat er alleen de\nadressen met toegrijpingen van een bepaalde soort(en) zal worden getoond.\nHet masker is een nummer met de bits \"ioRWXrwx\", waar RWX is voor ROM,\nen rwx voor RAM. Er kan optioneel een adres bereik worden opgegeven."},
	/* pl */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_PL, "Pokazuje mapÍ pamiÍci. By pokazaÊ tylko obszar dostÍpÛw danego typu,\nmoøna okre∂liÊ maskÍ. Maska to numer zawieraj±cy bity \"ioRWXrwx\", gdzie\nRWX to ROM, a rwx to RAM. Opcjonalnie moøna okre∂liÊ zakres adresÛw."},
	/* ru */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_RU, "Show the memmap. The mask can be specified to show only those\nlocations with accesses of certain type(s). The mask is a number\nwith the bits \"ioRWXrwx\", where RWX are for ROM and rwx for RAM.\nOptionally, an address range can be specified."},
	/* sv */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_SV, "Visa minneskartan. Masken kan anges fˆr att endast visa de\nceller som g‰ller specifik(a) typ(er). Masken ‰r ett tal\nmed bitarna \"ioRWXrwx\", d‰r RWX ‰r fˆr ROM och rwx ‰r fˆr\nRAM. Ett minnesomrÂde kan eventuellt anges."},
	/* tr */ {IDGS_MON_MEMMAPSHOW_DESCRIPTION_TR, "Bellek haritas˝n˝ gˆster. Maske, yaln˝zca belirli tiplerce eri˛ilebilen\nkonumlarda belirtilebilir. Maske \"ioRWXrwx\" bitlerinden olu˛an bir\nsay˝d˝r. RWX ROM'u, rwx RAM'i ifade eder. Opsiyonel olarak bir adres\naral˝˝ belirtilebilir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_MEMMAPZAP_DESCRIPTION,    N_("Clear the memmap.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_DA, "Nulstil memmap."},
	/* de */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_DE, "Lˆsche die memmap."},
	/* es */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_ES, "Limpiar mapa de memoria."},
	/* fr */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_HU, "A memÛria tÈrkÈp tˆrlÈse."},
	/* it */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_IT, "Cancella la mappa di meoria."},
	/* ko */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_NL, "Veeg de memmap schoon."},
	/* pl */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_PL, "Wyczy∂Ê mapÍ pamiÍci."},
	/* ru */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_RU, "Clear the memmap."},
	/* sv */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_SV, "Tˆm minneskartan."},
	/* tr */ {IDGS_MON_MEMMAPZAP_DESCRIPTION_TR, "Bellek haritas˝n˝ temizle."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_MEMSPRITE_DESCRIPTION,    N_("Display the contents of memory as sprite data.  If only one address is\nspecified, only one sprite is displayed.  If no addresses are given,\nthe ``dot'' address is used.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_MEMSPRITE_DESCRIPTION_DA, "Vis hukommelsens indhold som spritedata. Hvis kun en adresse\nangives, vises kun en sprite. Hvis ingen adresse angives bruges\n\"punktum\"-adressen."},
	/* de */ {IDGS_MON_MEMSPRITE_DESCRIPTION_DE, "Zeige den Speicher als Sprite Daten. Wenn nur eine Adresse angegeben wurde,\nwird nur ein Sprite gezeitg. Wenn keine Adresse angegeben wurde, wird\ndie aktuelle Adresse verwendet."},
	/* es */ {IDGS_MON_MEMSPRITE_DESCRIPTION_ES, "Mostrar el contenido de memoria como datos de sprites, Si sÛlo se \nespecifica una direcciÛn, solo se muestra un sprite. Si no se dan\ndirecciones, se usa la direcciÛn 'dot'."},
	/* fr */ {IDGS_MON_MEMSPRITE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_MEMSPRITE_DESCRIPTION_HU, "A memÛria tartalm·nak megjelenÌtÈse sprite adatkÈne. Ha csak egy cÌm\nvan megadva, egyetlen sprite-ot mutat.  Ha egy·ltal·n nincs cÌm megadva,\naz aktu·lis cÌmet haszn·lja."},
	/* it */ {IDGS_MON_MEMSPRITE_DESCRIPTION_IT, "Mostra il contenuto della memoria come dati sprite. Se Ë specificato\nsolo un indirizzo, verr‡ mostrato solo uno sprite. Se non Ë specificato\nalcun indirizzo, varr‡ utilizzato l'indirizzo ``dot''."},
	/* ko */ {IDGS_MON_MEMSPRITE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_MEMSPRITE_DESCRIPTION_NL, "Toon de geheugen inhoud als sprite data. Als er maar een adres is opgegeven\ndan zal er maar een sprite worden getoond. Als er geen adres is opgegeven\ndan zal het huidige adres worden gebruikt."},
	/* pl */ {IDGS_MON_MEMSPRITE_DESCRIPTION_PL, "Pokazuje zawarto∂Ê pamiÍci jako dane duszkÛw. Je∂li podano tylko jeden\nadres, pokazywany jest tylko jeden duszek. Je∂li nie podano adresu,\nuøywany jest adres ``dot'."},
	/* ru */ {IDGS_MON_MEMSPRITE_DESCRIPTION_RU, "Display the contents of memory as sprite data.  If only one address is\nspecified, only one sprite is displayed.  If no addresses are given,\nthe ``dot'' address is used."},
	/* sv */ {IDGS_MON_MEMSPRITE_DESCRIPTION_SV, "Visa minnets innehÂll som spritedata. Om endast en adress\nanges, visas endast en sprite. Om ingen adress anges anv‰nds\n\"punkt\"-adressen."},
	/* tr */ {IDGS_MON_MEMSPRITE_DESCRIPTION_TR, "Bellek iÁeriini yarat˝k verisi olarak gˆster.  Yaln˝zca bir adres\nbelirtilmi˛se, yaln˝zca tek yarat˝k gˆr¸nt¸lenir.  Eer hiÁ adres\ngirilmemi˛se, 'nokta' adresi kullan˝l˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_MOVE_DESCRIPTION,    N_("Move memory from the source specified by the address range to\nthe destination specified by the address.  The regions may overlap.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_MOVE_DESCRIPTION_DA, "KopiÈr data fra kilden angivet af hukommelsesomrÂdet til destinationen\nsom angives af adressen. Regionerne kan overlappe."},
	/* de */ {IDGS_MON_MOVE_DESCRIPTION_DE, "Verschiebe Speicher von Startadresse definiert durch den Adressbereich zum\nZielbereich definiert durch die Adresse. Die Bereiche kˆnnen ¸berlappend sein."},
	/* es */ {IDGS_MON_MOVE_DESCRIPTION_ES, "Mueve memoria desde la fuente especificada por rango de direcciones\nal destino especificado en direcciÛn. La region puede estas superpuesta."},
	/* fr */ {IDGS_MON_MOVE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_MOVE_DESCRIPTION_HU, "MemÛria m·sol·sa a forr·s ter¸letrıl a cÈl cÌm ·ltal meghat·rozott\nter¸letre. A tartom·nyok ·tfedÈse megengedett."},
	/* it */ {IDGS_MON_MOVE_DESCRIPTION_IT, "Sposta la memoria dalla sorgente specificata dall'intervallo di indirizzi\nalla destinazione specificata dall'indirizzo. Le regioni possono\nsovrapporsi."},
	/* ko */ {IDGS_MON_MOVE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_MOVE_DESCRIPTION_NL, "Verplaats data van de opgegeven bron adres reeks naar het doel adres. De\nreeksen kunnen overlappen."},
	/* pl */ {IDGS_MON_MOVE_DESCRIPTION_PL, "Przesuwa pamiÍÊ z okre∂lonego zakresu adresÛw pod podany adres.\nZakresy mog± siÍ pokrywaÊ."},
	/* ru */ {IDGS_MON_MOVE_DESCRIPTION_RU, "Move memory from the source specified by the address range to\nthe destination specified by the address.  The regions may overlap."},
	/* sv */ {IDGS_MON_MOVE_DESCRIPTION_SV, "Flytta minne frÂn k‰lladressen som anges av minnesomrÂdet\ntill destinationen som anges av adressen. Regionerna kan vara\nˆverlappande."},
	/* tr */ {IDGS_MON_MOVE_DESCRIPTION_TR, "Bellei belirtilmi˛ kaynak adres aral˝˝ndan belirtilmi˛ hedef\nadresine ta˛˝.  Alanlar ¸st ¸ste binebilir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_CHECKPOINT_COMMANDS,    N_("Checkpoint commands:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_CHECKPOINT_COMMANDS_DA, "Checkpoint-kommandoer:"},
	/* de */ {IDGS_CHECKPOINT_COMMANDS_DE, "Checkpoint Kommandos:"},
	/* es */ {IDGS_CHECKPOINT_COMMANDS_ES, "Comandos de control:"},
	/* fr */ {IDGS_CHECKPOINT_COMMANDS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_CHECKPOINT_COMMANDS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_CHECKPOINT_COMMANDS_IT, "Comandi punti di controllo:"},
	/* ko */ {IDGS_CHECKPOINT_COMMANDS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_CHECKPOINT_COMMANDS_NL, "Checkpunt commandos:"},
	/* pl */ {IDGS_CHECKPOINT_COMMANDS_PL, "Komendy punktÛw kontrolnych:"},
	/* ru */ {IDGS_CHECKPOINT_COMMANDS_RU, "Checkpoint commands:"},
	/* sv */ {IDGS_CHECKPOINT_COMMANDS_SV, "Kommandon fˆr brytpunkter:"},
	/* tr */ {IDGS_CHECKPOINT_COMMANDS_TR, "Kontrol Noktas˝ komutlar˝:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_COND_EXPR,    N_("cond_expr")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_COND_EXPR_DA, "betingelse"},
	/* de */ {IDGS_COND_EXPR_DE, "bedingter Ausdruck"},
	/* es */ {IDGS_COND_EXPR_ES, "Expr_cond"},
	/* fr */ {IDGS_COND_EXPR_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_COND_EXPR_HU, ""},  /* fuzzy */
	/* it */ {IDGS_COND_EXPR_IT, "espressione condizione"},
	/* ko */ {IDGS_COND_EXPR_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_COND_EXPR_NL, "cond_expr"},
	/* pl */ {IDGS_COND_EXPR_PL, "cond_expr"},
	/* ru */ {IDGS_COND_EXPR_RU, "cond_expr"},
	/* sv */ {IDGS_COND_EXPR_SV, "villkorsuttryck"},
	/* tr */ {IDGS_COND_EXPR_TR, "ko˛ul_idafesi"},
#endif
	
	/*
	 Translators: this command was extended:
	 
	 - "load|store|exec" option added
	 
	 TODO: update these languages: DA, DE, HU, IT, NL, SV, TR
	 */
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_BREAK_DESCRIPTION,    N_("Set a breakpoint, If no address is given, the currently valid break-\npoints are printed.\nIf an address is given, a breakpoint is set for that address and the\nbreakpoint number is printed.\n`load|store|exec' is either `load', `store' or `exec' (or any combina-\ntion of these) to specify on which operation the monitor breaks. If\nnot specified, the monitor breaks on `exec'.\nA conditional expression can also be specified for the breakpoint.\nFor more information on conditions, see the CONDITION command.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_BREAK_DESCRIPTION_DA, "SÊt et breakpoint. Hvis der ikke angives en adresse vises en liste\nover nuvÊrende gyldige breakpoints.\nHvis der angives en adresse vil der blive sat et breakpoint pÂ\ndenne, og breakpointets nummer udskrives.\n`load|store|exec' er enten `load', `store' eller `exec' (eller en\nvilkÂrlig kombination), og angiver pÂ hvilken operation monitoren\nafbryder. Hvis intet angives vil monitoren afbryde pÂ `exec'.\nDer kan ogsÂ angives en betingelse for det angivne breakpoint. For\nyderligere information om betingede udtryk, se kommandoen CONDITION."},
	/* de */ {IDGS_MON_BREAK_DESCRIPTION_DE, "Setze einen Breakpoint. Wenn keine Adresse angegeben wurde, werden die\naktuellen g¸ltigen Breakpoints gezeigt. \nWenn eine Adresse angegebene wurde, wird ein Breakpoint auf diese Adresse\ngesetzt und die Breakpoint Nummer wird ausgegeben.\n`load|store|exec' ist entweder `load', `store' oder `exec' (oder eine\nKombination) und dient zur Angabe, bei welcher Operation der Monitor\nanhalten soll. Wenn keine Angabe gemacht wird, stoppt der Monitor bei\n`exec'.\nEin bedingter Ausdruck kann zu Breakpoints zugeordnet werden. F¸r\nmehr Informations ¸ber bedingte Ausdr¸cke, bitte Kommando CONDITION\nansehen."},
	/* es */ {IDGS_MON_BREAK_DESCRIPTION_ES, "Poner punto de ruptura. Si no se d· direcciÛn, se imprime el actual punto\nde control. Si se d· una direcciÛn, se activa un punto de ruptura en la misma\ny se imprime el n˙mero de punto de ruptura.\n`load|store|exec' es cualquiera de `load', `store' or `exec' (o combinaciÛn\nde ellos) a especificar en que operacion el monitor se detiene. Si no se\nespecifica, el monitor se detiene en `exec'.\nSe puede especificar tambien una condiciÛn para el punto de ruptura.\nPara m·s informaciÛn sobre condiciones, ver el comandoa CONDITION."},
	/* fr */ {IDGS_MON_BREAK_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_BREAK_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_BREAK_DESCRIPTION_IT, "Imposta un breakpoint. Se non viene specificato alcun indirizzo,\nvengono stampati i breakpoint attuali.\nSe viene specificato un indirizzo, viene impostato un breakpoint\nper tale indirizzo e viene stampato il suo numero.\n`load|store|exec' Ë uno tra `load', `store' o `exec' (or una qualunque\ncombinazione di questi) per specificare su quale operazione il monitor\ninterromper‡. Se non specificato, il monitor interrompe su `exec'.\nPuÚ anche essere specificata una condizione per il breakpoint.\nPer ulteriori informazioni, vedere il comando CONDITION."},
	/* ko */ {IDGS_MON_BREAK_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_BREAK_DESCRIPTION_NL, "Zet een breekpunt, als er geen adres is opgegeven dan zullen de huidige\ngeldige breekpunten worden geprint. Als er een adres is opgegeven dan\nzal er een breekpunt gezet worden voor dat adres en de nummer van het\nbreekpunt zal worden getoond.\n`load|store|exec' is `load', `store' of `exec' (of een combinatie) die\ngebruikt zal worden om aan te geven bij wlke operatie de monitor zou\nmoeten starten. Als er niets is opgegeven dan zal de monitor op 'exec'\nstarten.\nEen conditie kan worden opgegeven voor het breekpunt. Voor meer\ninformatie over condities zie het CONDITION commando."},
	/* pl */ {IDGS_MON_BREAK_DESCRIPTION_PL, "Ustawia punkt wstrzymania. Je∂li nie podano adresu, pokazywane s±\nobecnie aktywne punkty wstrzymania.\nJe∂li podano adres, ustawiany jest punkt wstrzymania dla tego adresu\ni pokazywany jest numer punktu wstrzymania.\n`load|store|exec' to `load', `store' lub `exec' (albo ich po≥±czenia),\nokre∂laj±ce  podczas ktÛrych operacji nastÍpuje b≥±d. Je∂li nic\nnie okre∂lono, monitor przerywa dzia≥anie na `exec'.\nMoøna rÛwnieø okre∂liÊ wyraøenie warunkowe dla punktu wstrzymania.\nBy znaleºÊ wiÍcej informacji o warunkach, zobacz polecenie CONDITION."},
	/* ru */ {IDGS_MON_BREAK_DESCRIPTION_RU, "Set a breakpoint, If no address is given, the currently valid break-\npoints are printed.\nIf an address is given, a breakpoint is set for that address and the\nbreakpoint number is printed.\n`load|store|exec' is either `load', `store' or `exec' (or any combina-\ntion of these) to specify on which operation the monitor breaks. If\nnot specified, the monitor breaks on `exec'.\nA conditional expression can also be specified for the breakpoint.\nFor more information on conditions, see the CONDITION command."},
	/* sv */ {IDGS_MON_BREAK_DESCRIPTION_SV, "S‰tt en ˆvervakningspunkt, Om ingen adress anges visas de \nˆvervakningspunkter som ‰r giltiga.\nOm en adress anges s‰tts en brytpunkt pÂ den adressen och dess\nnummer visas.\n\"load|store|exec\" ‰r antingen \"load\", \"store\" eller \"exec\"\n(eller en kombination d‰rutav) fˆr att ange pÂ vilken operation\nmonitorn stoppar. Om det inte anges bryter monitorn pÂ \"exec\".\nEtt villkorsuttryck kan ocksÂ anges fˆr brytpunkten.\nFˆr mer information om villkor, se kommandot CONDITION."},
	/* tr */ {IDGS_MON_BREAK_DESCRIPTION_TR, "Kesme noktas˝ koy, eer adres girilmemi˛se, geÁerli mevcut izleme\nnoktalar˝ yazd˝r˝l˝r.\nEer bir adres girilmi˛se, o adres iÁin bir kesme noktas˝ i˛aretlenir\nve kesme noktas˝ say˝s˝ yazd˝r˝l˝r.\n`y¸kle|depola|y¸r¸t' iÁin `y¸kle', `depola' ya da `y¸r¸t' (ya da herhangi\nbir kombinasyonu) takip edilmek istenen operasyona gˆre belirtilmelidir.\nEer belirtilmemi˛se, takip i˛lemi `y¸r¸t'de sona erer.\nAyn˝ zamanda kesme noktas˝ iÁin bir ko˛ul ifadesi de belirtilebilir.\nKo˛ullar ile ilgili daha Áok bilgi almak iÁin, CONDITION komutuna\nbakabilirsiniz."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_COMMAND,    N_("Command")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_COMMAND_DA, "Kommando"},
	/* de */ {IDGS_COMMAND_DE, "Kommando"},
	/* es */ {IDGS_COMMAND_ES, "Comando"},
	/* fr */ {IDGS_COMMAND_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_COMMAND_HU, ""},  /* fuzzy */
	/* it */ {IDGS_COMMAND_IT, "Comando"},
	/* ko */ {IDGS_COMMAND_KO, "∏Ì∑…"},
	/* nl */ {IDGS_COMMAND_NL, "Commando"},
	/* pl */ {IDGS_COMMAND_PL, "Polecenie"},
	/* ru */ {IDGS_COMMAND_RU, "Command"},
	/* sv */ {IDGS_COMMAND_SV, "Kommando"},
	/* tr */ {IDGS_COMMAND_TR, "Komut"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_COMMAND_DESCRIPTION,    N_("Specify `command' as the command to execute when checkpoint `checknum'\nis hit.  Note that the `x' command is not yet supported as a\ncommand argument.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_COMMAND_DESCRIPTION_DA, "Angiv \"kommando\" som kommando der skal eksekveres nÂr ckeckpoint\n\"checknum\" nÂs. VÊr opmÊrksom pÂ at kommandoen \"x\" endnu ikke\ner underst¯ttet som parameter."},
	/* de */ {IDGS_MON_COMMAND_DESCRIPTION_DE, "Definiere `Kommando', welches bei Checkpoint `Checknum' ausgef¸hrt wird.\nAchtung Kommando `x' wird zurzeit noch nicht als Kommando Argument\nunterst¸tzt."},
	/* es */ {IDGS_MON_COMMAND_DESCRIPTION_ES, "Especificar 'comando' como el comando a ejecutar cuando el punto de control\n'checknum' est· activo. notar que el comando 'x' no est· soportado como\nargumento de comando."},
	/* fr */ {IDGS_MON_COMMAND_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_COMMAND_DESCRIPTION_HU, "`parancs' megad·sa egy `ell_pont_sz·m' sorsz·m·val adott ellenırzÈsi pont\nelÈrÈsekor tˆrtÈnı vÈgrehajt·sra.  Az `x' parancs egyelıre nem haszn·lhatÛ\nitt paramÈterkÈnt."},
	/* it */ {IDGS_MON_COMMAND_DESCRIPTION_IT, "Specifica `comando' come il comando da eseguire quando\nviene incontrato il punto di controllo `checknum'. Nota che \nil comando `x' non Ë ancora supportato come parametro."},
	/* ko */ {IDGS_MON_COMMAND_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_COMMAND_DESCRIPTION_NL, "Geef `commando' als het command om uit te voeren wanneer checkpunt `checknum'\nwordt uitgevoerd. NB: het `x' commando is op dit moment geen geldige\nparameter."},
	/* pl */ {IDGS_MON_COMMAND_DESCRIPTION_PL, "Okre∂l 'command' jako polecenie do wykonania przy osi±gniÍciu punktu 'checknum.'\nPolecenie 'x' nie jest jeszcze obs≥ugiwane jako argument polecenia."},
	/* ru */ {IDGS_MON_COMMAND_DESCRIPTION_RU, "Specify `command' as the command to execute when checkpoint `checknum'\nis hit.  Note that the `x' command is not yet supported as a\ncommand argument."},
	/* sv */ {IDGS_MON_COMMAND_DESCRIPTION_SV, "Ange \"kommando\" som kommando att exekvera n‰r vid tr‰ff pÂ\nkontrollpunkten∑\"kontrollnr\". Observera att kommandot \"x\" ‰nnu\ninte stˆds som kommandoparameter."},
	/* tr */ {IDGS_MON_COMMAND_DESCRIPTION_TR, "Kontrol noktas˝ `kontrolnumaras˝'na ula˛˝ld˝˝nda `komut' olarak\nÁal˝˛t˝r˝lacak komutu belirt.  Hen¸z `x' komutunun bir komut arg¸man˝\nolarak desteklenmediini not edin."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_CONDITION_DESCRIPTION,    N_("Each time the specified checkpoint is examined, the condition is\nevaluated.  If it evalutes to true, the checkpoint is activated.\nOtherwise, it is ignored.  If registers are specified in the expression,\nthe values used are those at the time the checkpoint is examined, not\nwhen the condition is set.\nThe condition can make use of registers (.A, .X, .Y, .PC, .SP) and\ncompare them (==, !=, <, >, <=, >=) again other registers or constants.\nRegisters can be the registers of other devices; this is denoted by\na memspace prefix (i.e., c:, 8:, 9:, 10:, 11:\nExamples: .A == 0, .X == .Y, 8:.X == .X\n")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_CONDITION_DESCRIPTION_DA, "Betingelsen evalueres hver gang det angivne checkpoint unders¯ges.\nHvis evalueres til sand aktiveres checkpointet, allers ignoreres\ndet. Hvis betingelsen indeholder registre, anvendes de vÊrdier,\nregistrene har nÂr betingelsen evalueres, ikke nÂr betingelsen\noprettes.\nBetingelsen kan anvende registrene (.A, .X, .Y, .PC, .SP) og\nsammenligne dem (==, !=, <, >, <=, >=) med andre registre eller\nkonstanter. Registre kan vÊre i andre enheder, og dette angives\nsom et hukommelsesomrÂdeprefix (dvs., c:, 8:, 9:, 10:, 11:)\nEksempel: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* de */ {IDGS_MON_CONDITION_DESCRIPTION_DE, "Bei jeder ‹berpr¸fung des Checkpoints, wird die Bedingung evaluiert.\nIst das Ergebnis `Wahr', wird der Checkpoint aktiviert, sonst ingnoriert.\nWenn Register benutzt werden, werden deren Werte zum Zeitpunkt der \n‹berpr¸fung herangezogen.\nDie Bedingung kann Register benutzen (.A, .X, .Y, .PC, .SP) und gegen \nRegister oder Konstanten vergleichen (==, !=, <, >, <=, >=).\nRegister kˆnnen auch Ger‰teregister sein; dazu wird die memspace Prefix-syntax \nverwendet: c:, 8:, 9:, 10:, 11:\nBeispiel: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* es */ {IDGS_MON_CONDITION_DESCRIPTION_ES, "Cada vez que un punto de control se examine, la condiciÛn se\nevaluar·. Si la condiciÛn es cierta, se activa el punto de control.\nSi no, se ignora. Si los registros est·n especificado en la condiciÛn,\nse usan los valores en el momento en el que se examina el punto\nde ruptura, no en el momento de poner la condicion.\nLa condiciÛn puede usar los registros (.A, .X, .Y, .PC, .SP)  y compararlos\nm (==, !=, <, >, <=, >=) con otros registros y constantes.\nLos registros pueden ser de otros perifÈricos, esto se denota por el\nprefijo de espacio memoria (ejm., c:, 8:, 9:, 10:, 11:\nEjemplos: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* fr */ {IDGS_MON_CONDITION_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_CONDITION_DESCRIPTION_HU, "Minden alkalommal, amikor egy adott ellenırzÈsi pontot megvizsg·l, a\nfeltÈtelt kiÈrtÈkeli. Ha az eredmÈny igaz, a tˆrÈspont aktiv·lÛdik.\nEgyÈbkÈnt, figyelmen kÌv¸l hagyja. Ha regiszterek szerepelnek a kifejezÈsben,\naz ellenırzÈs pillanat·ban vett ÈrtÈk¸k sz·mÌt, nem pedig a be·llÌt·skori.\nA feltÈtel haszn·lhatja a regisztereket ( .A, .X, .Y, .PC, .SP) Ès ˆssze is\nhasonlÌthatja ıket (==, !=, <, >, <=, >=) m·s regiszterekkel.\nA regiszterek lehetnek m·s eszkˆzˆk regiszterei is; azokat egy memÛria tÈr\nelıtaggal kell ell·tni (vagyis c:, 8:, 9:, 10:, 11:).\nPÈld·k: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* it */ {IDGS_MON_CONDITION_DESCRIPTION_IT, "Ogni volta che si esamina il punto di controllo specificato, viene valutata\nla condizione. Se Ë vera, il punto di controllo Ë attivato.\nAltrimenti viene ignorato. Se nell'espressione sono specificati i registri,\nquesti valori sono quelli usati quando viene esaminato il punto di controllo,\nnon quando viene impostata la condizione.\nLa condizione puÚ fare uso dei registri (.A, .X, .Y, .PC, .SP) e confontarli\n(==, !=, <, >, <=, >=) con altri registri o costanti.\nI registri possono essere registri di altre periferiche; questo Ë denotato da\nun prefisso che specifica lo spazio di memoria (cioÈ, c:, 8:, 9:, 10:, 11:)\nAlcuni esempi: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* ko */ {IDGS_MON_CONDITION_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_CONDITION_DESCRIPTION_NL, "Elke keer de opgegeven checkpunt wordt onderzocht zal de conditie worden\ngeevalueerd. Als de evaluatie positief is dan zal de checkpunt geactiveerd\nworden, bij negatief zal er niets worden gedaan. Als er registers zijn\nopgegeven in de expressie dan zullen de waarden in die registers gebruikt\nworden op het moment dat de checkpunt wordt onderzocht, niet op het moment\ndat de conditie is opgegeven.\nDe conditie kan gebruik maken van registers (.A, .X, .Y, .PC, .SP) en\nkan ze vergelijken (==, !=, <, >, <=, >=) met andere registers of constanten\nRegisters kunnen de registers van andere apparaten zijn; de manier van opgeven\nis door een geheugenruimte prefix (bijvoorbeeld: c:, 8:, 9:, 10:, 11:\nVoorbeelden: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* pl */ {IDGS_MON_CONDITION_DESCRIPTION_PL, "Za kaødym razem, gdy analizowany jest punkt kontrolny, szacowany\njest stan. Je∂li jest oszacowany na 'prawda', punkt kontrolny jest\nuaktywniany. W innym razie jest ignorowany. Je∂li w wyraøeniu\npodano rejestry, uøywane s± warto∂ci z czasu szacowania punktu\nkontrolnego, nie z czasu ustawienia stanu.Stan moøe korzystaÊ z rejestrÛw (.A, .X, .Y, .PC, .SP) i porÛwnywaÊ je\n(==, !=, <, >, <=, >=) z innymi rejestrami lub sta≥ymi. Rejestry mog± byÊ\nrejestrami innych urz±dzeÒ, co jest okre∂lone przedrostkiem przestrzeni\npamiÍci (np. c:, 8:, 9:, 10:, 11)\nPrzyk≥ady: A == 0, .X == .Y, 8:.X == .X\n"},
	/* ru */ {IDGS_MON_CONDITION_DESCRIPTION_RU, "Each time the specified checkpoint is examined, the condition is\nevaluated.  If it evalutes to true, the checkpoint is activated.\nOtherwise, it is ignored.  If registers are specified in the expression,\nthe values used are those at the time the checkpoint is examined, not\nwhen the condition is set.\nThe condition can make use of registers (.A, .X, .Y, .PC, .SP) and\ncompare them (==, !=, <, >, <=, >=) again other registers or constants.\nRegisters can be the registers of other devices; this is denoted by\na memspace prefix (i.e., c:, 8:, 9:, 10:, 11:\nExamples: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* sv */ {IDGS_MON_CONDITION_DESCRIPTION_SV, "Villkoret utv‰rderas varje gÂng den givna kontrollpunkten\nundersˆks. Om det utv‰rderas till sant aktiveras kontrollpunkten.\nI annat fall ignoreras den. Om uttrycket innehÂller register\nanv‰nds de v‰rden de har dÂ kontrollpunkten utv‰rderas, inte\nn‰r villkoret sattes.\nVillkoret kan anv‰nda register (.A, .X, .Y, .PC, .SP) och\nj‰mfˆra dem (==, !=, <, >, <=, >=) mot andra register eller\nkonstanter. Register kan vara register i andra enheter, detta\nanges som ett minnesomrÂdesprefix (dvs., c:, 8:, 9:, 10:, 11:)\nExempel: .A == 0, .X == .Y, 8:.X == .X\n"},
	/* tr */ {IDGS_MON_CONDITION_DESCRIPTION_TR, "Her defas˝nda belirtilmi˛ bir kontrol noktas˝ incelendiinde, ko˛ul\ndeerlendirilir.  Ko˛ul doru sonuÁ verirse, kontrol noktas˝ aktive edilir.\nAksi taktirde gˆz ard˝ edilir.  Eer ifadede registerlar tan˝mlanm˝˛sa,\nbu deerler ifade tan˝mland˝˝nda deil kontrol noktas˝ incelendiinde\nkullan˝l˝rlar.\n›fadelerde (.A, .X, .Y, .PC, .SP) registerlar˝ kullan˝labilir ve\n(==, !=, <, >, <=, >=) opertatˆrleriyle dier register ve sabit deerlerle.\nkar˛˝la˛t˝r˝labilirler. Registerlar ba˛ka ayg˝tlar˝n registerlar˝ da olabilir;\nbu bir bellek alan˝ ˆn ekiyle ifade edilir (yani, c:, 8:, 9:, 10:, 11:\n÷rnekler: .A == 0, .X == .Y, 8:.X == .X\n"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DISABLE_DESCRIPTION,    N_("Disable checkpoint `checknum'.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DISABLE_DESCRIPTION_DA, "DeaktivÈr checkpoint \"checknum\"."},
	/* de */ {IDGS_MON_DISABLE_DESCRIPTION_DE, "Checkpoint `Checknum' deaktivieren."},
	/* es */ {IDGS_MON_DISABLE_DESCRIPTION_ES, "Deshabilitar punto controlt `n˙mero control'."},
	/* fr */ {IDGS_MON_DISABLE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DISABLE_DESCRIPTION_HU, "`ell_pont_sz·m' jel˚ ellenırzÈsi pont tilt·sa."},
	/* it */ {IDGS_MON_DISABLE_DESCRIPTION_IT, "Disattiva il punto di controllo `checknum'."},
	/* ko */ {IDGS_MON_DISABLE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DISABLE_DESCRIPTION_NL, "Checkpunt `checknum' uitschakelen."},
	/* pl */ {IDGS_MON_DISABLE_DESCRIPTION_PL, "Wy≥±cz punkt kontrolny `checknum'."},
	/* ru */ {IDGS_MON_DISABLE_DESCRIPTION_RU, "Disable checkpoint `checknum'."},
	/* sv */ {IDGS_MON_DISABLE_DESCRIPTION_SV, "Inaktivera kontrollpunkt \"kontrollnr\"."},
	/* tr */ {IDGS_MON_DISABLE_DESCRIPTION_TR, "Kontrol Noktas˝ `kontrolnumaras˝'n˝ pasifle˛tir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_ENABLE_DESCRIPTION,    N_("Enable checkpoint `checknum'.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_ENABLE_DESCRIPTION_DA, "AktivÈr checkpoint \"checknum\"."},
	/* de */ {IDGS_MON_ENABLE_DESCRIPTION_DE, "Checkpoint `Checknum' aktivieren."},
	/* es */ {IDGS_MON_ENABLE_DESCRIPTION_ES, "Habilitar punto controlt `n˙mero control'."},
	/* fr */ {IDGS_MON_ENABLE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_ENABLE_DESCRIPTION_HU, "`ell_pont_sz·m' jel˚ ellenırzÈsi pont engedÈlyezÈse."},
	/* it */ {IDGS_MON_ENABLE_DESCRIPTION_IT, "Attiva il punto di controllo `checknum'."},
	/* ko */ {IDGS_MON_ENABLE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_ENABLE_DESCRIPTION_NL, "Activeer checkpunt `checknum'."},
	/* pl */ {IDGS_MON_ENABLE_DESCRIPTION_PL, "W≥±cz punkt kontrolny `checknum'."},
	/* ru */ {IDGS_MON_ENABLE_DESCRIPTION_RU, "Enable checkpoint `checknum'."},
	/* sv */ {IDGS_MON_ENABLE_DESCRIPTION_SV, "Aktivera kontrollpunkt \"kontrollnr\"."},
	/* tr */ {IDGS_MON_ENABLE_DESCRIPTION_TR, "Kontrol Noktas˝ `kontrolnumaras˝'n˝ aktif et."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_IGNORE_DESCRIPTION,    N_("Ignore a checkpoint a given number of crossings.  If no count is given,\nthe default value is 1.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_IGNORE_DESCRIPTION_DA, "IgnorÈr et checkpoint det angivne antal gange. Hvis antal ikke angives\nbruges standardvÊrdien 1."},
	/* de */ {IDGS_MON_IGNORE_DESCRIPTION_DE, "Ignoriere den Checkpoint f¸r die angegebene Anzahl an Aktivierungen.\nWenn kein `Z‰hler' angegeben wurde, wird der Standardwert 1 verwendet."},
	/* es */ {IDGS_MON_IGNORE_DESCRIPTION_ES, "Ignorar un punto control un numero determinado de veces. Si no se da contador,\nel valor por defecto es 1."},
	/* fr */ {IDGS_MON_IGNORE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_IGNORE_DESCRIPTION_HU, "Az ellenırzÈsi pont figyelmen kÌv¸l hagy·sa megadott sz·m˙ ·thalad·skor.  Ha nincs\nsz·m megadva, az alapÈrtelmezett ÈrtÈk 1."},
	/* it */ {IDGS_MON_IGNORE_DESCRIPTION_IT, "Ignora un punto di controllo un numero specificato di occorrenze. Se\nnon Ë specificato alcun valore, quello predefinito Ë 1."},
	/* ko */ {IDGS_MON_IGNORE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_IGNORE_DESCRIPTION_NL, "Negeer een checkpunt een opgegeven aantal keer. Als er geen aantal is\nopgegeven dan wordt de standaard waarde van 1 worden gebruikt."},
	/* pl */ {IDGS_MON_IGNORE_DESCRIPTION_PL, "Ignoruje punkt kontrolny dan± ilo∂Ê razy. Je∂li nie podano tej ilo∂ci,\ndomy∂lna warto∂Ê wynosi 1."},
	/* ru */ {IDGS_MON_IGNORE_DESCRIPTION_RU, "Ignore a checkpoint a given number of crossings.  If no count is given,\nthe default value is 1."},
	/* sv */ {IDGS_MON_IGNORE_DESCRIPTION_SV, "Ignorera en kontrollpunkt det givna antalet gÂnger. Om inget antal ges\n‰r standardv‰rdet 1."},
	/* tr */ {IDGS_MON_IGNORE_DESCRIPTION_TR, "Bir kontrol noktas˝n˝ verilen adette geÁi˛ iÁin yoksay.  Eer adet verilmemi˛se,\nvarsay˝lan deer 1'dir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_UNTIL_DESCRIPTION,    N_("If no address is given, the currently valid breakpoints are printed.\nIf an address is given, a temporary breakpoint is set for that address\nand the breakpoint number is printed.  Control is returned to the\nemulator by this command.  The breakpoint is deleted once it is hit.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_UNTIL_DESCRIPTION_DA, "Hvis ingen adresse angives vises de aktuelle breakpoints. Hvis en\nadresse angives sÊttes et midlertidigt breakpoint, og nummeret pÂ\nbreakpointet vises. Kontrollen returneres til emulatoren af denne\nkommando. Breakpointet fjernes nÂr det nÂs."},
	/* de */ {IDGS_MON_UNTIL_DESCRIPTION_DE, "Wenn keine Adresse angegeben wurde, werden die aktuell g¸ltigen \nBreakpoints angezeigt. Wenn eine Adresse angegeben wurde, wird ein \ntempor‰rer Breakpoint auf dieser Adresse gesetzt und die Breakpoint Nummer wird\nangezeigt. Die Kontrolle wirdd bei diesem Kommando an die Emulation gegeben.\nDer Breakpoint wird gelˆscht, wenn er einmal getroffen wurde."},
	/* es */ {IDGS_MON_UNTIL_DESCRIPTION_ES, "Si no se da direcciÛn, se imprime el ˙ltimo punto de ruptura v·lido.\nSi se da direcciÛn, se activa un punto de ruptura para la direcciÛn\ny se imprime el n˙mero del punto de ruptura. El control se devuelve al\nemulador por el comando. El punto de ruputa se borra una vez se encuentra."},
	/* fr */ {IDGS_MON_UNTIL_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_UNTIL_DESCRIPTION_HU, "Ha nincs cÌm megadva, a jelenleg ÈrvÈnyes tˆrÈspontokat Ìrja ki.\nHa van adott cÌm, egy ideiglenes tˆrÈspontot helyez el az adott cÌmre,\nÈs a tˆrÈspont sz·ma kiÌrÛdik.  A vezÈrlÈs visszaker¸l az emul·torhoz\ne parancs ·ltal. A tˆrÈspont elÈrÈsekor tˆrlıdik."},
	/* it */ {IDGS_MON_UNTIL_DESCRIPTION_IT, "Se non viene specificato alcun indirizzo, vengono stampati i\nbreakpoint attualmente validi. Se viene specificato un indirizzo,\nviene impostato un breakpoint temporaneo per tale indirizzo e\nviene stampato il suo numero. Il controllo ritorna all'emulatore\nper mezzo di questo comando. Il breakpoint Ë cancellato quando\nviene incontrato."},
	/* ko */ {IDGS_MON_UNTIL_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_UNTIL_DESCRIPTION_NL, "Als er geen adres is opgegeven dan zullen de huidig geldige breekpunten\nworden geprint. Als er een adres is opgegeven dan wordt er een tijdelijk\nbreekpunt worden gezet voor dat adres en het breekpunt nummer zal worden\ngetoond. Na het geven van dit commando zal er terug worden gegaan naar de\nemulator. Het breekpunt zal worden verwijdert na het uitvoeren."},
	/* pl */ {IDGS_MON_UNTIL_DESCRIPTION_PL, "Je∂li nie podano adresu, pokazywane s± obecne punkty wstrzymania.\nJe∂li podano adres, ustawiany jest tymczasowy punkt wstrzymania\ni pokazywany jest numer punktu wstrzymania. To polecenie przywraca\nkontrolÍ do emulatora. Punkt wstrzymania jest kasowany po jego osi±gniÍciu."},
	/* ru */ {IDGS_MON_UNTIL_DESCRIPTION_RU, "If no address is given, the currently valid breakpoints are printed.\nIf an address is given, a temporary breakpoint is set for that address\nand the breakpoint number is printed.  Control is returned to the\nemulator by this command.  The breakpoint is deleted once it is hit."},
	/* sv */ {IDGS_MON_UNTIL_DESCRIPTION_SV, "Om du inte anger nÂgon adress visas de fˆr n‰rvarande giltiga\nbrytpunkterna. Om en adress anges s‰tts en tempor‰r brytpunkt fˆr\nden adressen och numret pÂ den nya brytpunkten visas. Styrningen\nÂterl‰mnas till emulatorn fˆr det h‰r kommandot. Brytpunkten\ntas bort n‰r den har nÂtts."},
	/* tr */ {IDGS_MON_UNTIL_DESCRIPTION_TR, "Eer adres girilmemi˛se, geÁerli mevcut kesme noktalar˝ yazd˝r˝l˝r.\nEer bir adres girilmi˛se, o adres iÁin geÁici bir kesme noktas˝\ni˛aretlenir ve kesme noktas˝ say˝s˝ yazd˝r˝l˝r.  Kontrol bu komutla\nem¸latˆre dˆnd¸r¸l¸r.  Bir kere eri˛ildii zaman kesme noktas˝ silinir."},
#endif
	
	/*
	 Translators: this command was extended:
	 
	 - "loadstore" option is now "load|store|exec"
	 - conditional expression was added
	 
	 TODO: update these languages: DA, DE, HU, IT, NL, SV, TR
	 */
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_WATCH_DESCRIPTION,    N_("Set a watchpoint. If no address is given, the currently valid watch-\npoints are printed. If a single address is specified, set a watchpoint\nfor that address.  If two addresses are specified, set a watchpoint\nfor the memory locations between the two addresses.\n`load|store|exec' is either `load', `store' or `exec' (or any combina-\ntion of these) to specify on which operation the monitor breaks. If\nnot specified, the monitor breaks on `load' and `store'.\n")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_WATCH_DESCRIPTION_DA, "SÊt et watchpoint. Hvis der ikke angives en adresse vises en liste\nover nuvÊrende gyldige watchpoints. Hvis der angives en enkelt\nadresse sÊttes et watchpoint pÂ adressen. Hvis der angives to adresser\nsÊttes et watchpoint for hukommelsesomrÂdet mellem adresserne.\n`load|store|exec' er enten `load', `store' eller `exec' (eller en\nvilkÂrlig kombination), og angiver pÂ hvilken operation monitoren\nafbryder. Hvis intet angives vil monitoren afbryde pÂ `load' og\n`store'.\n"},
	/* de */ {IDGS_MON_WATCH_DESCRIPTION_DE, "Setze einen Watchpoint. Wenn eine einzelne Adresse angegeben wurde, setze \nden Watchpoint f¸r diese Adresse. Wenn zwei Adressen angegeben wurden, \nsetze den Watchpoint auf die Adressen zwischen den beiden Adressen.\n`load|store|exec' ist entweder `load', `store' oder `exec' (oder eine\nKombination) und dient zur Angabe, bei welcher Operation der Monitor\nanhalten soll. Wenn keine Angabe gemacht wird, stoppt der Monitor bei\n`exec'.\nWenn keine Angabe gemacht wurde, h‰lt der Monitor bei bei `load' und\n`store' Operationen an.\n"},
	/* es */ {IDGS_MON_WATCH_DESCRIPTION_ES, "Poner punto de visualizaciÛn. Si no se d· direcciÛn se mostrar· el\nactualmente v·lido. Si se d· una direcciÛn simple, se pondr· un punto\nde visualizaciÛn en la misma\nSi se d·n dos direcciones se activar· un punto de visualizaciÛn para las\nlocalizaciones de memoria entre ambas direcciones.\n`load|store|exec' es cualquiera de `load', `store' or `exec' (o alguna com-\nbinaciÛn de ellos) para especificar en que operaciÛn el monitor se detiene\nSi no se especifica, Se detiene en  `load' y `store'.\n"},
	/* fr */ {IDGS_MON_WATCH_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_WATCH_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_WATCH_DESCRIPTION_IT, "Imposta un watchpoint. Se non viene specificato alcun indirizzo,\nvengono stampati i watchpoint attuali. Se viene specificato solo un\nsolo indirizzo, imposta un watchpoint per tale indirizzo. Se vengono\nspecificati due indirizzi, imposta un watchpoint per le locazioni di \nmemoria comprese tra i due indirizzi.\n`load|store|exec' Ë uno tra `load', `store' o `exec' (or una qualunque\ncombinazione di questi) per specificare su quale operazione il monitor\ninterromper‡. Se non specificato, il monitor interrompe su `load' e\n`store'.\n"},
	/* ko */ {IDGS_MON_WATCH_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_WATCH_DESCRIPTION_NL, "Zet een kijkpunt. Als er geen adres is opgegeven dan zal de huidige\ngeldige kijkpunten worden getoont. Als er een enkel adres is opgegeven\ndan zal er een kijkpunt worden gezet voor dat adres. Als er twee\nadressen zijn opgegeven dan zal er een kijkpunt worden gezet voor de\nadressen tussen de twee adressen.\n`load|store|exec' is `load',  `store' of `exec' om aan te geven bij\nwelke operatie de monitor zou moeten starten. Als deze niet opgegeven\nis dan zal de monitor starten bij `load' en `store' operaties.\n"},
	/* pl */ {IDGS_MON_WATCH_DESCRIPTION_PL, "Ustawia punkt ∂ledzenia. Je∂li nie podano adresu, pokazywane s±\nobecnie aktualne punkty ∂ledzenia. Je∂li okre∂lono pojedynczy adres,\nustawia punkt ∂ledzenia na ten adres. JÍsli okre∂lono dwa adresy,\nustawia punkt ∂ledzenia dla obszaru pamiÍci pomiÍdzy tymi dwoma\nadresami.\n`load|store|exec' to `load', `store' lub `exec' (albo ich po≥±czenia),\nokre∂laj±ce  podczas ktÛrych operacji nastÍpuje b≥±d. Je∂li nic\nnie okre∂lono, monitor przerywa dzia≥anie na `load' i `store'.\n"},
	/* ru */ {IDGS_MON_WATCH_DESCRIPTION_RU, "Set a watchpoint. If no address is given, the currently valid watch-\npoints are printed. If a single address is specified, set a watchpoint\nfor that address.  If two addresses are specified, set a watchpoint\nfor the memory locations between the two addresses.\n`load|store|exec' is either `load', `store' or `exec' (or any combina-\ntion of these) to specify on which operation the monitor breaks. If\nnot specified, the monitor breaks on `load' and `store'.\n"},
	/* sv */ {IDGS_MON_WATCH_DESCRIPTION_SV, "S‰tt en ˆvervakningspunkt. Om du inte anger nÂgon adress, visas\nnu giltiga ˆvervakningspunkter. Om du anger en ensam adress s‰tts en\nˆvervakningspunkt fˆr adressen. Om tvÂ adresser anges s‰tts en\nˆvervakningspunkt fˆr minnesomrÂdet mellan adresserna.\n\"load|store|exec\" ‰r antingen \"load\". \"store\" eller \"exec\" (eller en\nkombination d‰rutav) och anger vilken operation monitorn skall\nstoppa fˆr. Om den inte anges stoppar emulatorn pÂ bÂde \"load\" och\n\"store\".\n"},
	/* tr */ {IDGS_MON_WATCH_DESCRIPTION_TR, "Bir gˆr¸nt¸leme noktas˝ koy. Eer hiÁ adres verilmemi˛se, mevcut geÁerli\ngˆr¸nt¸leme noktalar˝ yazd˝r˝l˝r. Eer tek bir adres belirtilmi˛se,\ngˆr¸nt¸leme noktas˝n˝ o adrese koy.  Eer iki adres belirtilmi˛se, gˆr¸nt¸leme\nnoktas˝n˝ o iki adres aras˝nda kalan adreslere koy.\n`y¸kle|depola|y¸r¸t' monitˆr¸n kesildii operatˆre bal˝ olarak `y¸kle'\n`depola' ya da `y¸r¸t' (ya da herhangi bir kombinasyonunda) i˛lemlerinde\nÁal˝˛abilir. Eer belirtilmemi˛se, monitˆr `y¸kle' ve `depola'da kesilecektir.\n"},
#endif
	
	/*
	 Translators: this command was extended:
	 
	 - "load|store|exec" option added
	 - conditional expression was added
	 
	 TODO: update these languages: DA, DE, HU, IT, NL, SV, TR
	 */
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_TRACE_DESCRIPTION,    N_("Set a tracepoint. If no address is given, the currently valid trace-\npoints are printed. If a single address is specified, set a tracepoint\nfor that address.  If two addresses are specified, set a tracepoint\nfor the memory locations between the two addresses.\n`load|store|exec' is either `load', `store' or `exec' (or any combina-\ntion of these) to specify on which operation the monitor breaks. If\nnot specified, the monitor traces all three operations.\n")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_TRACE_DESCRIPTION_DA, "SÊt et tracepoint. Hvis der ikke angives en adresse vises en liste\nover nuvÊrende gyldige tracepoints. Hvis der angives en enkelt\nadresse sÊttes et tracepoint pÂ adressen. Hvis der angives to adresser\nsÊttes et tracepoint for hukommelsesomrÂdet mellem adresserne.\n`load|store|exec' er enten `load', `store' eller `exec' (eller en\nvilkÂrlig kombination), og angiver pÂ hvilken operation monitoren\ntracer. Hvis intet angives vil monitoren trace alle 3 operationer.\n"},
	/* de */ {IDGS_MON_TRACE_DESCRIPTION_DE, "Setze einen Tracepoint. Wenn keine Adresse angegeben wird, werden die\naktuellen g¸ltigen Tracepoints ausgegeben. Wenn eine einzelne Adresse\nangegeben wurde, setze den Watchpoint f¸r diese Adresse. Wenn zwei\nAdressen angegeben wurden, setze den Watchpoint auf die Adressen\nzwischen den beiden Adressen.\n`load|store|exec' ist entweder `load', `store' oder `exec' (oder eine\nKombination) und dient zur Angabe, bei welcher Operation der Monitor\nanhalten soll. Wenn keine Angabe gemacht wird, beobachtet der Monitor\nalle Operationen.\n"},
	/* es */ {IDGS_MON_TRACE_DESCRIPTION_ES, "Poner punto rastreo. Si no se d· direcciÛn, Se mostrar· el actualmente\nv·lido. Si se d· una sÛla direcciÛn, se activa un punto para esa direcciÛn.\nSi se d·n dos, se activa el punto para las localizaciones de memoria entre\nlas dos direcciones.\n`load|store|exec' es cualquiera `load', `store' or `exec' (o una combina-\nciÛn de ellas) para indicar en cual de ellas se detiene el monitor. Si no se\nespecifican el monitor rastrea todas las tres operaciones.\n"},
	/* fr */ {IDGS_MON_TRACE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_TRACE_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_TRACE_DESCRIPTION_IT, "Imposta un tracepoint. Se non viene specificato alcun indirizzo,\nvengono stampati i tracepoint attuali. Se viene specificato solo un\nsolo indirizzo, imposta un tracepoint per tale indirizzo. Se vengono\nspecificati due indirizzi, imposta un tracepoint per le locazioni di \nmemoria comprese tra i due indirizzi.\n`load|store|exec' Ë uno tra `load', `store' o `exec' (or una qualunque\ncombinazione di questi) per specificare su quale operazione il monitor\ninterromper‡. Se non specificato, il monitor traccer‡ tutte e tre le\noperazioni.\n"},
	/* ko */ {IDGS_MON_TRACE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_TRACE_DESCRIPTION_NL, "Zet een traceerpunt. Als er geen adres is opgegeven dan zullen de huidige\ngeldige traceerpunten worden getoont. Als er een enkel adres is opgegeven\ndan zal er een traceerpunt worden gezet voor dat adres. Als er twee\nadressen zijn opgegeven dan zal er een traceerpunt worden gezet voor de\nadressen tussen de twee adressen.\n`load|store|exec' is `load', `store' of 'exec' om aan te geven bij welke\noperatie de monitor zou moeten starten. Als deze niet opgegeven is dan zal\nde monitor starten bij alle operaties.\n"},
	/* pl */ {IDGS_MON_TRACE_DESCRIPTION_PL, "Ustawia punkt ∂ledzenia. Je∂li nie podano adresu, pokazywane s±\nw≥a∂ciwe obecnie punkty ∂ledzenia. Je∂li podano jeden adres,\nustawia punkt ∂ledzenia tego adresu. Je∂li podano dwa adresy,\nustawia punkt ∂ledzenia obszaru pamiÍci pomiÍdzy nimi.\n`load|store|exec' to `load', `store' lub `exec' (albo ich po≥±czenia),\nokre∂laj±ce  podczas ktÛrych operacji nastÍpuje b≥±d. Je∂li nic\nnie okre∂lono, monitor ∂ledzi wszystkie trzy rodzaje operacji.\n"},
	/* ru */ {IDGS_MON_TRACE_DESCRIPTION_RU, "Set a tracepoint. If no address is given, the currently valid trace-\npoints are printed. If a single address is specified, set a tracepoint\nfor that address.  If two addresses are specified, set a tracepoint\nfor the memory locations between the two addresses.\n`load|store|exec' is either `load', `store' or `exec' (or any combina-\ntion of these) to specify on which operation the monitor breaks. If\nnot specified, the monitor traces all three operations.\n"},
	/* sv */ {IDGS_MON_TRACE_DESCRIPTION_SV, "S‰tt en spÂrningspunkt. Om ingen adress anges visas befintliga\nspÂrningspunkter. Om du anger en ensam adress s‰tts en spÂrningspunkt\nfˆr adressen. Om tvÂ adresser anges s‰tts en spÂrningspunkt fˆr\nminnesomrÂdet mellan adresserna.\n\"load|store|exec\" ‰r antingen \"load\", \"store\" eller \"exec\" (eller en\nkombination d‰rutav) och anger vilken operation monitorn skall stoppa\nfˆr. Om den inte anges spÂrar monitorn alla tre operationerna.\n"},
	/* tr */ {IDGS_MON_TRACE_DESCRIPTION_TR, "Bir izleme noktas˝ koy. Eer bir adres belirtilmemi˛se, mevcut geÁerli\nizleme noktalar˝ yazd˝r˝l˝r. Eer tek bir adres belirtilmi˛se, izleme\nnoktas˝n˝ o adrese koy.  Eer iki adres belirtilmi˛se, izleme noktas˝n˝\no iki adres aras˝nda kalan adreslere koy.\n`y¸kle|depola|y¸r¸t' monitˆr¸n kesildii operatˆre bal˝ olarak `y¸kle'\n`depola' ya da `y¸r¸t' (ya da herhangi bir kombinasyonunda) i˛lemlerinde\nÁal˝˛abilir. Eer belirtilmemi˛se, monitˆr her ¸Á i˛lemi de izleyecektir.\n"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MONITOR_STATE_COMMANDS,    N_("Monitor state commands:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MONITOR_STATE_COMMANDS_DA, "Monitorstatuskommandoer:"},
	/* de */ {IDGS_MONITOR_STATE_COMMANDS_DE, "Monitor Zustand Kommandos:"},
	/* es */ {IDGS_MONITOR_STATE_COMMANDS_ES, "Comandos de estado del Monitor:"},
	/* fr */ {IDGS_MONITOR_STATE_COMMANDS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MONITOR_STATE_COMMANDS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MONITOR_STATE_COMMANDS_IT, "Comandi stato monitor:"},
	/* ko */ {IDGS_MONITOR_STATE_COMMANDS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MONITOR_STATE_COMMANDS_NL, "Monitor status commandos:"},
	/* pl */ {IDGS_MONITOR_STATE_COMMANDS_PL, "Monitoruj polecenia stanu:"},
	/* ru */ {IDGS_MONITOR_STATE_COMMANDS_RU, "Monitor state commands:"},
	/* sv */ {IDGS_MONITOR_STATE_COMMANDS_SV, "Kommandon fˆr monitorstatus:"},
	/* tr */ {IDGS_MONITOR_STATE_COMMANDS_TR, "Monitˆr durum komutlar˝:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DEVICE_DESCRIPTION,    N_("Set the default memory device to either the computer `c:' or the\nspecified disk drive (`8:', `9:').")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DEVICE_DESCRIPTION_DA, "SÊt det valgte hukommelses omrÂde til enten computeren \"c:\" eller\ndet angivne diskettedrev (\"8:\", \"9:\")."},
	/* de */ {IDGS_MON_DEVICE_DESCRIPTION_DE, "Setze das aktuelle Speicherger‰t entweder auf `c:' \noder das angegebene Laufwerk (`8:', `9:')."},
	/* es */ {IDGS_MON_DEVICE_DESCRIPTION_ES, "Seleccionar el perifÈrico memoria por defecto entre  `c:' o la\nunidad de disco especificada (`8:', `9:')."},
	/* fr */ {IDGS_MON_DEVICE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DEVICE_DESCRIPTION_HU, "Az alapÈrtelmezett memÛria eszkˆz be·llÌt·sa a sz·mÌtÛgÈpre `c:' vagy\na megadott lemezmeghajtÛra (`8:', `9:')."},
	/* it */ {IDGS_MON_DEVICE_DESCRIPTION_IT, "Imposta la periferica di memoria predefinita o sul computer `c:'\noppure sul disk drive specificato (`8:', `9:')."},
	/* ko */ {IDGS_MON_DEVICE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DEVICE_DESCRIPTION_NL, "Zet de standaard geheugen apparaat naar of de computer `c:' of de\nopgegeven disk drive (`8:', `9:')."},
	/* pl */ {IDGS_MON_DEVICE_DESCRIPTION_PL, "Ustawia komputer `c:', lub okre∂lon± stacjÍ dyskÛw (`8:', `9:')\njako domy∂lne urz±dzenie pamiÍci."},
	/* ru */ {IDGS_MON_DEVICE_DESCRIPTION_RU, "Set the default memory device to either the computer `c:' or the\nspecified disk drive (`8:', `9:')."},
	/* sv */ {IDGS_MON_DEVICE_DESCRIPTION_SV, "S‰tt fˆrvald minnesenhet antingen till datorn \"c:\" eller\nden angivna diskettenheten (\"8:\", \"9:\")."},
	/* tr */ {IDGS_MON_DEVICE_DESCRIPTION_TR, "Varsay˝lan bellek ayg˝t˝n˝ bilgisayar `c:' ya da (`8:', `9:') ile\nbelirtilmi˛ disket d¸r¸c¸ olarak belirle."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_EXIT_DESCRIPTION,    N_("Leave the monitor and return to execution.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_EXIT_DESCRIPTION_DA, "Forlad monitoren og gÂ tilbage til eksekvering."},
	/* de */ {IDGS_MON_EXIT_DESCRIPTION_DE, "Verlasse Monitor und setze Ausf¸hrung fort."},
	/* es */ {IDGS_MON_EXIT_DESCRIPTION_ES, "Dejar el monitor y volver a la ejecuciÛn."},
	/* fr */ {IDGS_MON_EXIT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_EXIT_DESCRIPTION_HU, "A monitor elhagy·sa Ès a vÈgrehajt·s folytat·sa."},
	/* it */ {IDGS_MON_EXIT_DESCRIPTION_IT, "Esce dal monitor e ritorna all'esecuzione."},
	/* ko */ {IDGS_MON_EXIT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_EXIT_DESCRIPTION_NL, "Verlaat de monitor en ga terug naar de uitvoering."},
	/* pl */ {IDGS_MON_EXIT_DESCRIPTION_PL, "Opu∂Ê monitor i wrÛÊ do wykonywania"},
	/* ru */ {IDGS_MON_EXIT_DESCRIPTION_RU, "Leave the monitor and return to execution."},
	/* sv */ {IDGS_MON_EXIT_DESCRIPTION_SV, "L‰mna monitorn och ÂtergÂ till programkˆrningen."},
	/* tr */ {IDGS_MON_EXIT_DESCRIPTION_TR, "Monitˆr¸ terk et ve Áal˝˛t˝rmaya geri dˆn."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_QUIT_DESCRIPTION,    N_("Exit the emulator immediately.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_QUIT_DESCRIPTION_DA, "Afslut emulatoren ¯jblikkeligt."},
	/* de */ {IDGS_MON_QUIT_DESCRIPTION_DE, "Emulator sofort beenden."},
	/* es */ {IDGS_MON_QUIT_DESCRIPTION_ES, "Salir inmediatamente del emulador."},
	/* fr */ {IDGS_MON_QUIT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_QUIT_DESCRIPTION_HU, "Azonnali kilÈpÈs az emul·torbÛl."},
	/* it */ {IDGS_MON_QUIT_DESCRIPTION_IT, "Esci immediatamente dall'emulatore."},
	/* ko */ {IDGS_MON_QUIT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_QUIT_DESCRIPTION_NL, "Onmiddelijk de emulator afsluiten."},
	/* pl */ {IDGS_MON_QUIT_DESCRIPTION_PL, "Natychmiast wyjdº z emulatora."},
	/* ru */ {IDGS_MON_QUIT_DESCRIPTION_RU, "≤ÎŸ‚ÿ ÿ◊ Ì‹„€Ô‚ﬁ‡– ›’‹’‘€’››ﬁ."},
	/* sv */ {IDGS_MON_QUIT_DESCRIPTION_SV, "Avsluta emulatorn omedelbart."},
	/* tr */ {IDGS_MON_QUIT_DESCRIPTION_TR, "Em¸lasyondan derhal Á˝k."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_RADIX_DESCRIPTION,    N_("Set the default radix to hex, decimal, octal, or binary.  With no\nargument, the current radix is printed.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_RADIX_DESCRIPTION_DA, "SÊt standardradix til hex, decimal, oktal eller binÊr. Hvis der\nikke angives et argument vises det aktuelle radix."},
	/* de */ {IDGS_MON_RADIX_DESCRIPTION_DE, "Setze die Standardzahlenbasis auf Hexadezimal, Dezimal, Oktal oder Bin‰r.\nBei keinem Argument wird die akteulle Zahlenbasis ausgegeben."},
	/* es */ {IDGS_MON_RADIX_DESCRIPTION_ES, "Seleccionar sistema n˙merico por defecto como hex, decimal, octal, o binario.\nSi no se da argumento, se imprime el sistema n˙merico en uso."},
	/* fr */ {IDGS_MON_RADIX_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_RADIX_DESCRIPTION_HU, "Az alap sz·mrendszer hexadecim·lis, decim·lis, okt·lis vagy bin·ris.\nParamÈter nÈlk¸l az aktu·lisat mutatja."},
	/* it */ {IDGS_MON_RADIX_DESCRIPTION_IT, "Imposta la radice predefinita a esadecimale, decimale, ottale o\nbinaria. Senza parametro viene stampata la radice attuale."},
	/* ko */ {IDGS_MON_RADIX_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_RADIX_DESCRIPTION_NL, "Zet de standaard radix naar hex, decimaal, octaal of binair. Als er\ngeen parameter is opgegeven dan zal de huidige radix worden getoond."},
	/* pl */ {IDGS_MON_RADIX_DESCRIPTION_PL, "Ustawia domy∂lny korzeÒ na heksadecymalny, decymalny, Û∂emkowy\nlub binarny. Bez podanego argumentu, pokazywany jest obecny korzeÒ."},
	/* ru */ {IDGS_MON_RADIX_DESCRIPTION_RU, "Set the default radix to hex, decimal, octal, or binary.  With no\nargument, the current radix is printed."},
	/* sv */ {IDGS_MON_RADIX_DESCRIPTION_SV, "S‰tt standardradix till hex, decimal, oktal eller bin‰r. Om du\ninte ger nÂgot argument visas nuvarande radix."},
	/* tr */ {IDGS_MON_RADIX_DESCRIPTION_TR, "Varsay˝lan say˝ taban˝n˝ 16'l˝, 10'lu, 8'li ya da 2'li yap.\nArg¸mans˝z olarak geÁerli say˝ taban˝ yazd˝r˝l˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_SIDEFX_DESCRIPTION,    N_("Control how monitor generated reads affect memory locations that have\nread side-effects.  If the argument is 'on' then reads may cause\nside-effects.  If the argument is 'off' then reads don't cause\nside-effects.  If the argument is 'toggle' then the current mode is\nswitched.  No argument displays the current state.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_SIDEFX_DESCRIPTION_DA, "Bestemmer hvordan lÊsninger i monitoren pÂvirker hukommelsesomrÂder,\nder har sedeeffekter ved lÊsning. Hvis argumentet er \"on\" kan lÊsninger\nforesage sideeffekter. Hvis argumentet er \"off\" vil lÊsninger ikke\nforesage sideeffekter. Hvis argumentet er \"toggle\" skiftes\nden nuvÊrende tilstand. Hvis der ikke angives noget argument vises\nden nuvÊrende tilstand."},
	/* de */ {IDGS_MON_SIDEFX_DESCRIPTION_DE, "Steuerung, wie die vom Monitor erzeugten Lesezugriffe die Speicherzellen\nmit Lese-Seiteneffekten betreffen.\nBei Argument \"on\" werden Lese-Seiteneffekte erzeugt.\nBei Argument \"off\" werden keine Lese-Seiteneffekte erzeugt.\nBei Argumenrt \"toggle\" wird das Verhalten vertauscht.\nBei keinem Argument wird das aktuelle Verhalten ausgegebene."},
	/* es */ {IDGS_MON_SIDEFX_DESCRIPTION_ES, "Controla como manejar las lecturas de localizaciones de memoria generadas por el\nmonitor que tengan efectos colaterales, Si el argumento es 'on' las lecturas causar·n\nefectos colaterales. Si el argumento es 'off' no se causar·n efectos colaterales. Si el\nargumento es 'intercambiar' se intervambiar· el modo en uso. Sin argumentos, se \nmostrar· el estado en uso."},
	/* fr */ {IDGS_MON_SIDEFX_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_SIDEFX_DESCRIPTION_HU, "Be·llÌtja, hogyan hatnak a monitorprogram memÛria olvas·sai azokra a\nmemÛriahelyekre, amelyeknek olvas·s-mellÈkhat·sai vannak. Ha a paramÈter\n'on', az olvas·sok okozhatnak mellÈkhat·sokat. Ha a paramÈter 'off', akkor pedig\nnem okoznak. Ha a paramÈter 'toggle', az aktu·lis mÛdot ·tkapcsolja.\nParamÈter nÈlk¸li hÌv·s kiÌrja az aktu·lis mÛdot."},
	/* it */ {IDGS_MON_SIDEFX_DESCRIPTION_IT, "Controlla come le letture generate dal monitor affliggono le locazioni\ndi memoria che hanno degli effetti collaterali sulla lettura.\nSe il paremetro Ë 'on', le letture possono causare effetti collaterali.\nSe il parametro Ë 'off', le letture non causano effetti collaterali.\nSe il parametro Ë 'scambia', la modalit‡ attuale viene invertita.\nNessun parametro mostra lo stato attuale."},
	/* ko */ {IDGS_MON_SIDEFX_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_SIDEFX_DESCRIPTION_NL, "Geef aan hoe de lees acties van de monitor de geheugen locaties met lees\nbij-effecten beinvloed. Als de parameter 'off' is dan zullen lees acties\ngeen bij-effecten vertonen. Als de parameter 'on' is dan zullen lees\nacties bij-effecten vertonen. Als de parameter 'toggle' is dan zal de\nhuidige modus worden geschakeld. Als er geen parameter is dan zal de\nhuidige modus worden getoond."},
	/* pl */ {IDGS_MON_SIDEFX_DESCRIPTION_PL, "Kontroluje w jaki sposÛb wygenerowane w monitorze odczyty po≥oøenia\nwp≥ywaj± na obszary pamiÍci, ktÛre maj± efekty uboczne odczytu.\nJe∂li argument to 'on', wtedy odczyty mog± powodowaÊ efekty uboczne.\nJe∂li argument to 'off', wtedy odczyty nie powoduj± efektÛw ubocznych.\nJe∂li argument to 'toggle', obecny tryb jest prze≥±czany.\nBrak argumentu pokazuje obecny stan."},
	/* ru */ {IDGS_MON_SIDEFX_DESCRIPTION_RU, "Control how monitor generated reads affect memory locations that have\nread side-effects.  If the argument is 'on' then reads may cause\nside-effects.  If the argument is 'off' then reads don't cause\nside-effects.  If the argument is 'toggle' then the current mode is\nswitched.  No argument displays the current state."},
	/* sv */ {IDGS_MON_SIDEFX_DESCRIPTION_SV, "Styr hur l‰sningar i monitorn pÂverkar minnesomrÂden som har\nsidoeffekter vid l‰sning. Om argumentet ‰r \"on\" tillÂts l‰sningar\natt orsaka sidoeffekter. Om argumentet ‰r \"off\" tillÂts inte\nl‰sningar att orsaka sidoeffekter. Om argumentet ‰r \"toggle\" byts\ndet nuvarande l‰get. Om du inte anger nÂgra argument visas\nnuvarande l‰ge."},
	/* tr */ {IDGS_MON_SIDEFX_DESCRIPTION_TR, "Okuma yan etkileri bulunan bellek konumlar˝n˝ monitˆr taraf˝ndan olu˛turulan\nokumalar˝n nas˝l etkilediini kontrol et.  Arg¸man 'on' ise, okumalar yan\netkiye neden olabilir.  Arg¸man 'off' ise okumalar˝n bir yan etkisi\nolmayacakt˝r.  Eer arg¸man 'toggle' ise geÁerli mod dei˛tirilecektir.\nArg¸man verilmemesi o anki durumu gˆr¸nt¸ler."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_DISK_COMMANDS,    N_("Disk commands:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DISK_COMMANDS_DA, "Diskettekommandoer:"},
	/* de */ {IDGS_DISK_COMMANDS_DE, "Disk Kommandos:"},
	/* es */ {IDGS_DISK_COMMANDS_ES, "Comandos de disco:"},
	/* fr */ {IDGS_DISK_COMMANDS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_DISK_COMMANDS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_DISK_COMMANDS_IT, "Comandi disco:"},
	/* ko */ {IDGS_DISK_COMMANDS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_DISK_COMMANDS_NL, "Disk commandos:"},
	/* pl */ {IDGS_DISK_COMMANDS_PL, "Polecenia dyskowe:"},
	/* ru */ {IDGS_DISK_COMMANDS_RU, "Disk commands:"},
	/* sv */ {IDGS_DISK_COMMANDS_SV, "Diskettkommandon:"},
	/* tr */ {IDGS_DISK_COMMANDS_TR, "Disk komutlar˝:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_DISK_COMMAND,    N_("disk command")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DISK_COMMAND_DA, "diskkommando"},
	/* de */ {IDGS_DISK_COMMAND_DE, "Disk Kommando"},
	/* es */ {IDGS_DISK_COMMAND_ES, "comando disco"},
	/* fr */ {IDGS_DISK_COMMAND_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_DISK_COMMAND_HU, ""},  /* fuzzy */
	/* it */ {IDGS_DISK_COMMAND_IT, "comando disco"},
	/* ko */ {IDGS_DISK_COMMAND_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_DISK_COMMAND_NL, "disk commando"},
	/* pl */ {IDGS_DISK_COMMAND_PL, "disk command"},
	/* ru */ {IDGS_DISK_COMMAND_RU, "disk command"},
	/* sv */ {IDGS_DISK_COMMAND_SV, "diskkommando"},
	/* tr */ {IDGS_DISK_COMMAND_TR, "disk komutu"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_AT_DESCRIPTION,    N_("Perform a disk command on the currently attached disk image on drive 8.\nThe specified disk command is sent to the drive's channel #15.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_AT_DESCRIPTION_DA, "Udf¯rer en diskkommando pÂ det diskette-image, der er tilsluttet\ndrev 8. Diskkommandoen sendes til drevets kanal #15."},
	/* de */ {IDGS_MON_AT_DESCRIPTION_DE, "F¸hre ein Diskkommando auf dem aktuell eingelegtem Diskimage auf Laufwerk 8\naus.\nDas angegebene Kommando wird auf dem Laufwerks Kommandokanal #15 geschickt."},
	/* es */ {IDGS_MON_AT_DESCRIPTION_ES, "Realiza un comando de disco en el actualmente insertado en unidad disco 8.\nEl comando de disco especificado se envia a traves del canal de control #15."},
	/* fr */ {IDGS_MON_AT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_AT_DESCRIPTION_HU, "Lemez parancs vÈgrehajt·sa az aktu·lisan csatolt lemezen, a 8-as egysÈgen.\nA megadott lemez parancsot a meghajtÛ #15-ˆs csatorn·j·ra k¸ldi."},
	/* it */ {IDGS_MON_AT_DESCRIPTION_IT, "Esegue un comando disco sull'immagine disco attualmente presente nel\ndrive 8. Il comando specificato Ë inviato al canale #15 del drive."},
	/* ko */ {IDGS_MON_AT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_AT_DESCRIPTION_NL, "Doe een disk commando operatie op de huidig gekoppelde disk bestand in drive\n8, Het opgegeven disk commando zal worden gestuurt naar kanaal #15 van de\ndrive."},
	/* pl */ {IDGS_MON_AT_DESCRIPTION_PL, "Wykonaj polecenie dyskowe na obecnie zamontowanym obrazie dyskietki\nw stacji 8. Dane polecenie jest wysy≥ane na kana≥ #15 stacji."},
	/* ru */ {IDGS_MON_AT_DESCRIPTION_RU, "Perform a disk command on the currently attached disk image on drive 8.\nThe specified disk command is sent to the drive's channel #15."},
	/* sv */ {IDGS_MON_AT_DESCRIPTION_SV, "Utfˆr ett diskkommando pÂ den diskettavbildning som ‰r ansluten till\nenhet 8. Diskkommandot s‰nds pÂ diskettenhetens kanal nummer 15."},
	/* tr */ {IDGS_MON_AT_DESCRIPTION_TR, "8 nolu s¸r¸c¸de tak˝l˝ disk imaj˝ ¸zerinde bir disk komutu Áal˝˛t˝r.\nBelirtilen disk komutu s¸r¸c¸n¸n 15 numaral˝ kanal˝na gˆnderilir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_DEVICE,    N_("device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DEVICE_DA, "enhed"},
	/* de */ {IDGS_DEVICE_DE, "Ger‰t"},
	/* es */ {IDGS_DEVICE_ES, "perifÈrico"},
	/* fr */ {IDGS_DEVICE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_DEVICE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_DEVICE_IT, "dispositivo"},
	/* ko */ {IDGS_DEVICE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_DEVICE_NL, "apparaat"},
	/* pl */ {IDGS_DEVICE_PL, "device"},
	/* ru */ {IDGS_DEVICE_RU, "device"},
	/* sv */ {IDGS_DEVICE_SV, "enhet"},
	/* tr */ {IDGS_DEVICE_TR, "ayg˝t"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_FILE_INDEX,    N_("file_index")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_FILE_INDEX_DA, "fil_indeks"},
	/* de */ {IDGS_FILE_INDEX_DE, "Datei_Index"},
	/* es */ {IDGS_FILE_INDEX_ES, "Õndice de fichero"},
	/* fr */ {IDGS_FILE_INDEX_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_FILE_INDEX_HU, ""},  /* fuzzy */
	/* it */ {IDGS_FILE_INDEX_IT, "file_index"},
	/* ko */ {IDGS_FILE_INDEX_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_FILE_INDEX_NL, "bestandsindex"},
	/* pl */ {IDGS_FILE_INDEX_PL, "file_index"},
	/* ru */ {IDGS_FILE_INDEX_RU, "file_index"},
	/* sv */ {IDGS_FILE_INDEX_SV, "filindex"},
	/* tr */ {IDGS_FILE_INDEX_TR, "dosya_indeksi"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_AUTOSTART_DESCRIPTION,    N_("autostart a given disk/tape image or program")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_AUTOSTART_DESCRIPTION_DA, "Autostart et givent disk-/bÂnd-image eller program"},
	/* de */ {IDGS_MON_AUTOSTART_DESCRIPTION_DE, "Autostart ein Disk/Band Image oder Programm"},
	/* es */ {IDGS_MON_AUTOSTART_DESCRIPTION_ES, "Autoarranque imagen de disco/cinta Û programa"},
	/* fr */ {IDGS_MON_AUTOSTART_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_AUTOSTART_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_AUTOSTART_DESCRIPTION_IT, "Avvia automaticamente immagine un'immagine disco/cassetta o programma"},
	/* ko */ {IDGS_MON_AUTOSTART_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_AUTOSTART_DESCRIPTION_NL, "autostart een opgegeven disk-/tapebestand of programma"},
	/* pl */ {IDGS_MON_AUTOSTART_DESCRIPTION_PL, "automatycznie uruchom dany program albo obraz dysku lub ta∂my"},
	/* ru */ {IDGS_MON_AUTOSTART_DESCRIPTION_RU, "autostart a given disk/tape image or program"},
	/* sv */ {IDGS_MON_AUTOSTART_DESCRIPTION_SV, "starta given disk-/bandavbildningsfil eller program automatiskt"},
	/* tr */ {IDGS_MON_AUTOSTART_DESCRIPTION_TR, "verilen disk/teyp imaj˝n˝ ya da program˝ otomatik ba˛lat"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_AUTOLOAD_DESCRIPTION,    N_("autoload given disk/tape image or program")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_AUTOLOAD_DESCRIPTION_DA, "Autoload et givent disk-/bÂnd-image eller program"},
	/* de */ {IDGS_MON_AUTOLOAD_DESCRIPTION_DE, "Autoload ein Disk/Band Image oder Programm"},
	/* es */ {IDGS_MON_AUTOLOAD_DESCRIPTION_ES, "Autocarga imagen de disco/cinta Û programa"},
	/* fr */ {IDGS_MON_AUTOLOAD_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_AUTOLOAD_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_AUTOLOAD_DESCRIPTION_IT, "Carica automaticamente immagine un'immagine disco/cassetta o programma"},
	/* ko */ {IDGS_MON_AUTOLOAD_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_AUTOLOAD_DESCRIPTION_NL, "autolaad een opgegeven disk-/tapebestand of programma"},
	/* pl */ {IDGS_MON_AUTOLOAD_DESCRIPTION_PL, "automatycznie wczytaj dany program albo obraz dysku lub ta∂my"},
	/* ru */ {IDGS_MON_AUTOLOAD_DESCRIPTION_RU, "autoload given disk/tape image or program"},
	/* sv */ {IDGS_MON_AUTOLOAD_DESCRIPTION_SV, "l‰s in given disk-/bandavbildningsfil eller program automatiskt"},
	/* tr */ {IDGS_MON_AUTOLOAD_DESCRIPTION_TR, "verilen disk/teyp imaj˝n˝ ya da program˝ otomatik y¸klet"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_ATTACH_DESCRIPTION,    N_("Attach file to device. (device 32 = cart)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_ATTACH_DESCRIPTION_DA, "Tilslut en fil til enhed. (enhed 32 = cartridge)"},
	/* de */ {IDGS_MON_ATTACH_DESCRIPTION_DE, "Benutze Datei f¸r das Ger‰t. (Ger‰t 32 = Modul)"},
	/* es */ {IDGS_MON_ATTACH_DESCRIPTION_ES, "Inserta fichero en perifÈrico (perifÈrico 32=cartucho)"},
	/* fr */ {IDGS_MON_ATTACH_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_ATTACH_DESCRIPTION_HU, "F·jl csatol·sa az eszkˆzhˆz. (32-es eszkˆz = cart)"},
	/* it */ {IDGS_MON_ATTACH_DESCRIPTION_IT, "Seleziona il file per la perifica. (periferica 32 = cartuccia)"},
	/* ko */ {IDGS_MON_ATTACH_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_ATTACH_DESCRIPTION_NL, "Koppel bestand aan apparaat. (apparaat 32 = cart"},
	/* pl */ {IDGS_MON_ATTACH_DESCRIPTION_PL, "Pod≥±cz plik pod urz±dzenie (urz±dzenie 32 = cart)"},
	/* ru */ {IDGS_MON_ATTACH_DESCRIPTION_RU, "Attach file to device. (device 32 = cart)"},
	/* sv */ {IDGS_MON_ATTACH_DESCRIPTION_SV, "Anslut en fil till en enhet. (enhet 32 = insticksmodul)"},
	/* tr */ {IDGS_MON_ATTACH_DESCRIPTION_TR, "Ayg˝ta dosya yerle˛tir. (ayg˝t 32 = kartu˛)"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_BLOAD_DESCRIPTION,    N_("Load the specified file into memory at the specified address.\nIf device is 0, the file is read from the file system.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_BLOAD_DESCRIPTION_DA, "IndlÊs den angivne fil til hukommelsen pÂ den angivne adresse.\nHvis enhed er 0 lÊses fra filsystemet."},
	/* de */ {IDGS_MON_BLOAD_DESCRIPTION_DE, "Lade angegebene Datei in den Speicher an die angegebene Adresse.\nBei Ger‰t 0, wird die Datei vom Dateisystem gelesen."},
	/* es */ {IDGS_MON_BLOAD_DESCRIPTION_ES, "Cargar el fichero especificado en memoria en la direccciÛn indicada en\ndirecciÛn. Si el perifÈrico es 0 el fichero se lee desde sistema."},
	/* fr */ {IDGS_MON_BLOAD_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_BLOAD_DESCRIPTION_HU, "A megadott f·jl betˆltÈse a memÛri·ba a megadott cÌmre.\nHa az eszkˆz 0, a f·jlt a f·jlrendszerbıl olvassa."},
	/* it */ {IDGS_MON_BLOAD_DESCRIPTION_IT, "Carica il file specificato in memoria all'indirizzo specificato.\nSe la periferica Ë 0, il file Ë letto dal file system."},
	/* ko */ {IDGS_MON_BLOAD_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_BLOAD_DESCRIPTION_NL, "Laad het opgegeven bestand naar het geheugen met het opgegeven adres.\nAls het apparaat 0 is dan zal het bestand van het bestandssysteem\nworden geladen."},
	/* pl */ {IDGS_MON_BLOAD_DESCRIPTION_PL, "Wczytaj dany plik do pamiÍci w okre∂lonym adresie.\nJe∂li urz±dzenie to 0, plik jest czytany z systemu plikÛw."},
	/* ru */ {IDGS_MON_BLOAD_DESCRIPTION_RU, "Load the specified file into memory at the specified address.\nIf device is 0, the file is read from the file system."},
	/* sv */ {IDGS_MON_BLOAD_DESCRIPTION_SV, "L‰s den angivna filen till minnet pÂ den angivna adressen.\nOm enheten ‰r 0 l‰ses filen frÂn filsystemet."},
	/* tr */ {IDGS_MON_BLOAD_DESCRIPTION_TR, "Belirtilmi˛ dosyay˝ belirtilen adresten itibaren bellee y¸kle.\nAyg˝t 0 ise, dosya dosya sistemi ¸zerinden okunur."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_TRACK,    N_("track")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_TRACK_DA, "spor"},
	/* de */ {IDGS_TRACK_DE, "Spur"},
	/* es */ {IDGS_TRACK_ES, "Pista"},
	/* fr */ {IDGS_TRACK_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_TRACK_HU, ""},  /* fuzzy */
	/* it */ {IDGS_TRACK_IT, "traccia"},
	/* ko */ {IDGS_TRACK_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_TRACK_NL, "spoor"},
	/* pl */ {IDGS_TRACK_PL, "track"},
	/* ru */ {IDGS_TRACK_RU, "track"},
	/* sv */ {IDGS_TRACK_SV, "spÂr"},
	/* tr */ {IDGS_TRACK_TR, "track"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_SECTOR,    N_("sector")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_SECTOR_DA, "sektor"},
	/* de */ {IDGS_SECTOR_DE, "Sektor"},
	/* es */ {IDGS_SECTOR_ES, "sector"},
	/* fr */ {IDGS_SECTOR_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_SECTOR_HU, ""},  /* fuzzy */
	/* it */ {IDGS_SECTOR_IT, "settore"},
	/* ko */ {IDGS_SECTOR_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_SECTOR_NL, "sector"},
	/* pl */ {IDGS_SECTOR_PL, "sector"},
	/* ru */ {IDGS_SECTOR_RU, "·’⁄‚ﬁ‡"},
	/* sv */ {IDGS_SECTOR_SV, "sektor"},
	/* tr */ {IDGS_SECTOR_TR, "sektˆr"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_BLOCK_READ_DESCRIPTION,    N_("Read the block at the specified track and sector.  If an address is\nspecified, the data is loaded into memory.  If no address is given, the\ndata is displayed using the default datatype.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_BLOCK_READ_DESCRIPTION_DA, "LÊser en blok fra det angivne spor og sektor. Hvis en adresse angives\nindlÊses data til hukommelsen. Hvis der ikke angives nogen adresse vises\nindholdet med standarddatatypen."},
	/* de */ {IDGS_MON_BLOCK_READ_DESCRIPTION_DE, "Lese den Block von angegebener Spur und Sektor. Wenn eine Adresse\nangegeben wurde, lade in auf die entsprechende Adresse. Wenn keine Adresse\nangegeben ist, zeige die Daten im aktuellen Anzeigemodus f¸r Daten."},
	/* es */ {IDGS_MON_BLOCK_READ_DESCRIPTION_ES, "Leer bloque en la pista y sector especificados. Si la direcciÛn se\nespecifica, el dato se carga en memoria, si no, el dato se muestra\nusando el tipo dato por defecto."},
	/* fr */ {IDGS_MON_BLOCK_READ_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_BLOCK_READ_DESCRIPTION_HU, "Blokk beolvas·sa a megadott s·vbÛl Ès szektorbÛl.,  Ha egy cÌm is meg\nvan adva, az adatot a memÛri·ba tˆlti.  Ha az nincs, az\nadatot az alapbe·llÌt·s szerinti form·ban mutatja."},
	/* it */ {IDGS_MON_BLOCK_READ_DESCRIPTION_IT, "Legge il blocco dalla traccia e settore specificati. Se Ë specificato\nun indirizzo, il dato Ë caricato in memoria. Se non Ë specificato alcun\nindirizzo, il dato Ë mostrato usando il tipo di dato predefinito."},
	/* ko */ {IDGS_MON_BLOCK_READ_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_BLOCK_READ_DESCRIPTION_NL, "Lees het blok van de opgegeven spoor en sector. Als er een adres is\nopgegeven dan zal de data naar dat adres in geheugen worden geladen.\nAls er geen adres is opgegeven dan zal de data worder getoond met de\nhuidige datasoort."},
	/* pl */ {IDGS_MON_BLOCK_READ_DESCRIPTION_PL, "Czytaj blok z danej ∂cieøki i sektora. Je∂li okre∂lono adres, dane s±\nwczytywane do pamiÍci. Je∂li nie podano adresu, dane s± pokazane\nw domy∂lnym typie danych."},
	/* ru */ {IDGS_MON_BLOCK_READ_DESCRIPTION_RU, "Read the block at the specified track and sector.  If an address is\nspecified, the data is loaded into memory.  If no address is given, the\ndata is displayed using the default datatype."},
	/* sv */ {IDGS_MON_BLOCK_READ_DESCRIPTION_SV, "L‰ser blocket pÂ det angivna spÂret och sektorn. Om du anger en\nadress l‰ses data till minnet. Om du inte anger nÂgon adress visas\ninnehÂllet enligt standarddatatypen."},
	/* tr */ {IDGS_MON_BLOCK_READ_DESCRIPTION_TR, "Belirtilmi˛ track ve sektˆrdeki blou oku.  Eer bir adres belirtilmi˛se,\nveri bellee y¸klenir.  Eer adres belirtilmemi˛se, veri varsay˝lan veri\ntipi kullan˝larak gˆr¸nt¸lenir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_BSAVE_DESCRIPTION,    N_("Save the memory from address1 to address2 to the specified file.\nIf device is 0, the file is written to the file system.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_BSAVE_DESCRIPTION_DA, "Gem hukommelsen fra adresse1 til adresse2 til den angivne fil.\nHvis enhed er 0 skrives til filsystemet."},
	/* de */ {IDGS_MON_BSAVE_DESCRIPTION_DE, "Speichere den Speicherinhalt von Adresse1 zu Adresse2 in die angegebene Datei.\nWenn das Ger‰t 0 angegeben wurde, speichere im Dateisystem."},
	/* es */ {IDGS_MON_BSAVE_DESCRIPTION_ES, "Grabar la memoria entre direcciÛn 1 y direcciÛn2 al fichero indicado.\nSi el perifÈrico es 0, el fichero se graba en el fichero del sistema."},
	/* fr */ {IDGS_MON_BSAVE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_BSAVE_DESCRIPTION_HU, "A memÛria cÌm1 Ès cÌm2 kˆzˆtti rÈszÈnek f·jlba mentÈse.\nHa az eszkˆz 0, a f·jl a f·jlrendszerbe ker¸l."},
	/* it */ {IDGS_MON_BSAVE_DESCRIPTION_IT, "Salva la memoria compresa tra indirizzo1 e indirizzo2 sul file specificato.\nSe la periferica Ë 0, il file Ë scritto sul file system."},
	/* ko */ {IDGS_MON_BSAVE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_BSAVE_DESCRIPTION_NL, "Sla het geheugen tussen adres1 en adres2 op naar het opgegeven bestand.\nAls het apparaat 0 is dan zal het bestand naar het bestandssysteem worden\ngeschreven."},
	/* pl */ {IDGS_MON_BSAVE_DESCRIPTION_PL, "Zapisz pamiÍÊ z adres1 do adres2 do okre∂lonego pliku.\nJe∂li urz±dzenie to 0, plik jest zapisywany do systemu plikÛw."},
	/* ru */ {IDGS_MON_BSAVE_DESCRIPTION_RU, "Save the memory from address1 to address2 to the specified file.\nIf device is 0, the file is written to the file system."},
	/* sv */ {IDGS_MON_BSAVE_DESCRIPTION_SV, "Spara minnet frÂn adress1 till adress2 till den angivna filen.\nOm enheten ‰r 0 skrivs filen till filsystemet."},
	/* tr */ {IDGS_MON_BSAVE_DESCRIPTION_TR, "Adres1'den adres2'ye kadar olan bellei belirtilen dosyaya kaydet.\nEer ayg˝t 0 ise, dosya dosya sistemine yaz˝l˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION,    N_("Write a block of data at `address' on the specified track and sector\nof disk in drive 8.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_DA, "Skriv datablok pÂ \"adresse\" til det angivne spor og sektor\npÂ disken i drev 8."},
	/* de */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_DE, "Schreibe einen Datenblock von `Adresse' auf die angegebene Spure und Sektor\nin die Imagedatei von Laufwerk 8."},
	/* es */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_ES, "Grabar un bloque de datos en 'direcciÛn' en la pista y sector indicados\ndel disco en la unidad de discos 8."},
	/* fr */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_HU, "Egy adat blokk Ìr·sa `cÌm' helyrıl a megadott s·vba Ès szektorba\na 8-as meghajtÛn."},
	/* it */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_IT, "Scrive il blocco di dati all'indirizzo sulla traccia e settore specificati\ndel disco nel drive 8."},
	/* ko */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_NL, "Schrijf een data blok van `adres' naar de opgegeven spoor en sector van\nde disk in drive 8."},
	/* pl */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_PL, "Zapisz blok danych w `address' w podanej ∂cieøce i sektorze\ndysku w stacji 8."},
	/* ru */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_RU, "Write a block of data at `address' on the specified track and sector\nof disk in drive 8."},
	/* sv */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_SV, "Skriv ett datablock pÂ \"adress\" till det angivna spÂret och sektorn\npÂ disken i enhet 8."},
	/* tr */ {IDGS_MON_BLOCK_WRITE_DESCRIPTION_TR, "Belirtilmi˛ track ve sektˆrlerde `adres'te yer alan veri blounu 8\nnumaral˝ s¸r¸c¸deki diske yaz."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_DIRECTORY,    N_("Directory")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_DIRECTORY_DA, "Katalog"},
	/* de */ {IDGS_DIRECTORY_DE, "Verzeichnis"},
	/* es */ {IDGS_DIRECTORY_ES, "Directorio"},
	/* fr */ {IDGS_DIRECTORY_FR, "RÈpertoire"},
	/* hu */ {IDGS_DIRECTORY_HU, ""},  /* fuzzy */
	/* it */ {IDGS_DIRECTORY_IT, "Directory"},
	/* ko */ {IDGS_DIRECTORY_KO, "µ∑∫≈‰∏Æ"},
	/* nl */ {IDGS_DIRECTORY_NL, "Directory"},
	/* pl */ {IDGS_DIRECTORY_PL, "Katalog"},
	/* ru */ {IDGS_DIRECTORY_RU, "ø–ﬂ⁄–"},
	/* sv */ {IDGS_DIRECTORY_SV, "Katalog"},
	/* tr */ {IDGS_DIRECTORY_TR, "Dizin"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_P_DIRECTORY,    N_("<Directory>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_P_DIRECTORY_DA, "<Katalog>"},
	/* de */ {IDGS_P_DIRECTORY_DE, "<Verzeichnis>"},
	/* es */ {IDGS_P_DIRECTORY_ES, "<Directorio>"},
	/* fr */ {IDGS_P_DIRECTORY_FR, "<RÈpertoire>"},
	/* hu */ {IDGS_P_DIRECTORY_HU, ""},  /* fuzzy */
	/* it */ {IDGS_P_DIRECTORY_IT, "<Directory>"},
	/* ko */ {IDGS_P_DIRECTORY_KO, "<µ∑∫≈‰∏Æ>"},
	/* nl */ {IDGS_P_DIRECTORY_NL, "<Directory>"},
	/* pl */ {IDGS_P_DIRECTORY_PL, "<Katalog>"},
	/* ru */ {IDGS_P_DIRECTORY_RU, "<ø–ﬂ⁄–>"},
	/* sv */ {IDGS_P_DIRECTORY_SV, "<Katalog>"},
	/* tr */ {IDGS_P_DIRECTORY_TR, "<Dizin>"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_CD_DESCRIPTION,    N_("Change current working directory.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_CD_DESCRIPTION_DA, "Skift aktuelt arbejdskatalog"},
	/* de */ {IDGS_MON_CD_DESCRIPTION_DE, "Arbeitsverzeichnis ‰ndern."},
	/* es */ {IDGS_MON_CD_DESCRIPTION_ES, "Cambiar directorio de trabajo actual."},
	/* fr */ {IDGS_MON_CD_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_CD_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_CD_DESCRIPTION_IT, "Cambia la directory di lavoro."},
	/* ko */ {IDGS_MON_CD_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_CD_DESCRIPTION_NL, "Verander de huidige werk directory"},
	/* pl */ {IDGS_MON_CD_DESCRIPTION_PL, "ZmieÒ obecny katalog roboczy"},
	/* ru */ {IDGS_MON_CD_DESCRIPTION_RU, "¡‹’›ÿ‚Ï ‚’⁄„È„Ó ‡–—ﬁÁ„Ó ‘ÿ‡’⁄‚ﬁ‡ÿÓ."},
	/* sv */ {IDGS_MON_CD_DESCRIPTION_SV, "ƒndra aktuell arbetskatalog"},
	/* tr */ {IDGS_MON_CD_DESCRIPTION_TR, "GeÁerli Áal˝˛ma dizinini dei˛tir."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DETACH_DESCRIPTION,    N_("Detach file from device. (device 32 = cart)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DETACH_DESCRIPTION_DA, "Frakobl filen fra enheden. (enhed 32 = cartridge)"},
	/* de */ {IDGS_MON_DETACH_DESCRIPTION_DE, "Entferne Datei von Ger‰t. (Ger‰t 32 = Modul)"},
	/* es */ {IDGS_MON_DETACH_DESCRIPTION_ES, "Extraer fichero desde el perifÈrico (perifÈrico 32 = cartucho)"},
	/* fr */ {IDGS_MON_DETACH_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DETACH_DESCRIPTION_HU, "F·jl lev·laszt·sa az eszkˆzrıl. (32-es eszkˆz = cart)"},
	/* it */ {IDGS_MON_DETACH_DESCRIPTION_IT, "Rimuovi il file dalla periferica. (periferica 32 = cart)"},
	/* ko */ {IDGS_MON_DETACH_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DETACH_DESCRIPTION_NL, "Ontkoppel bestand van apparaat. (apparaat 32 = cart)"},
	/* pl */ {IDGS_MON_DETACH_DESCRIPTION_PL, "Od≥±cz plik od urz±dzenia (urz±dzenie 32 = cart)"},
	/* ru */ {IDGS_MON_DETACH_DESCRIPTION_RU, "Detach file from device. (device 32 = cart)"},
	/* sv */ {IDGS_MON_DETACH_DESCRIPTION_SV, "Koppla frÂn filen frÂn enheten. (enhet 32 = insticksmodul)"},
	/* tr */ {IDGS_MON_DETACH_DESCRIPTION_TR, "Ayg˝ttan dosya Á˝kart. (ayg˝t 32 = kartu˛)"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DIR_DESCRIPTION,    N_("Display the directory contents.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DIR_DESCRIPTION_DA, "Vis katalogets indhold."},
	/* de */ {IDGS_MON_DIR_DESCRIPTION_DE, "Zeige den Verzeichnisinhalt."},
	/* es */ {IDGS_MON_DIR_DESCRIPTION_ES, "Mostrar los contenidos del directorio"},
	/* fr */ {IDGS_MON_DIR_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DIR_DESCRIPTION_HU, "A kˆnyvt·r tartalm·nak mutat·sa."},
	/* it */ {IDGS_MON_DIR_DESCRIPTION_IT, "Mostra il contenuto della directory."},
	/* ko */ {IDGS_MON_DIR_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DIR_DESCRIPTION_NL, "Toon de directory inhoud."},
	/* pl */ {IDGS_MON_DIR_DESCRIPTION_PL, "Pokaø zawarto∂Ê katalogu."},
	/* ru */ {IDGS_MON_DIR_DESCRIPTION_RU, "æ‚ﬁ—‡–◊ÿ‚Ï ·ﬁ‘’‡÷–›ÿ’ ‘ÿ‡’⁄‚ﬁ‡ÿÿ."},
	/* sv */ {IDGS_MON_DIR_DESCRIPTION_SV, "Visa katalogens innehÂll."},
	/* tr */ {IDGS_MON_DIR_DESCRIPTION_TR, "Dizin iÁeriini gˆr¸nt¸le."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_LIST_DESCRIPTION,    N_("List disk contents.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_LIST_DESCRIPTION_DA, "Vis diskens indhold."},
	/* de */ {IDGS_MON_LIST_DESCRIPTION_DE, "Zeige den Verzeichnisinhalt."},
	/* es */ {IDGS_MON_LIST_DESCRIPTION_ES, "Listado contenidos disco"},
	/* fr */ {IDGS_MON_LIST_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_LIST_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_LIST_DESCRIPTION_IT, "Elenca i contenuti del disco."},
	/* ko */ {IDGS_MON_LIST_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_LIST_DESCRIPTION_NL, "Toon disk inhoud."},
	/* pl */ {IDGS_MON_LIST_DESCRIPTION_PL, "Pokaø zawarto∂Ê dysku"},
	/* ru */ {IDGS_MON_LIST_DESCRIPTION_RU, "List disk contents."},
	/* sv */ {IDGS_MON_LIST_DESCRIPTION_SV, "Visa diskens innehÂll"},
	/* tr */ {IDGS_MON_LIST_DESCRIPTION_TR, "Disk iÁeriini listele."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_LOAD_DESCRIPTION,    N_("Load the specified file into memory at the specified address. Set BASIC\npointers appropriately if loaded into computer memory (not all emulators).\nUse (otherwise ignored) two-byte load address from file if no address\nspecified.\nIf device is 0, the file is read from the file system.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_LOAD_DESCRIPTION_DA, "IndlÊs filen i hukommelsen pÂ den angivne adresse. Opdaterer\nBASIC-pointers ved lÊsning til computerens hukommelse (ikke alle\nemulatorer). Hvis ingen adresse angives bruges load-adressen fra(som ellers ignoreres).\nHvis enhed er 0 lÊses fra filsystemet."},
	/* de */ {IDGS_MON_LOAD_DESCRIPTION_DE, "Lade die angegebene Datei in den Speicher auf die angegebene Adresse.\nSetze den BASIC Zeiger entsprechend, wenn in den Rechnerspeicher geladen \nwurde (nicht bei allen Emulatoren!).\nVerwende (sonst ignoriert) die zwei-Byte Lade-Adresse aus der Datei, wenn\nkeine Adresse angegeben wurde.\nBei Ger‰t 0, wird die Datei vom Dateisystem gelade."},
	/* es */ {IDGS_MON_LOAD_DESCRIPTION_ES, "Cargar el fichero especificado en la direcciÛn de memoria indicada. Actualizar\npunteros BASIC apropiadamente si se carga en la memoria del ordenador\n(no en todos los emuladores).\nUsar direcciÛn de dos bytes del fichero si no se indica otra direcciÛn.\nSi el perifÈrico es 0, el fichero se lee del sistema."},
	/* fr */ {IDGS_MON_LOAD_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_LOAD_DESCRIPTION_HU, "A megadott f·jl betˆltÈse a megadott cÌmre. A BASIC mutatÛkat\na megfelelı mÛdon be·llÌtja, ha a sz·mÌtÛgÈp memÛri·ba tˆlti az adatot\n(nem minden emul·torn·l). Ha nincs cÌm megadva, az am˙gy figyelmen hagyott\nkÈt b·jtos betˆltÈsi cÌmet haszn·lja a f·jlbÛl.\nHa az eszkˆz 0, a f·jlt a f·jlrendszerrıl olvassa."},
	/* it */ {IDGS_MON_LOAD_DESCRIPTION_IT, "Carica il file specificato in memroia all'indirizzo specificato. Imposta\ni puntatori del BASIC in modo appropriato se caricato nella memoria\ndel computer (non su tutti gli emulatori).\nUsa (altrimenti ignora) l'indirizzo di caricamento su due byte del file\nse non viene specificato alcun indirizzo.\nSe la periferica Ë 0, il file viene letto dal file system."},
	/* ko */ {IDGS_MON_LOAD_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_LOAD_DESCRIPTION_NL, "Laad het opgegeven bestand naar geheugen op het opgegeven adres. Zet de BASIC\nstart en eind indicators correct als het bestand naar het computer geheugen\ngeladen wordt (niet alle emulatoren). De eerste twee bytes van het bestand\nzullen als laad adres worden gebruikt als er geen adres is opgegeven. Als\nhet apparaat 0 is dan zal het bestand van het bestandssysteem worden geladen."},
	/* pl */ {IDGS_MON_LOAD_DESCRIPTION_PL, "Wczytaj podany plik do pamiÍci w konkretnym adresie. Ustaw wskaºniki\nBASIC odpowiednio, jesli zostan± wczytane do pamiÍci komputera\n(nie wszystkie emulatory). Uøyj (w innym razie ignoruje) dwubajtowego\nadresu wczytywania z pliku, je∂li nie zosta≥ podany adres.\nJe∂li urz±dzenie jest 0, plik zostaje oczytany z systemu plikÛw."},
	/* ru */ {IDGS_MON_LOAD_DESCRIPTION_RU, "Load the specified file into memory at the specified address. Set BASIC\npointers appropriately if loaded into computer memory (not all emulators).\nUse (otherwise ignored) two-byte load address from file if no address\nspecified.\nIf device is 0, the file is read from the file system."},
	/* sv */ {IDGS_MON_LOAD_DESCRIPTION_SV, "L‰s in den angivna filen i minnet pÂ den angivna adressen. S‰tter\nmotsvarande BASIC-pekare vid l‰sning till datorminnet (inte alla\nemulatorer). Om ingen adress anges anv‰nds tvÂbytesadressen i filen(ignoreras annars).\nOm enheten ‰r 0 l‰ses filen frÂn filsystemet."},
	/* tr */ {IDGS_MON_LOAD_DESCRIPTION_TR, "Belirtilmi˛ dosyay˝ belirtilen adresten itibaren bellee y¸kle. Eer\nbilgisayar belleine y¸klenmi˛se BASIC imleÁlerini uygun bir biÁimde\nayarla (t¸m em¸latˆrlerde deil). Eer adres belirtilmemi˛se iki bytel˝k\ndosya y¸kleme adresini kullan (dier ihtimalde yoksay).\nEer ayg˝t 0 ise, dosya dosya sisteminden okunur."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_PWD_DESCRIPTION,    N_("Show current working directory.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_PWD_DESCRIPTION_DA, "Vis aktuelt arbejdskatalog."},
	/* de */ {IDGS_MON_PWD_DESCRIPTION_DE, "Zeige aktuelles Arbeitsverzeichnis."},
	/* es */ {IDGS_MON_PWD_DESCRIPTION_ES, "Muestra el directorio de trabajo actual"},
	/* fr */ {IDGS_MON_PWD_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_PWD_DESCRIPTION_HU, "Munkakˆnyvt·r mutat·sa."},
	/* it */ {IDGS_MON_PWD_DESCRIPTION_IT, "Mostra la directory di lavoro attuale."},
	/* ko */ {IDGS_MON_PWD_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_PWD_DESCRIPTION_NL, "Toon de huidige werk directory."},
	/* pl */ {IDGS_MON_PWD_DESCRIPTION_PL, "Pokaø obecny katalog roboczy."},
	/* ru */ {IDGS_MON_PWD_DESCRIPTION_RU, "æ‚ﬁ—‡–◊ÿ‚Ï ‚’⁄„È„Ó ‡–—ﬁÁ„Ó ‘ÿ‡’⁄‚ﬁ‡ÿÓ."},
	/* sv */ {IDGS_MON_PWD_DESCRIPTION_SV, "Visa aktuell arbetskatalog."},
	/* tr */ {IDGS_MON_PWD_DESCRIPTION_TR, "GeÁerli Áal˝˛ma dizinini gˆster."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_SAVE_DESCRIPTION,    N_("Save the memory from address1 to address2 to the specified file.\nWrite two-byte load address.\nIf device is 0, the file is written to the file system.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_SAVE_DESCRIPTION_DA, "Gem hukommelsen fra  adresse1 til adresse2 til den angivne fil.\nSkriv 2-byte loadadresse i starten af filen.\nHvis enhed er 0 skrives til filsystemet."},
	/* de */ {IDGS_MON_SAVE_DESCRIPTION_DE, "Speichere den Speicher von Adresse1 bis Adresse2 in die angegebene Datei.\nSchreibe eine zwei-Byte Lade Adresse.\nBei Ger‰t 0, wird dei Datei in das Dateisystem geschrieben."},
	/* es */ {IDGS_MON_SAVE_DESCRIPTION_ES, "Graba memoria entre direcciÛn1 y direcciÛn2 al fichero indicado.\nGraba direcciÛn de carga de dos bytes.\nSi el periferico es 0, se graba en el sistema."},
	/* fr */ {IDGS_MON_SAVE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_SAVE_DESCRIPTION_HU, "A memÛria cÌm1 Ès cÌm2 kˆzˆtti tartom·ny·nak f·jlba mentÈse.\nA kÈtb·jtos betˆltÈsi cÌmet is kiÌrja.\nHa az eszkˆz 0, a f·jlt a f·jlrendszeren hozza lÈtre."},
	/* it */ {IDGS_MON_SAVE_DESCRIPTION_IT, "Salva la memoria compresa tra indirizzo1 e indirizzo2 sul file\nspecificato.\nScrive l'indirizzo di caricamento su due byte.\nSe la periferica Ë 0, il file Ë scritto sul file system."},
	/* ko */ {IDGS_MON_SAVE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_SAVE_DESCRIPTION_NL, "Sla het geheugen tussen adres1 en adres2 op naar het opgegeven bestand.\nSchrijf een load adres van twee bytes.\nAls het apparaat 0 is dan zal het bestand geschreven worden naar het\nbestandssysteem."},
	/* pl */ {IDGS_MON_SAVE_DESCRIPTION_PL, "Zapisz pamiÍÊ od address1 do address2 do podanego pliku.\nZapisz dwubajtowy adres wczytania.\nJe∂li urz±dzenie jest 0, plik zostaje zapisany do systemu plikÛw."},
	/* ru */ {IDGS_MON_SAVE_DESCRIPTION_RU, "Save the memory from address1 to address2 to the specified file.\nWrite two-byte load address.\nIf device is 0, the file is written to the file system."},
	/* sv */ {IDGS_MON_SAVE_DESCRIPTION_SV, "Spara minnet frÂn adress1 till adress2 till den angivna filen.\nSkriv tvÂbytes inl‰sningsadress.\nOm enheten ‰r 0 skrivs filen till filsystemet."},
	/* tr */ {IDGS_MON_SAVE_DESCRIPTION_TR, "Adres1'den adres2'ye kadar olan bellei belirtilen dosyaya kaydet.\n›ki bytel˝k y¸keme adresini yaz.\nEer ayg˝t 0 ise, dosya dosya sistemine yaz˝l˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_OTHER_COMMANDS,    N_("Other commands:")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_OTHER_COMMANDS_DA, "Andre kommandoer:"},
	/* de */ {IDGS_OTHER_COMMANDS_DE, "Andere Kommandos:"},
	/* es */ {IDGS_OTHER_COMMANDS_ES, "Otros comandos:"},
	/* fr */ {IDGS_OTHER_COMMANDS_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_OTHER_COMMANDS_HU, ""},  /* fuzzy */
	/* it */ {IDGS_OTHER_COMMANDS_IT, "Altri comandi:"},
	/* ko */ {IDGS_OTHER_COMMANDS_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_OTHER_COMMANDS_NL, "Andere commandos:"},
	/* pl */ {IDGS_OTHER_COMMANDS_PL, "Pozosta≥e polecenia:"},
	/* ru */ {IDGS_OTHER_COMMANDS_RU, "¥‡„”ÿ’ ⁄ﬁ‹–›‘Î:"},
	/* sv */ {IDGS_OTHER_COMMANDS_SV, "Andra kommandon:"},
	/* tr */ {IDGS_OTHER_COMMANDS_TR, "Dier komutlar:"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION,    N_("Display the specified number in decimal, hex, octal and binary.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_DA, "Vis det angivne tal som decimal, hexadecimal, oktal og binÊrt."},
	/* de */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_DE, "Zeige die angegebene Zahl in dezimal, hexadezimal, oktal oder bin‰r."},
	/* es */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_ES, "Mostrar el numero indicado en decimal, hex, octal y binario."},
	/* fr */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_HU, "A megadott sz·m kiÌr·sa decim·lisan, hexadecim·lisan, okt·lisan Ès bin·risan."},
	/* it */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_IT, "Mostra il numero specificato in decimale, esadecimale, ottale e binario."},
	/* ko */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_NL, "Toon het opgegeven nummer in decimaal, hex, octaal en binair."},
	/* pl */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_PL, "Pokaø dan± liczbÍ w systemie dziesiÍtnym, szesnastkowym, Ûsemkowym i binarnym."},
	/* ru */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_RU, "Display the specified number in decimal, hex, octal and binary."},
	/* sv */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_SV, "Visa det angivna talet decimalt, hexadecimalt, oktalt och bin‰rt."},
	/* tr */ {IDGS_MON_DISPLAY_NUMBER_DESCRIPTION_TR, "Belirtilen say˝y˝ 10'lu, 16'l˝, 8'li ya da 2'li olarak gˆr¸nt¸le."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_CARTFREEZE_DESCRIPTION,    N_("Use cartridge freeze.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_CARTFREEZE_DESCRIPTION_DA, "Brug cartridge frys-funktion."},
	/* de */ {IDGS_MON_CARTFREEZE_DESCRIPTION_DE, "Erweiterungsmodul Freeze benutzen."},
	/* es */ {IDGS_MON_CARTFREEZE_DESCRIPTION_ES, "Usar congelaciÛn cartucho"},
	/* fr */ {IDGS_MON_CARTFREEZE_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_CARTFREEZE_DESCRIPTION_HU, "Cartridge fagyaszt·s haszn·lata."},
	/* it */ {IDGS_MON_CARTFREEZE_DESCRIPTION_IT, "Usa freeze della cartuccia."},
	/* ko */ {IDGS_MON_CARTFREEZE_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_CARTFREEZE_DESCRIPTION_NL, "Gebruik cartridge freeze."},
	/* pl */ {IDGS_MON_CARTFREEZE_DESCRIPTION_PL, "Uøyj zamroøenia kartridøa"},
	/* ru */ {IDGS_MON_CARTFREEZE_DESCRIPTION_RU, "Use cartridge freeze."},
	/* sv */ {IDGS_MON_CARTFREEZE_DESCRIPTION_SV, "Anv‰nd insticksmodulens frysfunktion."},
	/* tr */ {IDGS_MON_CARTFREEZE_DESCRIPTION_TR, "Kartu˛ freeze kullan"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_HELP_DESCRIPTION,    N_("If no argument is given, prints out a list of all available commands\nIf an argument is given, prints out specific help for that command.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_HELP_DESCRIPTION_DA, "Hvis der ikke angives et argument vises en liste over mulige kommandoer.\nAngives et argument vises hjÊlp for denne kommando."},
	/* de */ {IDGS_MON_HELP_DESCRIPTION_DE, "Wenn kein Argement angegeben wurde, werden alle Kommandos ausgegeben.\nMit Argument, zeige die Hilfe f¸r das angegebene Kommand."},
	/* es */ {IDGS_MON_HELP_DESCRIPTION_ES, "Si no se muestran argumentos, imprime salida de todos los comandos disponibles\nSi se da un argumento, imprime la ayuda especÌfica para el comando."},
	/* fr */ {IDGS_MON_HELP_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_HELP_DESCRIPTION_HU, "Ha nincs paramÈter, az ˆsszes lÈtezı parancs list·j·t mutatja.\nHa van, az adott parancshoz mutatja a s˙gÛt."},
	/* it */ {IDGS_MON_HELP_DESCRIPTION_IT, "Se non viene specificato alcun argomeno, stamapa la lista di tutti i\ncomandi disponibili.\nSe viene specificato un argomento, stampa l'aiuto relativo a quel\ncomando."},
	/* ko */ {IDGS_MON_HELP_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_HELP_DESCRIPTION_NL, "Als er geen parameter is opgegeven dan zal een lijst van alle commandos\nworden weergegeven. Als er een parameter is opgegeven dan zal de help voor\nhet opgegeven command worden weergegeven."},
	/* pl */ {IDGS_MON_HELP_DESCRIPTION_PL, "Je∂li nie jest podany argument, pokazuje listÍ dostÍpnych poleceÒ.\nJe∂li zosta≥ podany argument, pokazuje pomoc do tego polecenia."},
	/* ru */ {IDGS_MON_HELP_DESCRIPTION_RU, "If no argument is given, prints out a list of all available commands\nIf an argument is given, prints out specific help for that command."},
	/* sv */ {IDGS_MON_HELP_DESCRIPTION_SV, "Om du inte anger nÂgra argument visas alla tillg‰ngliga kommandon.\nOm du anger ett argument visas hj‰lp fˆr det specifika kommandot."},
	/* tr */ {IDGS_MON_HELP_DESCRIPTION_TR, "Eer hiÁ arg¸man verilmemi˛se, t¸m mevcut komutlar˝n listesi yazd˝r˝l˝r\nEer bir arg¸man verilmi˛se, o komuta ˆzel yard˝m bilgisi yazd˝r˝l˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_STRING,    N_("string")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_STRING_DA, "streng"},
	/* de */ {IDGS_STRING_DE, "String"},
	/* es */ {IDGS_STRING_ES, "cadena"},
	/* fr */ {IDGS_STRING_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_STRING_HU, ""},  /* fuzzy */
	/* it */ {IDGS_STRING_IT, "stringa"},
	/* ko */ {IDGS_STRING_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_STRING_NL, "string"},
	/* pl */ {IDGS_STRING_PL, "string"},
	/* ru */ {IDGS_STRING_RU, "string"},
	/* sv */ {IDGS_STRING_SV, "str‰ng"},
	/* tr */ {IDGS_STRING_TR, "yaz˝"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_KEYBUF_DESCRIPTION,    N_("Put the specified string into the keyboard buffer.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_KEYBUF_DESCRIPTION_DA, "IndsÊt den angivne streng i tastatur-bufferen."},
	/* de */ {IDGS_MON_KEYBUF_DESCRIPTION_DE, "Definierte Eingabe in Tastaturpuffer bereitstellen."},
	/* es */ {IDGS_MON_KEYBUF_DESCRIPTION_ES, "Introduce la cadena indicada en el bufer de teclado."},
	/* fr */ {IDGS_MON_KEYBUF_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_KEYBUF_DESCRIPTION_HU, "A megadott sztring elhelyezÈse a billenty˚zet pufferben."},
	/* it */ {IDGS_MON_KEYBUF_DESCRIPTION_IT, "Metti la stringa specificata nel buffer di tastiera."},
	/* ko */ {IDGS_MON_KEYBUF_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_KEYBUF_DESCRIPTION_NL, "Plaats de opgegeven string in de toetsenbordbuffer."},
	/* pl */ {IDGS_MON_KEYBUF_DESCRIPTION_PL, "Umie∂Ê dany ci±g znakÛw w buforze klawiatury"},
	/* ru */ {IDGS_MON_KEYBUF_DESCRIPTION_RU, "Put the specified string into the keyboard buffer."},
	/* sv */ {IDGS_MON_KEYBUF_DESCRIPTION_SV, "L‰gg den angivna str‰ngen i tangentbordsbufferten."},
	/* tr */ {IDGS_MON_KEYBUF_DESCRIPTION_TR, "Klavye arabelleine belirtilen yaz˝y˝ koy."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_PLAYBACK_DESCRIPTION,    N_("Monitor commands from the specified file are read and executed.  This\ncommand stops at the end of file or when a STOP command is read.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_PLAYBACK_DESCRIPTION_DA, "Monitorkommandoer indlÊses fra den angivne fil og udf¯res. Kommandoen\nstopper nÂr slutningen af filen nÂs, eller nÂr der opdages en STOP-kommando."},
	/* de */ {IDGS_MON_PLAYBACK_DESCRIPTION_DE, "Monitor Kommandos aus der angegebenen Datei werden gelesen und ausgef¸hrt.\nDieses Kommando stoppt, wenn das Ende der Datei erreicht wurde, oder das\nKommando STOP gelesen wurde."},
	/* es */ {IDGS_MON_PLAYBACK_DESCRIPTION_ES, "Los comandos de monitor incluidos en el fichero indicado, han sido leidos y ejecutados\nEstos comandos se detendr·n al finalizar el fichero o cuando se lea un comando STOP."},
	/* fr */ {IDGS_MON_PLAYBACK_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_PLAYBACK_DESCRIPTION_HU, "A monitor parancsokat beolvassa Ès vÈgrehajtja a megadott f·jlbÛl.\nA f·jl vÈgÈig halad, vagy egy beolvasott STOP parancsig."},
	/* it */ {IDGS_MON_PLAYBACK_DESCRIPTION_IT, "I comandi del monitor sono letti ed eseguiti dal file specificato. Questo\ncomando si arresta alla fine del file o quando viene letto il comando\nSTOP."},
	/* ko */ {IDGS_MON_PLAYBACK_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_PLAYBACK_DESCRIPTION_NL, "Monitor commandos van het opgegeven bestand zullen worden gelezen en\nuitgevoerd. Dit commando stopt aan het einde van het bestand of wanneer\neen STOP commando wordt gelezen."},
	/* pl */ {IDGS_MON_PLAYBACK_DESCRIPTION_PL, "Polecenia monitora z podanego pliku s± odczytywane i wykonywane.\nTa komenda zatrzymuje siÍ na koÒcu pliku, b±dº przy odczycie komendy STOP."},
	/* ru */ {IDGS_MON_PLAYBACK_DESCRIPTION_RU, "Monitor commands from the specified file are read and executed.  This\ncommand stops at the end of file or when a STOP command is read."},
	/* sv */ {IDGS_MON_PLAYBACK_DESCRIPTION_SV, "Monitorkommandon l‰ses in och kˆrs frÂn den angivna filen. Kommandot\nstoppar vid filslut eller n‰r ett STOP-kommando l‰ses."},
	/* tr */ {IDGS_MON_PLAYBACK_DESCRIPTION_TR, "Belirtilen dosyadaki monitˆr komutlar˝ okundu ve Áal˝˛t˝r˝ld˝.  Bu\nkomut dosya sonunda ya da STOP komutu okunduunda sonlan˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_EXPRESSION,    N_("expression")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_EXPRESSION_DA, "udtryk"},
	/* de */ {IDGS_EXPRESSION_DE, "Ausdruck"},
	/* es */ {IDGS_EXPRESSION_ES, "expresiÛn"},
	/* fr */ {IDGS_EXPRESSION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_EXPRESSION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_EXPRESSION_IT, "espressione"},
	/* ko */ {IDGS_EXPRESSION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_EXPRESSION_NL, "expressie"},
	/* pl */ {IDGS_EXPRESSION_PL, "expression"},
	/* ru */ {IDGS_EXPRESSION_RU, "expression"},
	/* sv */ {IDGS_EXPRESSION_SV, "uttryck"},
	/* tr */ {IDGS_EXPRESSION_TR, "ifade"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_PRINT_DESCRIPTION,    N_("Evaluate the specified expression and output the result.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_PRINT_DESCRIPTION_DA, "EvaluÈr det angivne udtryk og vis resultatet."},
	/* de */ {IDGS_MON_PRINT_DESCRIPTION_DE, "Evaluiere den angegebenen Ausdruck und zeige das Ergebnis."},
	/* es */ {IDGS_MON_PRINT_DESCRIPTION_ES, "Evaluar la expresiÛn y mostrar los resultados."},
	/* fr */ {IDGS_MON_PRINT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_PRINT_DESCRIPTION_HU, "KiÈrtÈkeli a megadott kifejezÈst Ès kiÌrja az eredmÈnyt."},
	/* it */ {IDGS_MON_PRINT_DESCRIPTION_IT, "Calcola l'espressione specificata e mostra il risultato."},
	/* ko */ {IDGS_MON_PRINT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_PRINT_DESCRIPTION_NL, "Evalueer de opgegeven expressie en toon het resultaat."},
	/* pl */ {IDGS_MON_PRINT_DESCRIPTION_PL, "Oszacuj okre∂lone wyraøenie i podaj rezultat."},
	/* ru */ {IDGS_MON_PRINT_DESCRIPTION_RU, "Evaluate the specified expression and output the result."},
	/* sv */ {IDGS_MON_PRINT_DESCRIPTION_SV, "Utv‰rdera det angivna uttrycket och visa resultatet."},
	/* tr */ {IDGS_MON_PRINT_DESCRIPTION_TR, "Belirtilen ifadeyi deerlendir ve sonucun Á˝kt˝s˝n˝ ver."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_RECORD_DESCRIPTION,    N_("After this command, all commands entered are written to the specified\nfile until the STOP command is entered.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_RECORD_DESCRIPTION_DA, "Efter denne kommando skrives alle kommandoer til den angivne fil,\nindtil der angives en STOP-kommando."},
	/* de */ {IDGS_MON_RECORD_DESCRIPTION_DE, "Nach diesem Kommando werden alle eingebenen Kommands in die angegebene\nDatei gespeicher solang bis das Kommando STOP eingegeben wurde."},
	/* es */ {IDGS_MON_RECORD_DESCRIPTION_ES, "Despues de este comando, todos los posteriomente introducidos se grabaran\nen el fichero indicado hasta que se entre el comando STOP."},
	/* fr */ {IDGS_MON_RECORD_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_RECORD_DESCRIPTION_HU, "Ezut·n a parancs ut·n az ˆsszes parancsot a megadott f·jlba\nÌrja, amÌg STOP parancs nem Èrkezik."},
	/* it */ {IDGS_MON_RECORD_DESCRIPTION_IT, "Dopo questo comando, tutti i comandi inseriti saranno scritti sul file\nspecificato fino a quando verr‡ inserito il comando STOP."},
	/* ko */ {IDGS_MON_RECORD_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_RECORD_DESCRIPTION_NL, "Na dit commando zullen alle opgegeven commandos worden geschreven naar\nhet opgegeven bestand totdat het STOP command wordt opgegeven."},
	/* pl */ {IDGS_MON_RECORD_DESCRIPTION_PL, "Po tym poleceniu wszystkie wprowadzone polecenia s± zapisywane\ndo podanego pliku, pÛki nie zostanie wprowadzone polecenie STOP."},
	/* ru */ {IDGS_MON_RECORD_DESCRIPTION_RU, "After this command, all commands entered are written to the specified\nfile until the STOP command is entered."},
	/* sv */ {IDGS_MON_RECORD_DESCRIPTION_SV, "Efter detta kommando kommer alla kommandon som anges att skrivas till\nden angivna filen tills ett STOP-kommando anges."},
	/* tr */ {IDGS_MON_RECORD_DESCRIPTION_TR, "Bu komuttan sonra, t¸m girilen komutlar ve STOP komutunu gˆrene dek\nbelirtilen dosyaya yaz˝lacakt˝r."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_RESOURCE,    N_("resource")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_RESOURCE_DA, "resource"},
	/* de */ {IDGS_RESOURCE_DE, "Ressource"},
	/* es */ {IDGS_RESOURCE_ES, "fuente"},
	/* fr */ {IDGS_RESOURCE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_RESOURCE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_RESOURCE_IT, "risorsa"},
	/* ko */ {IDGS_RESOURCE_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_RESOURCE_NL, "bron"},
	/* pl */ {IDGS_RESOURCE_PL, "resource"},
	/* ru */ {IDGS_RESOURCE_RU, "resource"},
	/* sv */ {IDGS_RESOURCE_SV, "resurs"},
	/* tr */ {IDGS_RESOURCE_TR, "kaynak"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_RESOURCEGET_DESCRIPTION,    N_("Displays the value of the resource.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_RESOURCEGET_DESCRIPTION_DA, "Viser vÊrdien for ressourcen."},
	/* de */ {IDGS_MON_RESOURCEGET_DESCRIPTION_DE, "Zeige den Werde der Ressource."},
	/* es */ {IDGS_MON_RESOURCEGET_DESCRIPTION_ES, "Mostrar el valor del recurso"},
	/* fr */ {IDGS_MON_RESOURCEGET_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_RESOURCEGET_DESCRIPTION_HU, "Az erıforr·s ÈrtÈkÈnek kiÌr·sa."},
	/* it */ {IDGS_MON_RESOURCEGET_DESCRIPTION_IT, "Mostra il valore della risorsa."},
	/* ko */ {IDGS_MON_RESOURCEGET_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_RESOURCEGET_DESCRIPTION_NL, "Toont de waarde van de resource."},
	/* pl */ {IDGS_MON_RESOURCEGET_DESCRIPTION_PL, "Pokazuje warto∂Ê zasobu"},
	/* ru */ {IDGS_MON_RESOURCEGET_DESCRIPTION_RU, "Displays the value of the resource."},
	/* sv */ {IDGS_MON_RESOURCEGET_DESCRIPTION_SV, "Visar v‰rdet fˆr resursen."},
	/* tr */ {IDGS_MON_RESOURCEGET_DESCRIPTION_TR, "Kayna˝n deerini gˆr¸nt¸ler."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_VALUE,    N_("value")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_VALUE_DA, "vÊrdi"},
	/* de */ {IDGS_VALUE_DE, "Wert"},
	/* es */ {IDGS_VALUE_ES, "valor"},
	/* fr */ {IDGS_VALUE_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_VALUE_HU, ""},  /* fuzzy */
	/* it */ {IDGS_VALUE_IT, "valore"},
	/* ko */ {IDGS_VALUE_KO, "∞°ƒ°"},
	/* nl */ {IDGS_VALUE_NL, "waarde"},
	/* pl */ {IDGS_VALUE_PL, "warto∂Ê"},
	/* ru */ {IDGS_VALUE_RU, "value"},
	/* sv */ {IDGS_VALUE_SV, "v‰rde"},
	/* tr */ {IDGS_VALUE_TR, "deer"},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_RESOURCESET_DESCRIPTION,    N_("Sets the value of the resource.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_RESOURCESET_DESCRIPTION_DA, "SÊtter vÊrdien for ressourcen."},
	/* de */ {IDGS_MON_RESOURCESET_DESCRIPTION_DE, "Setze den Werde der Ressource."},
	/* es */ {IDGS_MON_RESOURCESET_DESCRIPTION_ES, "Seleccionar el valor de los recursos"},
	/* fr */ {IDGS_MON_RESOURCESET_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_RESOURCESET_DESCRIPTION_HU, "Az erıforr·s ÈrtÈkÈnek be·llÌt·sa."},
	/* it */ {IDGS_MON_RESOURCESET_DESCRIPTION_IT, "Imposta il valore della risorsa."},
	/* ko */ {IDGS_MON_RESOURCESET_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_RESOURCESET_DESCRIPTION_NL, "Plaats de waarde in de resource."},
	/* pl */ {IDGS_MON_RESOURCESET_DESCRIPTION_PL, "Ustawia warto∂Ê zasobu."},
	/* ru */ {IDGS_MON_RESOURCESET_DESCRIPTION_RU, "Sets the value of the resource."},
	/* sv */ {IDGS_MON_RESOURCESET_DESCRIPTION_SV, "St‰ller in ett v‰rde fˆr resursen."},
	/* tr */ {IDGS_MON_RESOURCESET_DESCRIPTION_TR, "Kayna˝n deerini belirler."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION,    N_("Loads resources from file.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_DA, "IndlÊs indstillinger fra fil."},
	/* de */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_DE, "Einstellungen aus Datei laden"},
	/* es */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_ES, "Cargar recursos desde fichero."},
	/* fr */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_IT, "Carica le risorse da file."},
	/* ko */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_NL, "Laad instellingen van bestand"},
	/* pl */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_PL, "Wczytaj zasoby z pliku."},
	/* ru */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_RU, ""},  /* fuzzy */
	/* sv */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_SV, "L‰ser in resurser frÂn fil."},
	/* tr */ {IDGS_MON_LOAD_RESOURCES_DESCRIPTION_TR, "Kaynaklar˝ dosyadan y¸kler."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION,    N_("Saves resources to file.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_DA, "Gem indstillinger til fil."},
	/* de */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_DE, "Einstellungen speichern unter"},
	/* es */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_ES, "Grabar recursos a fichero."},
	/* fr */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_HU, ""},  /* fuzzy */
	/* it */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_IT, "Salva le risorse su file."},
	/* ko */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_NL, "Sla instellingen op naar bestand"},
	/* pl */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_PL, "Zapisz zasoby do pliku."},
	/* ru */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_RU, ""},  /* fuzzy */
	/* sv */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_SV, "Sparar resurser till fil."},
	/* tr */ {IDGS_MON_SAVE_RESOURCES_DESCRIPTION_TR, "Kaynaklar˝ dosyaya kaydeder."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_STOP_DESCRIPTION,    N_("Stop recording commands.  See `record'.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_STOP_DESCRIPTION_DA, "Afslut optagelse. Se \"record\"."},
	/* de */ {IDGS_MON_STOP_DESCRIPTION_DE, "Stoppe die Aufnahme von Kommandos. Siehe auch `Record'."},
	/* es */ {IDGS_MON_STOP_DESCRIPTION_ES, "Detener comando de grabaciÛn. Ver 'grabaciÛn'"},
	/* fr */ {IDGS_MON_STOP_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_STOP_DESCRIPTION_HU, "A parancsok rˆgzÌtÈsÈnek befejezÈse.  L·sd `record'"},
	/* it */ {IDGS_MON_STOP_DESCRIPTION_IT, "Ferma il comando di registrazione. Guarda `registra'."},
	/* ko */ {IDGS_MON_STOP_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_STOP_DESCRIPTION_NL, "Stop de opname van commandos. Zie 'record'."},
	/* pl */ {IDGS_MON_STOP_DESCRIPTION_PL, "PrzestaÒ zapisywaÊ polecenia. Zobacz `record'."},
	/* ru */ {IDGS_MON_STOP_DESCRIPTION_RU, "Stop recording commands.  See `record'."},
	/* sv */ {IDGS_MON_STOP_DESCRIPTION_SV, "Sluta spela in kommandon. Se \"record\"."},
	/* tr */ {IDGS_MON_STOP_DESCRIPTION_TR, "Kay˝t komutlar˝n˝ durdur.  `record'a bak."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_SCREENSHOT_DESCRIPTION,    N_("Take a screenshot. Format is:\ndefault = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_SCREENSHOT_DESCRIPTION_DA, "Gem et screenshot. Format er:\nstandard = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* de */ {IDGS_MON_SCREENSHOT_DESCRIPTION_DE, "Erzeuge Screenshot. Format ist:\nStandard = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* es */ {IDGS_MON_SCREENSHOT_DESCRIPTION_ES, "Tomar Captura de pantalla. El formato es:\npor defecto = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* fr */ {IDGS_MON_SCREENSHOT_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_SCREENSHOT_DESCRIPTION_HU, "KÈpernyıkÈp kÈszÌtÈse. A form·tum lehet:\nalap = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* it */ {IDGS_MON_SCREENSHOT_DESCRIPTION_IT, "Cattura schermo. Il formato Ë:\npredefinito = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* ko */ {IDGS_MON_SCREENSHOT_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_SCREENSHOT_DESCRIPTION_NL, "Sla een schermafdruk op. Formaat is:\nstandaard = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* pl */ {IDGS_MON_SCREENSHOT_DESCRIPTION_PL, "ZrÛb zrzut ekranu. Format:\ndomy∂lny = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* ru */ {IDGS_MON_SCREENSHOT_DESCRIPTION_RU, "Take a screenshot. Format is:\ndefault = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* sv */ {IDGS_MON_SCREENSHOT_DESCRIPTION_SV, "Ta en sk‰rmbild. Format ‰r:\nstandard = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
	/* tr */ {IDGS_MON_SCREENSHOT_DESCRIPTION_TR, "Ekran gˆr¸nt¸s¸ al. BiÁim:\nvarsay˝lan = BMP, 1 = PCX, 2 = PNG, 3 = GIF, 4 = IFF."},
#endif
	
	/* monitor/mon_command.c */
	/* en */ {IDGS_MON_TAPECTRL_DESCRIPTION,    N_("Control the datasette. Valid commands:\n0 = stop, 1 = start, 2 = forward, 3 = rewind, 4 = record,\n5 = reset, 6 = reset counter.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDGS_MON_TAPECTRL_DESCRIPTION_DA, "Styr datasette. Lovlige kommandoer:\n0 = stop, 1 = start, 2 = spol frem, 3 = spol tilbage,\n4 = optag, 5 = reset, 6 = nulstil tÊller."},
	/* de */ {IDGS_MON_TAPECTRL_DESCRIPTION_DE, "Steuere die Datasette. G¸ltige Kommandos sind:\n0 = Stop, 1 = Start, 2 = Forw‰rts, 3 = R¸ckw‰rts, 4 = Aufnahme,\n5 = Reset, 6 = Reset Z‰hler."},
	/* es */ {IDGS_MON_TAPECTRL_DESCRIPTION_ES, "Control unidad cinta, comandos validos:\n0 = alto, 1 = inicio, 2 = avance, 3 = rebobinar, 4 = grabar,\n5 = reinicio, 6 = reiniciar contador."},
	/* fr */ {IDGS_MON_TAPECTRL_DESCRIPTION_FR, ""},  /* fuzzy */
	/* hu */ {IDGS_MON_TAPECTRL_DESCRIPTION_HU, "Szalagos egysÈg vezÈrlÈse. …rvÈnyes parancsok:\n0 = start, 1 = indÌt, 2 = elıre, 3 = vissza, 4 = felvÈtel,\n5 = ˙jraindÌt, 6 = sz·ml·lÛt null·z"},
	/* it */ {IDGS_MON_TAPECTRL_DESCRIPTION_IT, "Controlla il registratore. Comandi validi:\n0 = ferma, 1 = avvia, 2 = avanti, 3 = indietro, 4 = registra,\n5 = reset, 6 = reset contatore."},
	/* ko */ {IDGS_MON_TAPECTRL_DESCRIPTION_KO, ""},  /* fuzzy */
	/* nl */ {IDGS_MON_TAPECTRL_DESCRIPTION_NL, "Geef datasette commandos. Geldige commandos:\n0 = stop, 1 = start, 2 = vooruit, 3 = terug, 4 = opnemen,\n5 = reset, 6 = reset teller."},
	/* pl */ {IDGS_MON_TAPECTRL_DESCRIPTION_PL, "Kontrola magnetofonu. W≥a∂ciwe polecenia:\n0 = stop, 1 = start, 2 = naprzÛd, 3 = przewiÒ, 4 = nagrywaj,\n5 = reset, 6 = reset licznika."},
	/* ru */ {IDGS_MON_TAPECTRL_DESCRIPTION_RU, "Control the datasette. Valid commands:\n0 = stop, 1 = start, 2 = forward, 3 = rewind, 4 = record,\n5 = reset, 6 = reset counter."},
	/* sv */ {IDGS_MON_TAPECTRL_DESCRIPTION_SV, "Styr bandspelaren. Giltiga kommandon:\n0 = stoppa, 1 = starta, 2 = spola framÂt, 3 = spola bakÂt,\n4 = spela in, 5 = Âterst‰ll, 6 = nollst‰ll r‰knare."},
	/* tr */ {IDGS_MON_TAPECTRL_DESCRIPTION_TR, "Teybi kontrol et. GeÁerli komutlar:\n0 = durdur, 1 = ba˛lat, 2 = ileri, 3 = geri, 4 = kay˝t,\n5 = reset, 6 = reset sayac˝."},
#endif
	
	/* ------------------------ COMMAND LINE OPTION STRINGS -------------------- */
	
	/* autostart.c */
	/* en */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START,    N_("On autostart, load to BASIC start (without ',1')")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_DA, "IndlÊs til BASIC start ved autostart (uden ',1')"},
	/* de */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_DE, "Bei Autostart, lade an BASIC Start (ohne ',1')"},
	/* es */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_ES, "En autoarranque, carga en inicio del BASIC (sin ',1')"},
	/* fr */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_IT, "All'avvio automatico, carica all'inizio del BASIC (senza ',1')"},
	/* ko */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_NL, "Bij autostarten, laad naar BASIC start (zonder ',1')"},
	/* pl */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_PL, "Przy autostarcie wczytuj do BASIC-a (bez ',1')"},
	/* ru */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_RU, "On autostart, load to BASIC start (without ',1')"},
	/* sv */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_SV, "Vid autostart, h‰mta till BASIC-start (utan \",1\")"},
	/* tr */ {IDCLS_AUTOSTART_LOAD_TO_BASIC_START_TR, "Otomatik ba˛lat˝ld˝˝nda, BASIC ba˛lang˝c˝na y¸kle (',1' olmadan)"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_AUTOSTART_LOAD_WITH_1,    N_("On autostart, load with ',1'")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_AUTOSTART_LOAD_WITH_1_DA, "IndlÊs med ',1' ved autostart"},
	/* de */ {IDCLS_AUTOSTART_LOAD_WITH_1_DE, "Bei Autostart, lade mit ',1'"},
	/* es */ {IDCLS_AUTOSTART_LOAD_WITH_1_ES, "En autoarranque, carga con ',1'"},
	/* fr */ {IDCLS_AUTOSTART_LOAD_WITH_1_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_AUTOSTART_LOAD_WITH_1_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_AUTOSTART_LOAD_WITH_1_IT, "All'avvio automatico, carica con ',1'"},
	/* ko */ {IDCLS_AUTOSTART_LOAD_WITH_1_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_AUTOSTART_LOAD_WITH_1_NL, "Bij autostarten, laad met ',1'"},
	/* pl */ {IDCLS_AUTOSTART_LOAD_WITH_1_PL, "Przy autostarcie wczytuj z ',1'"},
	/* ru */ {IDCLS_AUTOSTART_LOAD_WITH_1_RU, "On autostart, load with ',1'"},
	/* sv */ {IDCLS_AUTOSTART_LOAD_WITH_1_SV, "Vid autostart, h‰mta med \",1\""},
	/* tr */ {IDCLS_AUTOSTART_LOAD_WITH_1_TR, "Otomatik ba˛lat˝ld˝˝nda, ',1' ile y¸kle"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON,    N_("On autostart, use the 'RUN' command with a colon, i.e., 'RUN:'")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_DA, "Brug \"RUN\"-kommando med kolon ved autostart, dvs. \"RUN:\""},
	/* de */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_DE, "Bei Autostart soll 'RUN' mit Doppelpunkt ausgef¸hrt werden ('RUN:')"},
	/* es */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_ES, "En autoarranque, usa el comando 'RUN' con dos puntos, ejm. 'RUN:'"},
	/* fr */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_HU, "Automatikus indÌt·sn·l a 'RUN' parancs kettısponttal, vagyis 'RUN:'"},
	/* it */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_IT, "All'avvio automatico, usa il comando 'RUN' con i due punti; cioË 'RUN:'"},
	/* ko */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_NL, "Bij het autostarten, gebruik het 'RUN' commando met een dubbele punt, dus 'RUN:'"},
	/* pl */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_PL, "Przy autostarcie uøywaj polecenia 'RUN' z dwukropkiem, tj. 'RUN:'"},
	/* ru */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_RU, "On autostart, use the 'RUN' command with a colon, i.e., 'RUN:'"},
	/* sv */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_SV, "Vid autostart, anv‰nd \"RUN\"-kommando med kolon, dvs. \"RUN:\""},
	/* tr */ {IDCLS_ENABLE_AUTOSTARTWITHCOLON_TR, "Otomatik ba˛lat˝ld˝˝nda, 'RUN' komutunu ':' ile kullan, yani, 'RUN:'"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON,    N_("On autostart, do not use the 'RUN' command with a colon; i.e., 'RUN'")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_DA, "Brug ikke \"RUN\"-kommando med kolon ved autostart, dvs. \"RUN\""},
	/* de */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_DE, "Bei Autostart soll 'RUN' ohne Doppelpunkt ausgef¸hrt werden ('RUN')"},
	/* es */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_ES, "En autoarranque, no usar el comando 'RUN' con dos puntos, ejm.'RUN'"},
	/* fr */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_HU, "Automatikus indÌt·snak a 'RUN' parancs kettıspont nÈlk¸l, vagyis 'RUN'"},
	/* it */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_IT, "All'avvio automatico, non usare il comando 'RUN' con i due punti; cioË 'RUN'"},
	/* ko */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_NL, "Bij het autostarten, gebruik het 'RUN' commando niet met een dubbele punt, dus 'RUN'"},
	/* pl */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_PL, "Przy autostarcie uøywaj polecenia 'RUN' bez dwukropka, tj. 'RUN'"},
	/* ru */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_RU, "On autostart, do not use the 'RUN' command with a colon; i.e., 'RUN'"},
	/* sv */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_SV, "Vid autostart, anv‰nd inte \"RUN\"-kommando med kolon, dvs. \"RUN\""},
	/* tr */ {IDCLS_DISABLE_AUTOSTARTWITHCOLON_TR, "Otomatik ba˛lat˝ld˝˝nda, 'RUN' komutunu ':' ile kullanma, yani, 'RUN'"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE,    N_("Handle True Drive Emulation on autostart")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_DA, "Anvend Êgte drev-emulering ved autostart"},
	/* de */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_DE, "Pr‰zise Floppy Emulation bei Autostart beachten"},
	/* es */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_ES, "Manejar en autoarranque emulaciÛn de disco verdadera"},
	/* fr */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_HU, "ValÛs lemezegysÈg emul·ciÛ kezelÈse autostartn·l"},
	/* it */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_IT, "Emulazione hardware dei drive all'avvio automatico"},
	/* ko */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_NL, "Manipuleer hardwarematige drive emulatie bij autostarten"},
	/* pl */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_PL, "W≥±cz rzeczywist± emulacjÍ napÍdu przy autostarcie"},
	/* ru */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_RU, "Handle True Drive Emulation on autostart"},
	/* sv */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_SV, "Hantera ‰kta diskettenhetsemulering vid autostart"},
	/* tr */ {IDCLS_ENABLE_AUTOSTART_HANDLE_TDE_TR, "Otomatik ba˛latmada GerÁek S¸r¸c¸ Em¸lasyonu'nu denetle"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE,    N_("Do not handle True Drive Emulation on autostart")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_DA, "Anvend ikke Êgte drev-emulering ved autostart"},
	/* de */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_DE, "Pr‰zise Floppy Emulation bei Autostart nicht beachten"},
	/* es */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_ES, "No manejar en autoarranque emulaciÛn de disco verdadera"},
	/* fr */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_HU, "ValÛs lemezegysÈg emul·ciÛt nem kezeli autostartn·l"},
	/* it */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_IT, "Non gestire l'emulazione hardware dei drive all'avvio automatico"},
	/* ko */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_NL, "Geen manipulatie van de hardwarematige drive emulatie bij autostarten"},
	/* pl */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_PL, "Nie w≥±czaj rzeczywistej emulacji napÍdu przy autostarcie"},
	/* ru */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_RU, "Do not handle True Drive Emulation on autostart"},
	/* sv */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_SV, "Hantera inte ‰kta diskettenhetsemulering vid autostart"},
	/* tr */ {IDCLS_DISABLE_AUTOSTART_HANDLE_TDE_TR, "Ba˛lang˝Áta GerÁek S¸r¸c¸ Em¸lasyonu'nu Denetleme"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART,    N_("Enable warp mode during autostart")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_DA, "AktivÈr warp-tilstand under autostart"},
	/* de */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_DE, "Warp Mode w‰hrend Autostart aktivieren"},
	/* es */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_ES, "Permitir modo ultrar·pido durante autoarranque"},
	/* fr */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_HU, "Hipergyors mÛd engedÈlyezÈse autostartn·l"},
	/* it */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_IT, "Attiva la modalit‡ turbo all'avvio automatico"},
	/* ko */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_NL, "Activeer warp modus tijdens autostarten"},
	/* pl */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_PL, "W≥±cz tryb przy∂pieszony podczas automatycznego startu"},
	/* ru */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_RU, "Enable warp mode during autostart"},
	/* sv */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_SV, "Aktivera warpl‰ge fˆr autostart"},
	/* tr */ {IDCLS_ENABLE_WARP_MODE_AUTOSTART_TR, "Otomatik ba˛latma esnas˝nda warp modu aktif et"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART,    N_("Disable warp mode during autostart")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_DA, "DeaktivÈr warp-tilstand under autostart"},
	/* de */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_DE, "Warp Mode w‰hren Autostart deaktivieren"},
	/* es */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_ES, "Deshabilitar modo ultrar·pido durante autoarranque"},
	/* fr */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_HU, "Hipergyors mÛd tilt·sa autostartn·l"},
	/* it */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_IT, "Disattiva la modalit‡ turbo all'avvio automatico"},
	/* ko */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_NL, "Warp modus tijdens autostarten uitschakelen"},
	/* pl */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_PL, "Wy≥±cz tryb przy∂pieszony podczas automatycznego startu"},
	/* ru */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_RU, "Disable warp mode during autostart"},
	/* sv */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_SV, "Inaktivera warpl‰ge fˆr autostart"},
	/* tr */ {IDCLS_DISABLE_WARP_MODE_AUTOSTART_TR, "Otomatik ba˛latma esnas˝nda warp modu pasifle˛tir"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG,    N_("Set autostart mode for PRG files")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_DA, "VÊlg autostart-tilstand for PRG-filer"},
	/* de */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_DE, "Autstart Modus f¸r PRG Dateien definieren"},
	/* es */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_ES, "Seleccionar modo autoarranque para ficheros PRG"},
	/* fr */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_HU, "Automatikus indÌt·s mÛdja PRG f·jlokn·l"},
	/* it */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_IT, "Imposta avvio automatico per i file PRG"},
	/* ko */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_NL, "Zet autostart modus voor PRG bestanden"},
	/* pl */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_PL, "Okre∂l tryb autostartu z plikÛw PRG"},
	/* ru */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_RU, "Set autostart mode for PRG files"},
	/* sv */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_SV, "V‰lj autostartl‰ge fˆr PRG-filer"},
	/* tr */ {IDCLS_SET_AUTOSTART_MODE_FOR_PRG_TR, "PRG dosyalar˝ iÁin otomatik ba˛latma ayarla"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG,    N_("Set disk image for autostart of PRG files")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_DA, "VÊlg diskimage for autostart af PRG-filer"},
	/* de */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_DE, "Disk Imagedatei f¸r Autstart definieren"},
	/* es */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_ES, "Seleccionar imagen disco para autoarranque ficheros PRG"},
	/* fr */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_HU, "Lmeez kÈpm·s megad·sa PRG automatikus indÌt·shoz"},
	/* it */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_IT, "Imposta immagine disco per l'avvio automatico dei file PRG"},
	/* ko */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_NL, "Zet disk bestand voor het autostarten van PRG bestanden"},
	/* pl */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_PL, "Okre∂l obraz dysku do autostartu z plikÛw PRG"},
	/* ru */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_RU, "Set disk image for autostart of PRG files"},
	/* sv */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_SV, "Ange diskavbildning fˆr autostart av PRG-filer"},
	/* tr */ {IDCLS_SET_DISK_IMAGE_FOR_AUTOSTART_PRG_TR, "PRG dosyalar˝n˝n otomatik ba˛lat˝lmas˝ iÁin disk imaj˝ ayarla"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_SET_AUTOSTART_DELAY,    N_("Set initial autostart delay (0: use default)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_AUTOSTART_DELAY_DA, "Angiv autostart-forsinkelse (0: brug standard)"},
	/* de */ {IDCLS_SET_AUTOSTART_DELAY_DE, "Setze initiale Autostart Verzˆgerung (0: benutze Standard)"},
	/* es */ {IDCLS_SET_AUTOSTART_DELAY_ES, "Seleccionar retardo inicial autoarranque (Por defecto 0)"},
	/* fr */ {IDCLS_SET_AUTOSTART_DELAY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_AUTOSTART_DELAY_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_AUTOSTART_DELAY_IT, "Imposta ritardo iniziale all'avvio automatico (0: usa predefinito)"},
	/* ko */ {IDCLS_SET_AUTOSTART_DELAY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_AUTOSTART_DELAY_NL, "Zet de vertraging bij begin van het autostarten (0: gebruik de standaard waarde)"},
	/* pl */ {IDCLS_SET_AUTOSTART_DELAY_PL, "Okre∂l pocz±tkowe opÛºnienie autostartu (0: domy∂lne)"},
	/* ru */ {IDCLS_SET_AUTOSTART_DELAY_RU, "Set initial autostart delay (0: use default)"},
	/* sv */ {IDCLS_SET_AUTOSTART_DELAY_SV, "Ange inledande fˆrdrˆjning fˆr autostart (0: anv‰nd standard)"},
	/* tr */ {IDCLS_SET_AUTOSTART_DELAY_TR, "Otomatik ba˛latmada rastgele gecikmeyi ayarla (0: varsay˝lan˝ kullan)"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY,    N_("Enable random initial autostart delay.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_DA, "AktivÈr tilfÊldig autostart-forsinkelse"},
	/* de */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_DE, "Zuf‰lle Verzˆgerung w‰hrend Autostart aktivieren,"},
	/* es */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_ES, "Permitir retardo arranque inicial aleatorio."},
	/* fr */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_IT, "Attiva ritardo casuale all'avvio automatico"},
	/* ko */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_NL, "Activeer willekeurige vertraging bij begin van het autostarten."},
	/* pl */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_PL, "W≥±cz losowe opÛºnienie na pocz±tku autostartu."},
	/* ru */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_RU, "Enable random initial autostart delay."},
	/* sv */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_SV, "Aktivera slumpm‰ssig inledande autostartfˆrdrˆjning"},
	/* tr */ {IDCLS_ENABLE_AUTOSTART_RANDOM_DELAY_TR, "Otomatik ba˛latmada rastgele gecikmeyi aktif et"},
#endif
	
	/* autostart.c */
	/* en */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY,    N_("Disable random initial autostart delay.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_DA, "DeaktivÈr tilfÊldig autostart-forsinkelse"},
	/* de */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_DE, "Zuf‰lle Verzˆgerung w‰hrend Autostart deaktivieren."},
	/* es */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_ES, "Deshabilitar retardo arranque inicial aleatorio."},
	/* fr */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_IT, "Disattiva ritardo casuale all'avvio automatico"},
	/* ko */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_NL, "Willekeurige vertraging bij begin van het uitostarten uitschakelen."},
	/* pl */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_PL, "Wy≥±cz losowe opÛºnienie na pocz±tku autostartu."},
	/* ru */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_RU, "Disable random initial autostart delay."},
	/* sv */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_SV, "Inaktivera slumpm‰ssig inledande autostartfˆrdrˆjning"},
	/* tr */ {IDCLS_DISABLE_AUTOSTART_RANDOM_DELAY_TR, "Otomatik ba˛latmada rastgele gecikmeyi pasifle˛tir"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c,
	 c64/psid.c, plus4/plus4-cmdline-options.c,
	 vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_USE_PAL_SYNC_FACTOR,    N_("Use PAL sync factor")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_PAL_SYNC_FACTOR_DA, "Anvend PAL-synkfaktor"},
	/* de */ {IDCLS_USE_PAL_SYNC_FACTOR_DE, "PAL Sync Faktor benutzen"},
	/* es */ {IDCLS_USE_PAL_SYNC_FACTOR_ES, "Usar factor sincronizaciÛn PAL"},
	/* fr */ {IDCLS_USE_PAL_SYNC_FACTOR_FR, "Utiliser PAL"},
	/* hu */ {IDCLS_USE_PAL_SYNC_FACTOR_HU, "PAL szinkron faktor haszn·lata"},
	/* it */ {IDCLS_USE_PAL_SYNC_FACTOR_IT, "Usa fattore di sincronizzazione PAL"},
	/* ko */ {IDCLS_USE_PAL_SYNC_FACTOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_PAL_SYNC_FACTOR_NL, "Gebruik PAL synchronisatiefaktor"},
	/* pl */ {IDCLS_USE_PAL_SYNC_FACTOR_PL, "Uøywaj synchronizacji PAL"},
	/* ru */ {IDCLS_USE_PAL_SYNC_FACTOR_RU, "Use PAL sync factor"},
	/* sv */ {IDCLS_USE_PAL_SYNC_FACTOR_SV, "Anv‰nd PAL-synkfaktor"},
	/* tr */ {IDCLS_USE_PAL_SYNC_FACTOR_TR, "PAL senkron faktˆr¸ kullan"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c,
	 c64/psid.c, plus4/plus4-cmdline-options.c,
	 vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_USE_NTSC_SYNC_FACTOR,    N_("Use NTSC sync factor")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_NTSC_SYNC_FACTOR_DA, "Anvend NTSC-synkfaktor"},
	/* de */ {IDCLS_USE_NTSC_SYNC_FACTOR_DE, "NTSC Sync Faktor benutzen"},
	/* es */ {IDCLS_USE_NTSC_SYNC_FACTOR_ES, "Usar factor sincronizacion NTSC"},
	/* fr */ {IDCLS_USE_NTSC_SYNC_FACTOR_FR, "Utiliser NTSC"},
	/* hu */ {IDCLS_USE_NTSC_SYNC_FACTOR_HU, "NTSC szinkron faktor haszn·lata"},
	/* it */ {IDCLS_USE_NTSC_SYNC_FACTOR_IT, "Usa fattore di sincronizzazione NTSC"},
	/* ko */ {IDCLS_USE_NTSC_SYNC_FACTOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_NTSC_SYNC_FACTOR_NL, "Gebruik NTSC synchronisatiefaktor"},
	/* pl */ {IDCLS_USE_NTSC_SYNC_FACTOR_PL, "Uøywaj synchronizacji NTSC"},
	/* ru */ {IDCLS_USE_NTSC_SYNC_FACTOR_RU, "Use NTSC sync factor"},
	/* sv */ {IDCLS_USE_NTSC_SYNC_FACTOR_SV, "Anv‰nd NTSC-synkfaktor"},
	/* tr */ {IDCLS_USE_NTSC_SYNC_FACTOR_TR, "NTSC senkron faktˆr¸ kullan"},
#endif
	
	/* c64/c64-cmdline-options.c, c64/psid.c */
	/* en */ {IDCLS_USE_PALN_SYNC_FACTOR,    N_("Use PAL-N sync factor")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_PALN_SYNC_FACTOR_DA, "Anvend PAL-N synkfaktor"},
	/* de */ {IDCLS_USE_PALN_SYNC_FACTOR_DE, "PAL Sync Faktor benutzen"},
	/* es */ {IDCLS_USE_PALN_SYNC_FACTOR_ES, "Usar factor sincronizaciÛn PAL-N"},
	/* fr */ {IDCLS_USE_PALN_SYNC_FACTOR_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_USE_PALN_SYNC_FACTOR_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_USE_PALN_SYNC_FACTOR_IT, "Usa fattore di sincronizzazione PAL-N"},
	/* ko */ {IDCLS_USE_PALN_SYNC_FACTOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_PALN_SYNC_FACTOR_NL, "Gebruik PAL-N synchronisatiefaktor"},
	/* pl */ {IDCLS_USE_PALN_SYNC_FACTOR_PL, "Uøywaj synchronizacji PAL-N"},
	/* ru */ {IDCLS_USE_PALN_SYNC_FACTOR_RU, "Use PAL-N sync factor"},
	/* sv */ {IDCLS_USE_PALN_SYNC_FACTOR_SV, "Anv‰nd PAL N-synkfaktor"},
	/* tr */ {IDCLS_USE_PALN_SYNC_FACTOR_TR, "PAL-N senkron faktˆr¸ kullan"},
#endif
	
	/* c64/c64-cmdline-options.c */
	/* en */ {IDCLS_SET_BURST_MOD,    N_("Burst modification (0 = None, 1 = CIA1, 2 = CIA2)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_BURST_MOD_DA, "Burst modification (0 = ingen, 1 = CIA1, 2 = CIA2)"},
	/* de */ {IDCLS_SET_BURST_MOD_DE, "Burst Modifikation (0 = Kein, 1 = CIA1, 2 = CIA2)"},
	/* es */ {IDCLS_SET_BURST_MOD_ES, "ModificaciÛn arranque (0=No, 1=CIA1, 2=CIA2)"},
	/* fr */ {IDCLS_SET_BURST_MOD_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_BURST_MOD_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_BURST_MOD_IT, "Burst modification (0 = Nessuna, 1 = CIA1, 2 = CIA2)"},
	/* ko */ {IDCLS_SET_BURST_MOD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_BURST_MOD_NL, "Burst modificatie (0 = Geen, 1 = CIA1, 2 = CIA2)"},
	/* pl */ {IDCLS_SET_BURST_MOD_PL, "Modyfikacja trybu synchronicznego (0 = Brak, 1 = CIA1, 2 = CIA2)"},
	/* ru */ {IDCLS_SET_BURST_MOD_RU, "Burst modification (0 = None, 1 = CIA1, 2 = CIA2)"},
	/* sv */ {IDCLS_SET_BURST_MOD_SV, "Burstmodifiering (0 = ingen, 1 = CIA1, 2 = CIA2)"},
	/* tr */ {IDCLS_SET_BURST_MOD_TR, "Burst dei˛iklii (0 = Yok, 1 = CIA1, 2 = CIA2)"},
#endif
	
	/* c128/c128-cmdline-options.c, c128/functionrom.c,
	 c64/c64-cmdline-options.c, c64/cart/georam.c,
	 c64/cart/ramcart.c, c64/cart/reu.c, c64/cart/c64cart.c,
	 c64/cart/ide64.c, cbm2/cbm2-cmdline-options.c,
	 drive/iec/iec-cmdline-options.c, drive/iec128dcr/iec128dcr-cmdline-options.c,
	 drive/ieee/ieee-cmdline-options.c, drive/tcbm/tcbm-cmdline-options.c,
	 fsdevice/fsdevice-cmdline-options.c, pet/pet-cmdline-options.c,
	 plus4/plus4-cmdline-options.c, printerdrv/driver-select.c,
	 printerdrv/output-select.c, printerdrv/output-text.c,
	 rs232drv/rs232drv.c, vic20/vic20-cmdline-options.c,
	 vic20/vic20cartridge.c, video/video-cmdline-options.c,
	 fliplist.c, initcmdline.c, log.c, sound.c, c64/plus60k.c,
	 c64/c64_256k.c, pet/petreu.c, c64/plus256k.c */
	/* en */ {IDCLS_P_NAME,    N_("<Name>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_NAME_DA, "<Navn>"},
	/* de */ {IDCLS_P_NAME_DE, "<Name>"},
	/* es */ {IDCLS_P_NAME_ES, "<Nombre>"},
	/* fr */ {IDCLS_P_NAME_FR, "<Nom>"},
	/* hu */ {IDCLS_P_NAME_HU, "<NÈv>"},
	/* it */ {IDCLS_P_NAME_IT, "<Nome>"},
	/* ko */ {IDCLS_P_NAME_KO, "<¿Ã∏ß>"},
	/* nl */ {IDCLS_P_NAME_NL, "<Naam>"},
	/* pl */ {IDCLS_P_NAME_PL, "<Nazwa>"},
	/* ru */ {IDCLS_P_NAME_RU, "<∏‹Ô>"},
	/* sv */ {IDCLS_P_NAME_SV, "<Namn>"},
	/* tr */ {IDCLS_P_NAME_TR, "<›sim>"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_INT_KERNEL_NAME,    N_("Specify name of international Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_INT_KERNEL_NAME_DA, "Angiv navn pÂ internationalt kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_INT_KERNEL_NAME_DE, "Bitte Namen f¸r internationale Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_INT_KERNEL_NAME_ES, "Especificar nombre imagen ROM Kernal internacional"},
	/* fr */ {IDCLS_SPECIFY_INT_KERNEL_NAME_FR, "SpÈcifier le nom de l'image Kernal internationale"},
	/* hu */ {IDCLS_SPECIFY_INT_KERNEL_NAME_HU, "Adja meg a nemzetkˆzi Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_INT_KERNEL_NAME_IT, "Specifica il nome immagine della ROM del Kernal internazionale"},
	/* ko */ {IDCLS_SPECIFY_INT_KERNEL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_INT_KERNEL_NAME_NL, "Geef de naam van het internationaal Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_INT_KERNEL_NAME_PL, "Okre∂l nazwÍ obrazu miÍdzynarodowego ROM-u Kernala"},
	/* ru */ {IDCLS_SPECIFY_INT_KERNEL_NAME_RU, "Specify name of international Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_INT_KERNEL_NAME_SV, "Ange namn pÂ internationell kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_INT_KERNEL_NAME_TR, "Uluslararas˝ Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_DE_KERNEL_NAME,    N_("Specify name of German Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_DE_KERNEL_NAME_DA, "Angiv navn pÂ tysk kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_DE_KERNEL_NAME_DE, "Name f¸r deutsche Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_DE_KERNEL_NAME_ES, "Especificar nombre imagen ROM Kernal alem·n"},
	/* fr */ {IDCLS_SPECIFY_DE_KERNEL_NAME_FR, "SpÈcifier le nom de l'image Kernal allemande"},
	/* hu */ {IDCLS_SPECIFY_DE_KERNEL_NAME_HU, "Adja meg a nÈmet Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_DE_KERNEL_NAME_IT, "Specifica il nome immagine della ROM del Kernal tedesca"},
	/* ko */ {IDCLS_SPECIFY_DE_KERNEL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_DE_KERNEL_NAME_NL, "Geef de naam van het Duitse Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_DE_KERNEL_NAME_PL, "Podaj nazwÍ obrazu niemieckiego ROM-u Kernala"},
	/* ru */ {IDCLS_SPECIFY_DE_KERNEL_NAME_RU, "Specify name of German Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_DE_KERNEL_NAME_SV, "Ange namn pÂ tysk kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_DE_KERNEL_NAME_TR, "Alman Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_FI_KERNEL_NAME,    N_("Specify name of Finnish Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_FI_KERNEL_NAME_DA, "Angiv navn pÂ finsk kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_FI_KERNEL_NAME_DE, "Name f¸r finnische Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_FI_KERNEL_NAME_ES, "Especificar nombre imagen ROM Kernal finlandÈs"},
	/* fr */ {IDCLS_SPECIFY_FI_KERNEL_NAME_FR, "SpÈcifier le nom de l'image Kernal finlandaise"},
	/* hu */ {IDCLS_SPECIFY_FI_KERNEL_NAME_HU, "Adja meg a finn Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_FI_KERNEL_NAME_IT, "Specifica il nome immagine della ROM del Kernal finlandese"},
	/* ko */ {IDCLS_SPECIFY_FI_KERNEL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_FI_KERNEL_NAME_NL, "Geef de naam van het Finse Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_FI_KERNEL_NAME_PL, "Okre∂l nazwÍ obrazu fiÒskiego ROM-u Kernala"},
	/* ru */ {IDCLS_SPECIFY_FI_KERNEL_NAME_RU, "Specify name of Finnish Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_FI_KERNEL_NAME_SV, "Ange namn pÂ finsk kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_FI_KERNEL_NAME_TR, "Finlandiya Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_FR_KERNEL_NAME,    N_("Specify name of French Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_FR_KERNEL_NAME_DA, "Angiv navn pÂ fransk kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_FR_KERNEL_NAME_DE, "Name f¸r franzˆsische Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_FR_KERNEL_NAME_ES, "Especificar nombre imagen ROM Kernal francÈs"},
	/* fr */ {IDCLS_SPECIFY_FR_KERNEL_NAME_FR, "SpÈcifier le nom de l'image Kernal franÁaise"},
	/* hu */ {IDCLS_SPECIFY_FR_KERNEL_NAME_HU, "Adja meg a francia Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_FR_KERNEL_NAME_IT, "Specifica il nome immagine della ROM del Kernal francese"},
	/* ko */ {IDCLS_SPECIFY_FR_KERNEL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_FR_KERNEL_NAME_NL, "Geef de naam van het Franse Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_FR_KERNEL_NAME_PL, "Okre∂l nazwÍ obrazu francuskiego ROM-u Kernala"},
	/* ru */ {IDCLS_SPECIFY_FR_KERNEL_NAME_RU, "Specify name of French Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_FR_KERNEL_NAME_SV, "Ange namn pÂ fransk kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_FR_KERNEL_NAME_TR, "Frans˝z Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_IT_KERNEL_NAME,    N_("Specify name of Italian Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_IT_KERNEL_NAME_DA, "Angiv navn pÂ italiensk kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_IT_KERNEL_NAME_DE, "Name f¸r italienische Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_IT_KERNEL_NAME_ES, "Especificar nombre imagen ROM Kernal italiano"},
	/* fr */ {IDCLS_SPECIFY_IT_KERNEL_NAME_FR, "SpÈcifier le nom de l'image Kernal italienne"},
	/* hu */ {IDCLS_SPECIFY_IT_KERNEL_NAME_HU, "Adja meg az olasz Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_IT_KERNEL_NAME_IT, "Specifica il nome immagine della ROM del Kernal italiana"},
	/* ko */ {IDCLS_SPECIFY_IT_KERNEL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_IT_KERNEL_NAME_NL, "Geef de naam van het Italiaanse Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_IT_KERNEL_NAME_PL, "Okre∂l nazwÍ obrazu w≥oskiego ROM-u Kernala"},
	/* ru */ {IDCLS_SPECIFY_IT_KERNEL_NAME_RU, "Specify name of Italian Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_IT_KERNEL_NAME_SV, "Ange namn pÂ italiensk kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_IT_KERNEL_NAME_TR, "›talyan Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_NO_KERNEL_NAME,    N_("Specify name of Norwegian Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_NO_KERNEL_NAME_DA, "Angiv navn pÂ norsk kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_NO_KERNEL_NAME_DE, "Name f¸r norwegische Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_NO_KERNEL_NAME_ES, "Especificar nombre imagen ROM noruego"},
	/* fr */ {IDCLS_SPECIFY_NO_KERNEL_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_NO_KERNEL_NAME_HU, "Adja meg a norvÈg Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_NO_KERNEL_NAME_IT, "Specifica il nome immagine della ROM del Kernal norvegese"},
	/* ko */ {IDCLS_SPECIFY_NO_KERNEL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_NO_KERNEL_NAME_NL, "Geef de naam van het Noorse Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_NO_KERNEL_NAME_PL, "Okre∂l nazwÍ obrazu norweskiego ROM-u Kernala"},
	/* ru */ {IDCLS_SPECIFY_NO_KERNEL_NAME_RU, "Specify name of Norwegian Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_NO_KERNEL_NAME_SV, "Ange namn pÂ norsk kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_NO_KERNEL_NAME_TR, "NorveÁ Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_SV_KERNEL_NAME,    N_("Specify name of Swedish Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SV_KERNEL_NAME_DA, "Angiv navn pÂ svensk kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_SV_KERNEL_NAME_DE, "Name f¸r schwedische Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_SV_KERNEL_NAME_ES, "Especificar nombre imagen ROM Kernal sueco"},
	/* fr */ {IDCLS_SPECIFY_SV_KERNEL_NAME_FR, "SpÈcifier le nom de l'image Kernal suÈdoise"},
	/* hu */ {IDCLS_SPECIFY_SV_KERNEL_NAME_HU, "Adja meg s svÈd Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_SV_KERNEL_NAME_IT, "Specifica il nome immagine della ROM del Kernal svedese"},
	/* ko */ {IDCLS_SPECIFY_SV_KERNEL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SV_KERNEL_NAME_NL, "Geef de naam van het Zweedse Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_SV_KERNEL_NAME_PL, "Okre∂l nazwÍ obrazu szwedzkiego ROM-u Kernala"},
	/* ru */ {IDCLS_SPECIFY_SV_KERNEL_NAME_RU, "Specify name of Swedish Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_SV_KERNEL_NAME_SV, "Ange namn pÂ svensk kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_SV_KERNEL_NAME_TR, "›sveÁ Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW,    N_("Specify name of BASIC ROM image (lower part)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_DA, "Angiv navn pÂ BASIC ROM-image (lav del)"},
	/* de */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_DE, "Namen f¸r Basic ROM Datei spezifizieren (unterer Teil)"},
	/* es */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_ES, "Especificar nombre imagen BASIC ROM (parte baja)"},
	/* fr */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_FR, "SpÈcifier le nom de l'image BASIC ROM (partie basse)"},
	/* hu */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_HU, "Adja meg a BASIC ROM kÈpm·s nevÈt (alsÛ rÈsz)"},
	/* it */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_IT, "Specifica il nome immagine della ROM del BASIC (parte inferiore)"},
	/* ko */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_NL, "Geef de naam van het BASIC ROM bestand (laag gedeelte)"},
	/* pl */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_PL, "Okre∂l nazwÍ obrazu ROM BASIC (niøsza partia)"},
	/* ru */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_RU, "Specify name of BASIC ROM image (lower part)"},
	/* sv */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_SV, "Ange namn pÂ BASIC ROM-avbildning (nedre delen)"},
	/* tr */ {IDCLS_SPECIFY_BASIC_ROM_NAME_LOW_TR, "BASIC ROM imaj˝n˝n (alt k˝s˝m) ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH,    N_("Specify name of BASIC ROM image (higher part)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_DA, "Angiv navn pÂ BASIC ROM-image (h¯j del)"},
	/* de */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_DE, "Namen f¸r Basic ROM Datei spezifizieren (oberer Teil)"},
	/* es */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_ES, "Especificar nombre imagen BASIC ROM (parte alta)"},
	/* fr */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_FR, "SpÈcifier le nom de l'image BASIC ROM (partie haute)"},
	/* hu */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_HU, "Adja meg a BASIC ROM kÈpm·s nevÈt (felsı rÈsz)"},
	/* it */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_IT, "Specifica il nome immagine della ROM del BASIC (parte superiore)"},
	/* ko */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_NL, "Geef de naam van het BASIC ROM bestand (hoog gedeelte)"},
	/* pl */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_PL, "Okre∂l nazwÍ obrazu ROM BASIC (wyøsza partia)"},
	/* ru */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_RU, "Specify name of BASIC ROM image (higher part)"},
	/* sv */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_SV, "Ange namn pÂ BASIC ROM-avbildning (ˆvre delen)"},
	/* tr */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HIGH_TR, "BASIC ROM imaj˝n˝n (¸st k˝s˝m) ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME,    N_("Specify name of international character generator ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_DA, "Angiv navn pÂ internationalt tegngenerator-ROM-image"},
	/* de */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_DE, "Name f¸r internationale Charakter ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_ES, "Especificar nombre imagen ROM generador caracteres internacional"},
	/* fr */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_FR, "SpÈcifier le nom de l'image du gÈnÈrateur de caractËres internationaux"},
	/* hu */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_HU, "Adja meg a nemzetkˆzi karaktergener·tor ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_IT, "Specifica il nome immagine della ROM del generatore di caratteri internazionale"},
	/* ko */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_NL, "Geef de naam van het internationaal CHARGEN ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM generatora znakÛw miÍdzynarodowych"},
	/* ru */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_RU, "Specify name of international character generator ROM image"},
	/* sv */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_SV, "Ange namn pÂ internationell teckengenerator-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_INT_CHARGEN_ROM_NAME_TR, "Uluslararas˝ Karakter Olu˛turucu ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME,    N_("Specify name of German character generator ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_DA, "Angiv navn pÂ tysk tegngenerator-ROM-image"},
	/* de */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_DE, "Name f¸r deutsche Charakter ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_ES, "Especificar nombre imagen ROM generador caracteres alem·n"},
	/* fr */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_FR, "SpÈcifier le nom de l'image du gÈnÈrateur de caractËres allemands"},
	/* hu */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_HU, "Adja meg a nÈmet karaktergener·tor ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_IT, "Specifica il nome immagine della ROM del generatore di caratteri tedesco"},
	/* ko */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_NL, "Geef de naam van het Duitse CHARGEN ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM generatora niemieckich znakÛw"},
	/* ru */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_RU, "√⁄–◊–‚Ï ÿ‹Ô ROM ﬁ—‡–◊– ”’›’‡–‚ﬁ‡– ›’‹’Ê⁄ÿÂ ·ÿ‹“ﬁ€ﬁ“"},
	/* sv */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_SV, "Ange namn pÂ tysk teckengenerator-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_DE_CHARGEN_ROM_NAME_TR, "Alman Karakter Olu˛turucu ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME,    N_("Specify name of French character generator ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_DA, "Angiv navn pÂ fransk tegngenerator-ROM-image"},
	/* de */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_DE, "Name f¸r franzˆsische Charakter ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_ES, "Especificar nombre imagen ROM generador caracteres francÈs"},
	/* fr */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_FR, "SpÈcifier le nom de l'image du gÈnÈrateur de caractËres franÁais"},
	/* hu */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_HU, "Adja meg a francia karaktergener·tor ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_IT, "Specifica il nome immagine della ROM del generatore di caratteri francese"},
	/* ko */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_NL, "Geef de naam van het Franse CHARGEN ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM generatora francuskich znakÛw"},
	/* ru */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_RU, "√⁄–◊–‚Ï ÿ‹Ô ROM ﬁ—‡–◊– ”’›’‡–‚ﬁ‡– ‰‡–›Ê„◊·⁄ÿÂ ·ÿ‹“ﬁ€ﬁ“"},
	/* sv */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_SV, "Ange namn pÂ fransk teckengenerator-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_FR_CHARGEN_ROM_NAME_TR, "Finlandiya Karakter Olu˛turucu ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME,    N_("Specify name of Swedish character generator ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_DA, "Angiv navn pÂ svensk tegngenerator-ROM-image"},
	/* de */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_DE, "Name f¸r schwedische Charakter ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_ES, "Especificar nombre imagen ROM generador caracteres sueco"},
	/* fr */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_FR, "SpÈcifier le nom de l'image du gÈnÈrateur de caractËres suÈdois"},
	/* hu */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_HU, "Adja meg a svÈd karaktergener·tor ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_IT, "Specifica il nome immagine della ROM del generatore di caratteri svedese"},
	/* ko */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_NL, "Geef de naam van het Zweedse CHARGEN ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM generatora szwedzkich znakÛw"},
	/* ru */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_RU, "√⁄–◊–‚Ï ÿ‹Ô ROM ﬁ—‡–◊– ”’›’‡–‚ﬁ‡– Ë“’‘·⁄ÿÂ ·ÿ‹“ﬁ€ﬁ“"},
	/* sv */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_SV, "Ange namn pÂ svensk teckengenerator-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_SV_CHARGEN_ROM_NAME_TR, "›sveÁ Karakter Olu˛turucu ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME,    N_("Specify name of C64 mode Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_DA, "Angiv navn pÂ C64-kerne-ROM-image"},
	/* de */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_DE, "Name f¸r C64 Modus Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_ES, "Especificar nombre imagen ROM Kernal modo C64"},
	/* fr */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_FR, "SpÈcifier le nom de l'image Kernal du mode C64"},
	/* hu */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_HU, "Adja meg a C64 mÛd˙ Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_IT, "Specifica il nome immagine della ROM del Kernal in modalit‡ C64"},
	/* ko */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_NL, "Geef de naam van het Kernal ROM bestand voor de C64 modus"},
	/* pl */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_PL, "Okre∂l nazwÍ obrazu ROM Kernala trybu C64"},
	/* ru */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_RU, "Specify name of C64 mode Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_SV, "Ange namn pÂ C64-kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_C64_MODE_KERNAL_NAME_TR, "C64 modu Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME,    N_("Specify name of C64 mode BASIC ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_DA, "Angiv navn pÂ C64-BASIC-ROM-image"},
	/* de */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_DE, "Name f¸r C64 Modus Basic ROM Datei spezifizieren"},
	/* es */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_ES, "Especificar nombre imagen BASIC ROM modo C64"},
	/* fr */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_FR, "SpÈcifier le nom de l'image BASIC ROM du mode C64"},
	/* hu */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_HU, "Adja meg a C64 mÛd˙ BASIC ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_IT, "Specifica il nome immagine della ROM in modalit‡ C64"},
	/* ko */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_NL, "Geef de naam van het BASIC ROM bestand voor de C64 modus"},
	/* pl */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_PL, "Okre∂l nazwÍ obrazu ROM BASIC trybu C64"},
	/* ru */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_RU, "√⁄–◊–‚Ï ÿ‹Ô ROM ﬁ—‡–◊– ‡’÷ÿ‹– C64 BASIC"},
	/* sv */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_SV, "Ange namn pÂ C64-BASIC-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_C64_MODE_BASIC_NAME_TR, "C64 modu BASIC ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_OEM_JOY,    N_("Enable the OEM userport joystick adapter")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_OEM_JOY_DA, "AktivÈr OEM brugerportjoystickadapter"},
	/* de */ {IDCLS_ENABLE_OEM_JOY_DE, "OEM Userport Joystick Adapter aktivieren"},
	/* es */ {IDCLS_ENABLE_OEM_JOY_ES, "Permitir adaptador puerto joystick OEM"},
	/* fr */ {IDCLS_ENABLE_OEM_JOY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_OEM_JOY_HU, "OEM userport botkorm·ny adapter engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_OEM_JOY_IT, "Attiva adattatore joystick OEM su userport"},
	/* ko */ {IDCLS_ENABLE_OEM_JOY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_OEM_JOY_NL, "Activeer de OEM userport joystick adapter"},
	/* pl */ {IDCLS_ENABLE_OEM_JOY_PL, "W≥±cz z≥±cze OEM userportu joysticka"},
	/* ru */ {IDCLS_ENABLE_OEM_JOY_RU, "Enable the OEM userport joystick adapter"},
	/* sv */ {IDCLS_ENABLE_OEM_JOY_SV, "Aktivera OEM-anv‰ndarportspelportsadapter"},
	/* tr */ {IDCLS_ENABLE_OEM_JOY_TR, "OEM userport joystick dˆn¸˛t¸r¸c¸y¸ aktif et"},
#endif
	
	/* vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_OEM_JOY,    N_("Disable the OEM userport joystick adapter")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_OEM_JOY_DA, "DeaktivÈr OEM brugerportjoystickadapter"},
	/* de */ {IDCLS_DISABLE_OEM_JOY_DE, "OEM Userport Joystick Adapter deaktivieren"},
	/* es */ {IDCLS_DISABLE_OEM_JOY_ES, "Deshabilitar adaptador puerto joystick OEM"},
	/* fr */ {IDCLS_DISABLE_OEM_JOY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_OEM_JOY_HU, "OEM userport botkorm·ny adapter tilt·sa"},
	/* it */ {IDCLS_DISABLE_OEM_JOY_IT, "Disattiva adattatore joystick OEM su userport"},
	/* ko */ {IDCLS_DISABLE_OEM_JOY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_OEM_JOY_NL, "De OEM userport joystick adapter uitschakelen"},
	/* pl */ {IDCLS_DISABLE_OEM_JOY_PL, "Wy≥±cz z≥±cze OEM userportu joysticka"},
	/* ru */ {IDCLS_DISABLE_OEM_JOY_RU, "Disable the OEM userport joystick adapter"},
	/* sv */ {IDCLS_DISABLE_OEM_JOY_SV, "Inaktivera OEM-anv‰ndarportspelportsadapter"},
	/* tr */ {IDCLS_DISABLE_OEM_JOY_TR, "OEM userport joystick dˆn¸˛t¸r¸c¸y¸ pasifle˛tir"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_IEE488,    N_("Enable the IEEE488 interface emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEE488_DA, "AktivÈr emulering af IEEE488-interface"},
	/* de */ {IDCLS_ENABLE_IEE488_DE, "IEEE488 Schnittstellen-Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_IEE488_ES, "Permitir emulaciÛn interface IEEE488"},
	/* fr */ {IDCLS_ENABLE_IEE488_FR, "Activer l'interface d'Èmulation IEEE488"},
	/* hu */ {IDCLS_ENABLE_IEE488_HU, "IEEE488 interfÈsz emul·ciÛ engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEE488_IT, "Attiva emulazione interfaccia IEEE488"},
	/* ko */ {IDCLS_ENABLE_IEE488_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEE488_NL, "Activeer de IEEE488 interface emulatie"},
	/* pl */ {IDCLS_ENABLE_IEE488_PL, "W≥±cz emulacjÍ interfejsu IEEE488"},
	/* ru */ {IDCLS_ENABLE_IEE488_RU, "Enable the IEEE488 interface emulation"},
	/* sv */ {IDCLS_ENABLE_IEE488_SV, "Aktivera emulering av IEEE488-gr‰nssnitt"},
	/* tr */ {IDCLS_ENABLE_IEE488_TR, "IEEE488 arabirim em¸lasyonunu aktif et"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_IEE488,    N_("Disable the IEEE488 interface emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEE488_DA, "DeaktivÈr emulering af IEEE488-interface"},
	/* de */ {IDCLS_DISABLE_IEE488_DE, "IEEE488 Schnittstellen-Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEE488_ES, "Deshabilitar emulaciÛn interface IEEE488"},
	/* fr */ {IDCLS_DISABLE_IEE488_FR, "DÈsactiver l'interface d'Èmulation IEEE488"},
	/* hu */ {IDCLS_DISABLE_IEE488_HU, "IEEE488 interfÈsz emul·ciÛ tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEE488_IT, "Disattiva emulazione interfaccia IEEE488"},
	/* ko */ {IDCLS_DISABLE_IEE488_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEE488_NL, "De IEEE488 interface emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEE488_PL, "Wy≥±cz emulacjÍ interfejsu IEEE488"},
	/* ru */ {IDCLS_DISABLE_IEE488_RU, "Disable the IEEE488 interface emulation"},
	/* sv */ {IDCLS_DISABLE_IEE488_SV, "Inaktivera emulering av IEEE488-gr‰nssnitt"},
	/* tr */ {IDCLS_DISABLE_IEE488_TR, "IEEE488 arabirim em¸lasyonunu pasifle˛tir"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c */
	/* en */ {IDCLS_P_REVISION,    N_("<Revision>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_REVISION_DA, "<Udgave>"},
	/* de */ {IDCLS_P_REVISION_DE, "<Revision>"},
	/* es */ {IDCLS_P_REVISION_ES, "<RevisiÛn>"},
	/* fr */ {IDCLS_P_REVISION_FR, "<RÈvision>"},
	/* hu */ {IDCLS_P_REVISION_HU, "<V·ltozatsz·m>"},
	/* it */ {IDCLS_P_REVISION_IT, "<Revisione>"},
	/* ko */ {IDCLS_P_REVISION_KO, "<ºˆ¡§>"},
	/* nl */ {IDCLS_P_REVISION_NL, "<Revisie>"},
	/* pl */ {IDCLS_P_REVISION_PL, "<Poprawka>"},
	/* ru */ {IDCLS_P_REVISION_RU, "<Revision>"},
	/* sv */ {IDCLS_P_REVISION_SV, "<UtgÂva>"},
	/* tr */ {IDCLS_P_REVISION_TR, "<Revizyon>"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c */
	/* en */ {IDCLS_PATCH_KERNAL_TO_REVISION,    N_("Patch the Kernal ROM to the specified <revision>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PATCH_KERNAL_TO_REVISION_DA, "Patch kerne-ROM til den angivne <revision>"},
	/* de */ {IDCLS_PATCH_KERNAL_TO_REVISION_DE, "Kernal ROM auf spezifizierte <Revision> ver‰ndern"},
	/* es */ {IDCLS_PATCH_KERNAL_TO_REVISION_ES, "Parchear la ROM Kernal a la versiÛn <revisiÛn>"},
	/* fr */ {IDCLS_PATCH_KERNAL_TO_REVISION_FR, "Mettre ‡ jour le ROM Kernal ‡ la <revision> spÈcifiÈe"},
	/* hu */ {IDCLS_PATCH_KERNAL_TO_REVISION_HU, "A Kernal ROM ·tÌr·sa adott <v·ltozatra>"},
	/* it */ {IDCLS_PATCH_KERNAL_TO_REVISION_IT, "Fai il patch della ROM del Kernal alla <revisione> specificata"},
	/* ko */ {IDCLS_PATCH_KERNAL_TO_REVISION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PATCH_KERNAL_TO_REVISION_NL, "Verbeter de Kernal ROM naar de opgegeven <revisie>"},
	/* pl */ {IDCLS_PATCH_KERNAL_TO_REVISION_PL, "Za≥ataj ROM Kernala do konkretnej <wersji>"},
	/* ru */ {IDCLS_PATCH_KERNAL_TO_REVISION_RU, "Patch the Kernal ROM to the specified <revision>"},
	/* sv */ {IDCLS_PATCH_KERNAL_TO_REVISION_SV, "Patcha kernal-ROM till angiven <utgÂva>"},
	/* tr */ {IDCLS_PATCH_KERNAL_TO_REVISION_TR, "Kernal ROM'u belirtilmi˛ <revizyon>'a yama"},
#endif
	
#ifdef HAVE_RS232
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU,    N_("Enable the ACIA RS232 interface emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_DA, "AktivÈr ACIA RS232-interface emulering"},
	/* de */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_DE, "ACIA RS232 Schnittstellen-Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_ES, "Permitir emulaciÛn interface ACIA RS232"},
	/* fr */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_IT, "Attiva emulazione interfaccia ACIA RS232"},
	/* ko */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_NL, "Activeer de ACIA RS232 interface emulatie"},
	/* pl */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_PL, "W≥±cz emulacjÍ interfejsu ACIA RS232"},
	/* ru */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_RU, "Enable the ACIA RS232 interface emulation"},
	/* sv */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_SV, "Aktivera ACIA RS232-gr‰nssnittsemulering"},
	/* tr */ {IDCLS_ENABLE_DEXX_ACIA_RS232_EMU_TR, "ACIA RS232 arabirim em¸lasyonunu aktif et"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU,    N_("Disable the ACIA RS232 interface emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_DA, "DeaktivÈr ACIA-RS232-interface emulering"},
	/* de */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_DE, "ACIA RS232 Schnittstellen-Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_ES, "Deshabilitar emulaciÛn interface ACIA RS232"},
	/* fr */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_IT, "Disattiva emulazione interfaccia ACIA RS232"},
	/* ko */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_NL, "De ACIA RS232 interface emulatie aflsuiten"},
	/* pl */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_PL, "Wy≥±cz emulacjÍ interfejsu ACIA RS232"},
	/* ru */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_RU, "Disable the ACIA RS232 interface emulation"},
	/* sv */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_SV, "Inaktivera ACIA-RS232-gr‰nssnittsemulering"},
	/* tr */ {IDCLS_DISABLE_DEXX_ACIA_RS232_EMU_TR, "ACIA RS232 arabirim em¸lasyonunu pasifle˛tir"},
#endif
#endif
	
	/* plus4/plus4acia.c */
	/* en */ {IDCLS_ENABLE_ACIA_EMU,    N_("Enable the ACIA emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_ACIA_EMU_DA, "AktivÈr ACIA-emulering"},
	/* de */ {IDCLS_ENABLE_ACIA_EMU_DE, "ACIA Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_ACIA_EMU_ES, "Habilitar emulaciÛn ACIA"},
	/* fr */ {IDCLS_ENABLE_ACIA_EMU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_ACIA_EMU_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_ACIA_EMU_IT, "Attiva emulazione ACIA"},
	/* ko */ {IDCLS_ENABLE_ACIA_EMU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_ACIA_EMU_NL, "Activeer de ACIA emulatie"},
	/* pl */ {IDCLS_ENABLE_ACIA_EMU_PL, "W≥±cz emulacjÍ ACIA"},
	/* ru */ {IDCLS_ENABLE_ACIA_EMU_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_ACIA_EMU_SV, "Aktivera ACIA-emuleringen"},
	/* tr */ {IDCLS_ENABLE_ACIA_EMU_TR, "ACIA em¸lasyonunu aktif et"},
#endif
	
	/* plus4/plus4acia.c */
	/* en */ {IDCLS_DISABLE_ACIA_EMU,    N_("Disable the ACIA emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_ACIA_EMU_DA, "DeaktivÈr ACIA-emulering"},
	/* de */ {IDCLS_DISABLE_ACIA_EMU_DE, "ACIA Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_ACIA_EMU_ES, "Deshabilitar emulaciÛn ACIA"},
	/* fr */ {IDCLS_DISABLE_ACIA_EMU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_ACIA_EMU_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_ACIA_EMU_IT, "Disattiva emulazione ACIA"},
	/* ko */ {IDCLS_DISABLE_ACIA_EMU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_ACIA_EMU_NL, "De ACIA emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_ACIA_EMU_PL, "Wy≥±cz emulacjÍ ACIA"},
	/* ru */ {IDCLS_DISABLE_ACIA_EMU_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_ACIA_EMU_SV, "Inaktivera ACIA-emuleringen"},
	/* tr */ {IDCLS_DISABLE_ACIA_EMU_TR, "ACIA em¸lasyonunu pasifle˛tir"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c,
	 c64/psid.c, cbm2/cbm2-cmdline-options.c,
	 pet/pet-cmdline-options.c, plus4/plus4-cmdline-options.c,
	 vdc/vdc-cmdline-options.c, vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_P_NUMBER,    N_("<number>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_NUMBER_DA, "<nummer>"},
	/* de */ {IDCLS_P_NUMBER_DE, "<Nummer>"},
	/* es */ {IDCLS_P_NUMBER_ES, "<n˙mero>"},
	/* fr */ {IDCLS_P_NUMBER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_NUMBER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_NUMBER_IT, "<numero>"},
	/* ko */ {IDCLS_P_NUMBER_KO, "<º˝¿⁄>"},
	/* nl */ {IDCLS_P_NUMBER_NL, "<nummer>"},
	/* pl */ {IDCLS_P_NUMBER_PL, "<numer>"},
	/* ru */ {IDCLS_P_NUMBER_RU, "<number>"},
	/* sv */ {IDCLS_P_NUMBER_SV, "<nummer>"},
	/* tr */ {IDCLS_P_NUMBER_TR, "<say˝>"},
#endif
	
#ifdef COMMON_KBD
	/* c128/c128-cmdline-options.c, plus4/plus4-cmdline-options.c,
	 vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX,    N_("Specify index of keymap file (0=symbol, 1=positional)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_DA, "Angiv indeks for tastaturindstillingsfil (0=symbolsk, 1=positionsbestemt)"},
	/* de */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_DE, "Index f¸r Kymap Datei festlegen (0=symbol, 1=positional)"},
	/* es */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_ES, "Especificar Ìndice del fichero mapa del teclado (0=simbÛlico, 1=posicional)"},
	/* fr */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_FR, "SpÈcifier l'index du fichier keymap (0=symboles, 1=position)"},
	/* hu */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_HU, "Adja meg a billenty˚zet lekÈpzÈsi mÛdot (0=szimbolikus, 1=pozÌciÛ szerinti)"},
	/* it */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_IT, "Specifica l'indice del file della mappa della tastiera (0=simbolica, 1=posizionale)"},
	/* ko */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_NL, "Geef index van het keymapbestand (0=symbool, 1=positioneel)"},
	/* pl */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_PL, "Podaj indeks uk≥adu klawiatury (0=symbol, 1=pozycja)"},
	/* ru */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_RU, "Specify index of keymap file (0=symbol, 1=positional)"},
	/* sv */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_SV, "Ange index fˆr fˆr tangentbordsinst‰llningsfil (0=symbolisk, 1=positionsriktig)"},
	/* tr */ {IDCLS_SPECIFY_KEYMAP_FILE_INDEX_TR, "Tu˛ haritas˝ dosyas˝n˝n indeksini belirt (0=sembol, 1=konumsal)"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c,
	 plus4/plus4-cmdline-options.c, vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME,    N_("Specify name of symbolic keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_DA, "Angiv filnavn for symbolsk tastatur"},
	/* de */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_DE, "Bitte Namen f¸r symbolische Keymap Datei definieren"},
	/* es */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_ES, "Especificar nombre fichero del mapa de teclado simbÛlico"},
	/* fr */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier symbolique"},
	/* hu */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_HU, "Adja meg a szimbolikus lekÈpzÈsf·jl nevÈt"},
	/* it */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_IT, "Specifica il nome del file della mappa simbolica della tastiera"},
	/* ko */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_NL, "Geef naam van het symbolisch keymapbestand"},
	/* pl */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_PL, "Okre∂l nazwÍ pliku symbolicznego uk≥adu klawiatury"},
	/* ru */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_RU, "Specify name of symbolic keymap file"},
	/* sv */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_SV, "Ange fil fˆr symbolisk tangentbordsemulering"},
	/* tr */ {IDCLS_SPECIFY_SYM_KEYMAP_FILE_NAME_TR, "Sembolik tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
	
	/* c128/c128-cmdline-options.c, c64/c64-cmdline-options.c,
	 plus4/plus4-cmdline-options.c, vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME,    N_("Specify name of positional keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_DA, "Angiv fil for positionsbestemt tastatur"},
	/* de */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_DE, "Bitte Namen f¸r positions Keymap Datei definieren"},
	/* es */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_ES, "Especificar nombre fichero del mapa de teclado posicional"},
	/* fr */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier positionnel"},
	/* hu */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_HU, "Adja meg a pozÌciÛ szerinti lekÈpzÈsf·jl nevÈt"},
	/* it */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_IT, "Specifica il nome del file della mappa posizionale della tastiera"},
	/* ko */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_NL, "Geef naam van het positioneel keymapbestand"},
	/* pl */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_PL, "Okre∂l nazwÍ pliku pozycyjnego uk≥adu klawiatury"},
	/* ru */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_RU, "Specify name of positional keymap file"},
	/* sv */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_SV, "Ange fil fˆr positionsriktig tangentbordsemulering"},
	/* tr */ {IDCLS_SPECIFY_POS_KEYMAP_FILE_NAME_TR, "Konumsal tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
#endif
	
	/* c128/c128mmu.c */
	/* en */ {IDCLS_ACTIVATE_40_COL_MODE,    N_("Activate 40 column mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ACTIVATE_40_COL_MODE_DA, "AktivÈr 40-kolonners tilstand"},
	/* de */ {IDCLS_ACTIVATE_40_COL_MODE_DE, "40 Spalten Modus aktivieren"},
	/* es */ {IDCLS_ACTIVATE_40_COL_MODE_ES, "Activar modo 40 columnas"},
	/* fr */ {IDCLS_ACTIVATE_40_COL_MODE_FR, "Activer le mode 40 colonnes"},
	/* hu */ {IDCLS_ACTIVATE_40_COL_MODE_HU, "40 oszlopos mÛd aktiv·l·sa"},
	/* it */ {IDCLS_ACTIVATE_40_COL_MODE_IT, "Attiva modalit‡ a 40 colonne"},
	/* ko */ {IDCLS_ACTIVATE_40_COL_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ACTIVATE_40_COL_MODE_NL, "Activeer 40 kolomsmodus"},
	/* pl */ {IDCLS_ACTIVATE_40_COL_MODE_PL, "W≥±cz tryb 40 kolumn"},
	/* ru */ {IDCLS_ACTIVATE_40_COL_MODE_RU, "∞⁄‚ÿ“ÿ‡ﬁ“–‚Ï ‡’÷ÿ‹ 40 ⁄ﬁ€ﬁ›ﬁ⁄"},
	/* sv */ {IDCLS_ACTIVATE_40_COL_MODE_SV, "Aktivera 40-kolumnersl‰ge"},
	/* tr */ {IDCLS_ACTIVATE_40_COL_MODE_TR, "40 s¸tun modunu aktif et"},
#endif
	
	/* c128/c128mmu.c */
	/* en */ {IDCLS_ACTIVATE_80_COL_MODE,    N_("Activate 80 column mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ACTIVATE_80_COL_MODE_DA, "AktivÈr 80-kolonners tilstand"},
	/* de */ {IDCLS_ACTIVATE_80_COL_MODE_DE, "80 Spalten Modus aktivieren"},
	/* es */ {IDCLS_ACTIVATE_80_COL_MODE_ES, "Activar modo 80 columnas"},
	/* fr */ {IDCLS_ACTIVATE_80_COL_MODE_FR, "Activer le mode 80 colonnes"},
	/* hu */ {IDCLS_ACTIVATE_80_COL_MODE_HU, "80 oszlopos mÛd aktiv·l·sa"},
	/* it */ {IDCLS_ACTIVATE_80_COL_MODE_IT, "Attiva modalit‡ a 80 colonne"},
	/* ko */ {IDCLS_ACTIVATE_80_COL_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ACTIVATE_80_COL_MODE_NL, "Activeer 80 kolomsmodus"},
	/* pl */ {IDCLS_ACTIVATE_80_COL_MODE_PL, "W≥±cz tryb 80 kolumn"},
	/* ru */ {IDCLS_ACTIVATE_80_COL_MODE_RU, "∞⁄‚ÿ“ÿ‡ﬁ“–‚Ï ‡’÷ÿ‹ 80 ⁄ﬁ€ﬁ›ﬁ⁄"},
	/* sv */ {IDCLS_ACTIVATE_80_COL_MODE_SV, "Aktivera 80-kolumnersl‰ge"},
	/* tr */ {IDCLS_ACTIVATE_80_COL_MODE_TR, "80 s¸tun modunu aktif et"},
#endif
	
	/* c128/c128mmu.c */
	/* en */ {IDCLS_GO64_MODE,    N_("Always switch to C64 mode on reset")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_GO64_MODE_DA, "Skift altid til C64-tilstand ved reset"},
	/* de */ {IDCLS_GO64_MODE_DE, "Immer bei Reset in C64 Modus schalten"},
	/* es */ {IDCLS_GO64_MODE_ES, "Al reiniciar, pasar siempre al modo C64"},
	/* fr */ {IDCLS_GO64_MODE_FR, "Toujours revenir au mode C64 au redÈmarrage"},
	/* hu */ {IDCLS_GO64_MODE_HU, "Mindig C64 mÛdban ˙jraindÌt·s ut·n"},
	/* it */ {IDCLS_GO64_MODE_IT, "Usa sempre in modalit‡ C64 al reset"},
	/* ko */ {IDCLS_GO64_MODE_KO, "¥ŸΩ√Ω√¿€«œ∏È «◊ªÛ C64 ∏µÂ ∑Œ πŸ≤Ú¥œ¥Ÿ"},
	/* nl */ {IDCLS_GO64_MODE_NL, "Start altijd op in C64 modus na reset"},
	/* pl */ {IDCLS_GO64_MODE_PL, "Przy restarcie zawsze prze≥±czaj w tryb C64"},
	/* ru */ {IDCLS_GO64_MODE_RU, "Always switch to C64 mode on reset"},
	/* sv */ {IDCLS_GO64_MODE_SV, "V‰xla alltid till C64-l‰ge vid Âterst‰llning"},
	/* tr */ {IDCLS_GO64_MODE_TR, "Resetlendiinde her zaman C64 moduna geÁ"},
#endif
	
	/* c128/c128mmu.c */
	/* en */ {IDCLS_GO128_MODE,    N_("Always switch to C128 mode on reset")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_GO128_MODE_DA, "Skift altid til C128-tilstand ved reset"},
	/* de */ {IDCLS_GO128_MODE_DE, "Immer be Reset in C128 Modus schalten"},
	/* es */ {IDCLS_GO128_MODE_ES, "Al reiniciar, pasar siempre al modo C128"},
	/* fr */ {IDCLS_GO128_MODE_FR, "Toujours revenir au mode C128 au redÈmarrage"},
	/* hu */ {IDCLS_GO128_MODE_HU, "Mindig C128 mÛd ˙jraindÌt·s ut·n"},
	/* it */ {IDCLS_GO128_MODE_IT, "Cambia sempre in modalit‡ C128 al reset"},
	/* ko */ {IDCLS_GO128_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_GO128_MODE_NL, "Start altijd op in C128 modus na reset"},
	/* pl */ {IDCLS_GO128_MODE_PL, "Przy restarcie zawsze prze≥±czaj w tryb C128"},
	/* ru */ {IDCLS_GO128_MODE_RU, "≤·’”‘– ﬂ’‡’⁄€ÓÁ–‚Ï “ ‡’÷ÿ‹ C128 ﬂﬁ·€’ ﬂ’‡’◊–ﬂ„·⁄–"},
	/* sv */ {IDCLS_GO128_MODE_SV, "V‰xla alltid till C128-l‰ge vid Âterst‰llning"},
	/* tr */ {IDCLS_GO128_MODE_TR, "Resetlendiinde her zaman C128 moduna geÁ"},
#endif
	
	/* c128/functionrom.c */
	/* en */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME,    N_("Specify name of internal Function ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_DA, "Angiv navn pÂ internt funktions-ROM-image"},
	/* de */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_DE, "Name der internen Funktions ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_ES, "Especificar nombre imagen ROM funciÛn interna"},
	/* fr */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_FR, "SpÈcifier le nom de l'image ROM des fonctions internes"},
	/* hu */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_HU, "Adja meg a belsı Function ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_IT, "Specifica il nome immagine della Function ROM interna"},
	/* ko */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_NL, "Geef de naam van het intern functie ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_PL, "Okre∂l nazwÍ obrazu wewnÍtrznego Function ROM-u"},
	/* ru */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_RU, "Specify name of internal Function ROM image"},
	/* sv */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_SV, "Ange namn pÂ intern funktions-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_INT_FUNC_ROM_NAME_TR, "Dahili Function ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/functionrom.c */
	/* en */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME,    N_("Specify name of external Function ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_DA, "Angiv navn pÂ externt funktions-ROM-image"},
	/* de */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_DE, "Name der externen Funktions ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_ES, "Especificar nombre imagen ROM funciÛn externa"},
	/* fr */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_FR, "SpÈcifier le nom de l'image ROM des fonctions externes"},
	/* hu */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_HU, "Adja meg a k¸lsı Function ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_IT, "Specifica il nome immagine della Function ROM esterna"},
	/* ko */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_NL, "Geef de naam van het extern functie ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_PL, "Okre∂l nazwÍ obrazu zewnÍtrznego Function ROM-u"},
	/* ru */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_RU, "Specify name of external Function ROM image"},
	/* sv */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_SV, "Ange namn pÂ extern funktions-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_EXT_FUNC_ROM_NAME_TR, "Harici Function ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c128/functionrom.c */
	/* en */ {IDCLS_ENABLE_INT_FUNC_ROM,    N_("Type of internal Function ROM: (0: None, 1: ROM, 2: RAM, 3: RTC)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_INT_FUNC_ROM_DA, "Typen af intern funktions-ROM: (0: Ingen, 1: ROM, 2: RAM, 3:RTC)"},
	/* de */ {IDCLS_ENABLE_INT_FUNC_ROM_DE, "Typ des internen Funktions ROM: (0: Kein, 1: ROM, 2: RAM, 3: RTC)"},
	/* es */ {IDCLS_ENABLE_INT_FUNC_ROM_ES, "Tipo de Function ROM interna: (0: None, 1: ROM, 2: RAM, 3: RTC)"},
	/* fr */ {IDCLS_ENABLE_INT_FUNC_ROM_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_INT_FUNC_ROM_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_INT_FUNC_ROM_IT, "Tipologia di function ROM interna: (0: None, 1: ROM, 2: RAM, 3: RTC)"},
	/* ko */ {IDCLS_ENABLE_INT_FUNC_ROM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_INT_FUNC_ROM_NL, "Intern functie ROM soort: (0: Geen, 1: ROM, 2: RAM, 3: RTC)"},
	/* pl */ {IDCLS_ENABLE_INT_FUNC_ROM_PL, "Typ wewnÍtrznego Function ROM-u: (0: Øaden, 1: ROM, 2: RAM, 3: RTC)"},
	/* ru */ {IDCLS_ENABLE_INT_FUNC_ROM_RU, "Type of internal Function ROM: (0: None, 1: ROM, 2: RAM, 3: RTC)"},
	/* sv */ {IDCLS_ENABLE_INT_FUNC_ROM_SV, "Typ fˆr intern funktions-ROM (0: ingen, 1: ROM, 2: RAM, 3: RTC)"},
	/* tr */ {IDCLS_ENABLE_INT_FUNC_ROM_TR, "Dahili Function ROM Tipi: (0: Yok, 1: ROM, 2: RAM, 3: RTC)"},
#endif
	
	/* c128/functionrom.c */
	/* en */ {IDCLS_DISABLE_INT_FUNC_ROM,    N_("Disable the internal Function ROM")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_INT_FUNC_ROM_DA, "DeaktivÈr intern funktions-ROM"},
	/* de */ {IDCLS_DISABLE_INT_FUNC_ROM_DE, "Internes Funktions ROM deaktivieren"},
	/* es */ {IDCLS_DISABLE_INT_FUNC_ROM_ES, "Deshabilitar ROM funciÛn interna"},
	/* fr */ {IDCLS_DISABLE_INT_FUNC_ROM_FR, "DÈsactiver l'image ROM des fonctions internes"},
	/* hu */ {IDCLS_DISABLE_INT_FUNC_ROM_HU, "Belsı Function ROM tilt·sa"},
	/* it */ {IDCLS_DISABLE_INT_FUNC_ROM_IT, "Disattiva la Function ROM interna"},
	/* ko */ {IDCLS_DISABLE_INT_FUNC_ROM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_INT_FUNC_ROM_NL, "De interne functie ROM uitschakelen"},
	/* pl */ {IDCLS_DISABLE_INT_FUNC_ROM_PL, "Wy≥±cz wewnÍtrzny Function ROM"},
	/* ru */ {IDCLS_DISABLE_INT_FUNC_ROM_RU, "Disable the internal Function ROM"},
	/* sv */ {IDCLS_DISABLE_INT_FUNC_ROM_SV, "Inaktivera internt funktions-ROM"},
	/* tr */ {IDCLS_DISABLE_INT_FUNC_ROM_TR, "Dahili Function ROM'u pasifle˛tir"},
#endif
	
	/* c128/functionrom.c */
	/* en */ {IDCLS_ENABLE_EXT_FUNC_ROM,    N_("Enable the external Function ROM")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_EXT_FUNC_ROM_DA, "AktivÈr extern funktions-ROM"},
	/* de */ {IDCLS_ENABLE_EXT_FUNC_ROM_DE, "Externes Funktions ROM aktivieren"},
	/* es */ {IDCLS_ENABLE_EXT_FUNC_ROM_ES, "Permitir ROM funciÛn externa"},
	/* fr */ {IDCLS_ENABLE_EXT_FUNC_ROM_FR, "Activer l'image ROM des fonctions externes"},
	/* hu */ {IDCLS_ENABLE_EXT_FUNC_ROM_HU, "K¸lsı Function ROM engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_EXT_FUNC_ROM_IT, "Attiva la Function ROM esterna"},
	/* ko */ {IDCLS_ENABLE_EXT_FUNC_ROM_KO, "ø‹∫Œ Function ROM ¿ª ªÁøÎ∞°¥…«œ∞‘ «œ±‚"},
	/* nl */ {IDCLS_ENABLE_EXT_FUNC_ROM_NL, "Activeer de externe functie ROM"},
	/* pl */ {IDCLS_ENABLE_EXT_FUNC_ROM_PL, "W≥±cz zewnÍtrzny Function ROM"},
	/* ru */ {IDCLS_ENABLE_EXT_FUNC_ROM_RU, "Enable the external Function ROM"},
	/* sv */ {IDCLS_ENABLE_EXT_FUNC_ROM_SV, "Aktivera externt funktions-ROM"},
	/* tr */ {IDCLS_ENABLE_EXT_FUNC_ROM_TR, "Harici Function ROM'u aktif et"},
#endif
	
	/* c128/functionrom.c */
	/* en */ {IDCLS_DISABLE_EXT_FUNC_ROM,    N_("Disable the external Function ROM")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_EXT_FUNC_ROM_DA, "DeaktivÈr extern funktions-ROM"},
	/* de */ {IDCLS_DISABLE_EXT_FUNC_ROM_DE, "Externes Funktions ROM deaktivieren"},
	/* es */ {IDCLS_DISABLE_EXT_FUNC_ROM_ES, "Deshabilitar ROM funciÛn externa"},
	/* fr */ {IDCLS_DISABLE_EXT_FUNC_ROM_FR, "DÈsactiver l'image ROM des fonctions externes"},
	/* hu */ {IDCLS_DISABLE_EXT_FUNC_ROM_HU, "K¸lsı Function ROM tilt·sa"},
	/* it */ {IDCLS_DISABLE_EXT_FUNC_ROM_IT, "Disattiva la Function ROM esterna"},
	/* ko */ {IDCLS_DISABLE_EXT_FUNC_ROM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_EXT_FUNC_ROM_NL, "De externe functie ROM uitschakelen"},
	/* pl */ {IDCLS_DISABLE_EXT_FUNC_ROM_PL, "Wy≥±cz zewnÍtrzny Function ROM"},
	/* ru */ {IDCLS_DISABLE_EXT_FUNC_ROM_RU, "Disable the external Function ROM"},
	/* sv */ {IDCLS_DISABLE_EXT_FUNC_ROM_SV, "Inaktivera externt funktions-ROM"},
	/* tr */ {IDCLS_DISABLE_EXT_FUNC_ROM_TR, "Harici Function ROM'u pasifle˛tir"},
#endif
	
	/* c64/c64-cmdline-options.c, c64/psid.c */
	/* en */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR,    N_("Use old NTSC sync factor")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_DA, "Anvend gammel NTSC-synkfaktor"},
	/* de */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_DE, "Alten NTSC Sync Faktor verwenden"},
	/* es */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_ES, "Usar antiguo factor de sincronizaciÛn NTSC"},
	/* fr */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_FR, "Utiliser l'ancien mode NTSC"},
	/* hu */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_HU, "RÈgi NTSC szinkron faktor haszn·lata"},
	/* it */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_IT, "Usa il vecchio fattore di sincronizzazione NTSC"},
	/* ko */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_NL, "Gebruik oude NTSC synchronisatiefactor"},
	/* pl */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_PL, "Uøywaj starej synchronizacji NTSC"},
	/* ru */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_RU, "Use old NTSC sync factor"},
	/* sv */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_SV, "Anv‰nd gammal NTSC-synkfaktor"},
	/* tr */ {IDCLS_USE_OLD_NTSC_SYNC_FACTOR_TR, "Eski NTSC senkron faktˆr¸ kullan"},
#endif
	
	/* c64/c64-cmdline-options.c, viciisc/vicii-cmdline-options.c */
	/* en */ {IDCLS_P_MODEL,    N_("<Model>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_MODEL_DA, "<Model>"},
	/* de */ {IDCLS_P_MODEL_DE, "<Modell>"},
	/* es */ {IDCLS_P_MODEL_ES, "<Modelo>"},
	/* fr */ {IDCLS_P_MODEL_FR, "<ModËle>"},
	/* hu */ {IDCLS_P_MODEL_HU, "<Modell>"},
	/* it */ {IDCLS_P_MODEL_IT, "<Modello>"},
	/* ko */ {IDCLS_P_MODEL_KO, "<∏µ®>"},
	/* nl */ {IDCLS_P_MODEL_NL, "<Model>"},
	/* pl */ {IDCLS_P_MODEL_PL, "<Model>"},
	/* ru */ {IDCLS_P_MODEL_RU, "<ºﬁ‘’€Ï>"},
	/* sv */ {IDCLS_P_MODEL_SV, "<Modell>"},
	/* tr */ {IDCLS_P_MODEL_TR, "<Model>"},
#endif
	
	/* c64/c64-cmdline-options.c */
	/* en */ {IDCLS_SET_BOTH_CIA_MODELS,    N_("Set both CIA models (0 = old 6526, 1 = new 6526A)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_BOTH_CIA_MODELS_DA, "VÊlg type for begge CIA-kredse (0=gammel 6526, 1=ny 6526A)"},
	/* de */ {IDCLS_SET_BOTH_CIA_MODELS_DE, "W‰hle beide CIA Modelle (0 = alt 6526, 1 = neu 6526A)"},
	/* es */ {IDCLS_SET_BOTH_CIA_MODELS_ES, "Seleccionar ambos modelos de CIA (0 = antiguo 6526, 1 = nuevo 6526A)"},
	/* fr */ {IDCLS_SET_BOTH_CIA_MODELS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_BOTH_CIA_MODELS_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_BOTH_CIA_MODELS_IT, "Imposta entrambi i modelli CIA (0 = 6526 vecchio, 1 = 6526A nuovo)"},
	/* ko */ {IDCLS_SET_BOTH_CIA_MODELS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_BOTH_CIA_MODELS_NL, "Zet model voor beide CIAs (0 = oud 6526, 1 = nieuw 6526A)"},
	/* pl */ {IDCLS_SET_BOTH_CIA_MODELS_PL, "Ustaw oba modele CIA (0 = stary 6526, 1 = nowy 6526A)"},
	/* ru */ {IDCLS_SET_BOTH_CIA_MODELS_RU, "Set both CIA models (0 = old 6526, 1 = new 6526A)"},
	/* sv */ {IDCLS_SET_BOTH_CIA_MODELS_SV, "V‰lj bÂda CIA-modellerna (0 = gammal 6526, 1 = ny 2526A)"},
	/* tr */ {IDCLS_SET_BOTH_CIA_MODELS_TR, "Her iki CIA modelini belirle (0 = eski 6526, 1 = yeni 6526A)"},
#endif
	
	/* c64/c64-cmdline-options.c */
	/* en */ {IDCLS_SET_CIA1_MODEL,    N_("Set CIA 1 model (0 = old 6526, 1 = new 6526A)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_CIA1_MODEL_DA, "VÊlg CIA 1 type (0=gammel 6526, 1=ny 6526A)"},
	/* de */ {IDCLS_SET_CIA1_MODEL_DE, "W‰hle CIA 1 Modell (0 = alt 6526, 1 = neu 6526A)"},
	/* es */ {IDCLS_SET_CIA1_MODEL_ES, "Seleccionar CIA 1 Poner CIA 1 model (0 = antiguo 6526, 1 = nuevo 6526A)"},
	/* fr */ {IDCLS_SET_CIA1_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_CIA1_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_CIA1_MODEL_IT, "Imposta modello CIA 1 (0 = 6526 vecchio, 1 = 6526A nuovo)"},
	/* ko */ {IDCLS_SET_CIA1_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_CIA1_MODEL_NL, "Zet CIA 1 model (0 = oud 6526, 1 = nieuw 6526A)"},
	/* pl */ {IDCLS_SET_CIA1_MODEL_PL, "Ustaw model CIA 1 (0 = stary 6526, 1 = nowy 6526A)"},
	/* ru */ {IDCLS_SET_CIA1_MODEL_RU, "Set CIA 1 model (0 = old 6526, 1 = new 6526A)"},
	/* sv */ {IDCLS_SET_CIA1_MODEL_SV, "V‰lj CIA 1-modell (0 = gammal 6526, 1 = ny 2526A)"},
	/* tr */ {IDCLS_SET_CIA1_MODEL_TR, "CIA 1 modelini belirle (0 = eski 6526, 1 = yeni 6526A)"},
#endif
	
	/* c64/c64-cmdline-options.c */
	/* en */ {IDCLS_SET_CIA2_MODEL,    N_("Set CIA 2 model (0 = old 6526, 1 = new 6526A)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_CIA2_MODEL_DA, "VÊlg CIA 2 type (0=gammel 6526, 1=ny 6526A)"},
	/* de */ {IDCLS_SET_CIA2_MODEL_DE, "W‰hle CIA 2 Modell (0 = alt 6526, 1 = neu 6526A)\""},
	/* es */ {IDCLS_SET_CIA2_MODEL_ES, "Seleccionar CIA 2 model (0 = antiguo 6526, 1 = nuevo 6526A)"},
	/* fr */ {IDCLS_SET_CIA2_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_CIA2_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_CIA2_MODEL_IT, "Imposta modello CIA 2 (0 = 6526 vecchio, 1 = 6526A nuovo)"},
	/* ko */ {IDCLS_SET_CIA2_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_CIA2_MODEL_NL, "Zet CIA 2 model (0 = oud 6526, 1 = nieuw 6526A)"},
	/* pl */ {IDCLS_SET_CIA2_MODEL_PL, "Ustaw model CIA 2 (0 = stary 6526, 1 = nowy 6526A)"},
	/* ru */ {IDCLS_SET_CIA2_MODEL_RU, "Set CIA 2 model (0 = old 6526, 1 = new 6526A)"},
	/* sv */ {IDCLS_SET_CIA2_MODEL_SV, "V‰lj CIA 2-modell (0 = gammal 6526, 1 = ny 2526A)"},
	/* tr */ {IDCLS_SET_CIA2_MODEL_TR, "CIA 2 modelini belirle (0 = eski 6526, 1 = yeni 6526A)"},
#endif
	
	/* c64/c64-cmdline-options.c */
	/* en */ {IDCLS_SET_C64_MODEL,    N_("Set C64 model (c64/c64c/c64old, ntsc/newntsc/oldntsc, drean)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_C64_MODEL_DA, "VÊlg C64 model (c64/c64c/c64old, ntsc/newntsc/oldntsc, drean)"},
	/* de */ {IDCLS_SET_C64_MODEL_DE, "W‰hle C64 Modell (c64/c64c/c64alt/c64ntsc/c64cntsc/c64oldntsc/drean)"},
	/* es */ {IDCLS_SET_C64_MODEL_ES, "Seleccionar modelo C64 (c64/c64c/c64antiguo, ntsc/nuevontsc/antiguontsc, drean)"},
	/* fr */ {IDCLS_SET_C64_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_C64_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_C64_MODEL_IT, "Imposta modello C64 (c64/c64c/c64old, ntsc/newntsc/oldntsc, drean)"},
	/* ko */ {IDCLS_SET_C64_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_C64_MODEL_NL, "Zet C64 model (c64/c64c/c64old, ntsc/newntsc/oldntsc, drean)"},
	/* pl */ {IDCLS_SET_C64_MODEL_PL, "Okre∂l model C64 (c64/c64c/c64old, ntsc/newntsc/oldntsc, drean)"},
	/* ru */ {IDCLS_SET_C64_MODEL_RU, "Set C64 model (c64/c64c/c64old, ntsc/newntsc/oldntsc, drean)"},
	/* sv */ {IDCLS_SET_C64_MODEL_SV, "V‰lj C64-modell (c64/c64c/c64old, ntsc/newntsc/oldntsc, drean)"},
	/* tr */ {IDCLS_SET_C64_MODEL_TR, "C64 modelini belirle (c64/c64c/c64eski, ntsc/yenintsc/eskintsc, drean)"},
#endif
	
	/* c128/c128-cmdline-options.c */
	/* en */ {IDCLS_SET_C128_MODEL,    N_("Set C128 model (c128/c128dcr, pal/ntsc)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_C128_MODEL_DA, "Angiv C128-model (c128/c128dcr, pal/ntsc)"},
	/* de */ {IDCLS_SET_C128_MODEL_DE, "W‰hle C128 Modell (c128/c128dcr, pal/ntsc)"},
	/* es */ {IDCLS_SET_C128_MODEL_ES, "Seleccionar modelo C128 (c128/c128dcr, pal/ntsc)"},
	/* fr */ {IDCLS_SET_C128_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_C128_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_C128_MODEL_IT, "Imposta modello C128 (c128/c128dcr, pal/ntsc)"},
	/* ko */ {IDCLS_SET_C128_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_C128_MODEL_NL, "Zet C128 model (c128/c128dcr, pal/ntsc)"},
	/* pl */ {IDCLS_SET_C128_MODEL_PL, "Ustaw model C128 (c128/c128dcr, pal/ntsc)"},
	/* ru */ {IDCLS_SET_C128_MODEL_RU, "Set C128 model (c128/c128dcr, pal/ntsc)"},
	/* sv */ {IDCLS_SET_C128_MODEL_SV, "V‰lj C128-modell (c128/c128dcr, pal/ntsc)"},
	/* tr */ {IDCLS_SET_C128_MODEL_TR, "C128 modelini belirle (c128/c128dcr, pal/ntsc)"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SET_PLUS4_MODEL,    N_("Set Plus4 model (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_PLUS4_MODEL_DA, "Angiv Plus4-modem (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* de */ {IDCLS_SET_PLUS4_MODEL_DE, "Setze Plus4 Modell (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* es */ {IDCLS_SET_PLUS4_MODEL_ES, "Seleccionar Plus4 model (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* fr */ {IDCLS_SET_PLUS4_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_PLUS4_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_PLUS4_MODEL_IT, "Imposta modello Plus4 (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* ko */ {IDCLS_SET_PLUS4_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_PLUS4_MODEL_NL, "Zet Plus4 model (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* pl */ {IDCLS_SET_PLUS4_MODEL_PL, "Ustaw model Plus4 (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* ru */ {IDCLS_SET_PLUS4_MODEL_RU, "Set Plus4 model (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* sv */ {IDCLS_SET_PLUS4_MODEL_SV, "V‰lj Plus4-modell (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
	/* tr */ {IDCLS_SET_PLUS4_MODEL_TR, "Plus4 modelini ayarla (c16/c16pal/c16ntsc, plus4/plus4pal/plus4ntsc, v364/cv364, c232)"},
#endif
	
	/* c64dtv/c64dtv-cmdline-options.c */
	/* en */ {IDCLS_SET_DTV_MODEL,    N_("Set DTV model (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DTV_MODEL_DA, "Angiv DTV-model (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* de */ {IDCLS_SET_DTV_MODEL_DE, "Setze DTV Modell (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* es */ {IDCLS_SET_DTV_MODEL_ES, "Seleccionar DTV model (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* fr */ {IDCLS_SET_DTV_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_DTV_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_DTV_MODEL_IT, "Imposta modello DTV (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* ko */ {IDCLS_SET_DTV_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DTV_MODEL_NL, "Zet DTV model (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* pl */ {IDCLS_SET_DTV_MODEL_PL, "Ustaw model DTV (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* ru */ {IDCLS_SET_DTV_MODEL_RU, "Set DTV model (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* sv */ {IDCLS_SET_DTV_MODEL_SV, "V‰lj DTV-modell (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
	/* tr */ {IDCLS_SET_DTV_MODEL_TR, "DTV modelini ayarla (v2/v2pal/v2ntsc, v3/v3pal/v3ntsc, hummer)"},
#endif
	
	/* c64/c64-cmdline-options.c, cbm2/cbm2-cmdline-options.c,
	 pet/pet-cmdline-options.c, plus4/plus4-cmdline-options.c,
	 vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_KERNAL_ROM_NAME,    N_("Specify name of Kernal ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_DA, "Angiv navn pÂ kernal-ROM-image"},
	/* de */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_DE, "Name von Kernal ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_ES, "Especificar nombre de la imagen ROM Kernal"},
	/* fr */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_FR, "SpÈcifier le nom de l'image ROM Kernal"},
	/* hu */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_HU, "Adja meg a Kernal ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_IT, "Specifica il nome immagine della ROM del Kernal"},
	/* ko */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_NL, "Geef de naam van het Kernal ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Kernala"},
	/* ru */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_RU, "Specify name of Kernal ROM image"},
	/* sv */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_SV, "Ange namn pÂ kernal-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_KERNAL_ROM_NAME_TR, "Kernal ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/c64-cmdline-options.c, cbm2/cbm2-cmdline-options.c,
	 pet/pet-cmdline-options.c, plus4/plus4-cmdline-options.c,
	 vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_BASIC_ROM_NAME,    N_("Specify name of BASIC ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_BASIC_ROM_NAME_DA, "Angiv navn pÂ BASIC-ROM-image"},
	/* de */ {IDCLS_SPECIFY_BASIC_ROM_NAME_DE, "Name von Basic ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_BASIC_ROM_NAME_ES, "Especificar nombre de la imagen ROM BASIC"},
	/* fr */ {IDCLS_SPECIFY_BASIC_ROM_NAME_FR, "SpÈcifier le nom de l'image BASIC ROM"},
	/* hu */ {IDCLS_SPECIFY_BASIC_ROM_NAME_HU, "Adja meg a BASIC ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_BASIC_ROM_NAME_IT, "Specifica il nome immagine della ROM del BASIC"},
	/* ko */ {IDCLS_SPECIFY_BASIC_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_BASIC_ROM_NAME_NL, "Geef de naam van het BASIC ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_BASIC_ROM_NAME_PL, "Okre∂l nazwÍ obrazu BASIC ROM"},
	/* ru */ {IDCLS_SPECIFY_BASIC_ROM_NAME_RU, "Specify name of BASIC ROM image"},
	/* sv */ {IDCLS_SPECIFY_BASIC_ROM_NAME_SV, "Ange namn pÂ BASIC-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_BASIC_ROM_NAME_TR, "BASIC ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/c64-cmdline-options.c, cbm2/cbm2-cmdline-options.c,
	 pet/pet-cmdline-options.c, vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME,    N_("Specify name of character generator ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_DA, "Angiv navn pÂ BASIC-ROM-image"},
	/* de */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_DE, "Name von Druckerausgabe Datei definieren (print.dump)"},
	/* es */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_ES, "Especificar el nombre de la imagen ROM generador de caracteres"},
	/* fr */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_FR, "SpÈcifier le nom de l'image du gÈnÈrateur de caractËres"},
	/* hu */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_HU, "Adja meg a karaktergener·tor ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_IT, "Specifica il nome della ROM del generatore di caratteri"},
	/* ko */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_NL, "Geef de naam van het CHARGEN ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM tworzenia znakÛw"},
	/* ru */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_RU, "Specify name of character generator ROM image"},
	/* sv */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_SV, "Ange namn pÂ teckengenerator-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_CHARGEN_ROM_NAME_TR, "Karakter Olu˛turucu ROM imaj˝n˝n ismini belirt"},
#endif
	
#ifdef COMMON_KBD
	/* c64/c64-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2,    N_("Specify index of keymap file (0=sym, 1=symDE, 2=pos)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_DA, "Angiv indeks for tastaturindstillingsfil (0=symbolsk, 1=symbolsk tysk, 2=positionsbestemt)"},
	/* de */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_DE, "Index f¸r Keymap Datei festlegen (0=symbol, 1=symDE, 2=positional)"},
	/* es */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_ES, "Especificar Ìndice fichero mapa teclado (0=sim, 1=simAL, 2=pos)"},
	/* fr */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_FR, "SpÈcifier l'index du fichier keymap (0=sym, 1=symDE, 2=pos)"},
	/* hu */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_HU, "Adja meg a billenty˚zet lekÈpzÈsi f·jl tÌpus·t (0=szimbolikus, 1=nÈmet szimbolikus, 2=pozÌciÛ szerinti)"},
	/* it */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_IT, "Specifica l'indice del file della mappa della tastiera (0=sim, 1=simGER, 2=pos)"},
	/* ko */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_NL, "Geef de index van het keymapbestand (0=sym, 1=symDE, 2=pos)"},
	/* pl */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_PL, "Podaj indeks dla uk≥adu klawiatury (0=symbol, 1=symbolDE, 2=pozycja)"},
	/* ru */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_RU, "Specify index of keymap file (0=sym, 1=symDE, 2=pos)"},
	/* sv */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_SV, "Ange index fˆr fˆr tangentbordsinst‰llningsfil (0=symbolisk, 1=symbolisk tysk, 2=positionsriktig)"},
	/* tr */ {IDCLS_SPECIFY_INDEX_KEYMAP_FILE_0_2_TR, "Tu˛ haritas˝ dosyas˝n˝n indeksini belirt (0=sembol, 1=sembol Almanca, 2=konumsal)"},
#endif
	
	/* c64/c64-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP,    N_("Specify name of symbolic German keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_DA, "Angiv fil for tysk symbolsk tastaturindstilling"},
	/* de */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_DE, "Name von symbolischer Keymap Datei definieren"},
	/* es */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_ES, "Especificar nombre del fichero teclado simbÛlico alem·n"},
	/* fr */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_FR, "SpÈcifier le nom du fichier symbolique de mappage clavier"},
	/* hu */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_HU, "Adja meg a nevÈt a nÈmet billenty˚zet lekÈpzÈs f·jlnak"},
	/* it */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_IT, "Specifica il nome del file della mappa simbolica della tastiera tedesca"},
	/* ko */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_NL, "Geef de naam van het symbolische Duitse keymapbestand"},
	/* pl */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_PL, "Okre∂l nazwÍ pliku symbolicznego niemieckiego uk≥adu klawiatury"},
	/* ru */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_RU, "Specify name of symbolic German keymap file"},
	/* sv */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_SV, "Ange fil fˆr tysk symbolisk tangentbordsemulering"},
	/* tr */ {IDCLS_SPECIFY_NAME_SYM_DE_KEYMAP_TR, "Sembolik Almanca tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
#endif
	
	/* c64/c64gluelogic.c */
	/* en */ {IDCLS_SET_GLUE_LOGIC_TYPE,    N_("Set glue logic type (0 = discrete, 1 = 252535-01)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_GLUE_LOGIC_TYPE_DA, "VÊlg glue logic type (0=diskret, 1=252535-01)"},
	/* de */ {IDCLS_SET_GLUE_LOGIC_TYPE_DE, "Setze Glue-Lokig Typ (0 = diskret, 1 = 252535-01)"},
	/* es */ {IDCLS_SET_GLUE_LOGIC_TYPE_ES, "Seleccionar tipo de 'glue' lÛgico (0 = discrete, 1 = 252535-01)"},
	/* fr */ {IDCLS_SET_GLUE_LOGIC_TYPE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_GLUE_LOGIC_TYPE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_GLUE_LOGIC_TYPE_IT, "Imposta il tipo di glue logic (0 = discreta, 1 = 252535-01)"},
	/* ko */ {IDCLS_SET_GLUE_LOGIC_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_GLUE_LOGIC_TYPE_NL, "Zet lijk logica soort (0 = discreet, 1 = 252535-01)"},
	/* pl */ {IDCLS_SET_GLUE_LOGIC_TYPE_PL, "Ustaw typ glue logic (0 = dyskretna, 1 = 252535-01)"},
	/* ru */ {IDCLS_SET_GLUE_LOGIC_TYPE_RU, "Set glue logic type (0 = discrete, 1 = 252535-01)"},
	/* sv */ {IDCLS_SET_GLUE_LOGIC_TYPE_SV, "V‰lj typ av klisterlogik (0 = diskret, 1 = 252535-01)"},
	/* tr */ {IDCLS_SET_GLUE_LOGIC_TYPE_TR, "Glue logic tipini ayarla (0 = balant˝y˝ kes, 1 = 252535-01)"},
#endif
	
	/* c64dtv/c64dtv-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_HUMMER_ADC,    N_("Enable Hummer ADC")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_HUMMER_ADC_DA, "AktivÈr Hummer ADC"},
	/* de */ {IDCLS_ENABLE_HUMMER_ADC_DE, "Hummer ADC Aktivieren"},
	/* es */ {IDCLS_ENABLE_HUMMER_ADC_ES, "Permitir Hummer ADC"},
	/* fr */ {IDCLS_ENABLE_HUMMER_ADC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_HUMMER_ADC_HU, "Hummer ADC engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_HUMMER_ADC_IT, "Attiva Hummer ADC"},
	/* ko */ {IDCLS_ENABLE_HUMMER_ADC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_HUMMER_ADC_NL, "Activeer Hummer ADC"},
	/* pl */ {IDCLS_ENABLE_HUMMER_ADC_PL, "W≥±cz Hummer ADC"},
	/* ru */ {IDCLS_ENABLE_HUMMER_ADC_RU, "Enable Hummer ADC"},
	/* sv */ {IDCLS_ENABLE_HUMMER_ADC_SV, "Aktivera Hummer-A/D-omvandlare"},
	/* tr */ {IDCLS_ENABLE_HUMMER_ADC_TR, "Hummer ADC'yi aktif et"},
#endif
	
	/* c64dtv/c64dtv-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_HUMMER_ADC,    N_("Disable Hummer ADC")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_HUMMER_ADC_DA, "DeaktivÈr Hummer ADC"},
	/* de */ {IDCLS_DISABLE_HUMMER_ADC_DE, "Hummer ADC deaktivieren"},
	/* es */ {IDCLS_DISABLE_HUMMER_ADC_ES, "Deshabilitar Hummer ADC"},
	/* fr */ {IDCLS_DISABLE_HUMMER_ADC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_HUMMER_ADC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_HUMMER_ADC_IT, "Disattiva Hummer ADC"},
	/* ko */ {IDCLS_DISABLE_HUMMER_ADC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_HUMMER_ADC_NL, "Hummer ADC uitschakelen"},
	/* pl */ {IDCLS_DISABLE_HUMMER_ADC_PL, "Wy≥±cz Hummer ADC"},
	/* ru */ {IDCLS_DISABLE_HUMMER_ADC_RU, "Disable Hummer ADC"},
	/* sv */ {IDCLS_DISABLE_HUMMER_ADC_SV, "Inaktivera Hummer-A/D-omvandlare"},
	/* tr */ {IDCLS_DISABLE_HUMMER_ADC_TR, "Hummer ADC'yi pasifle˛tir"},
#endif
	
	/* c64/c64io.c, vic20/vic20io.c */
	/* en */ {IDCLS_SELECT_CONFLICT_HANDLING,    N_("Select the way the I/O collisions should be handled, (0: error message and detach all involved carts, 1: error message and detach last attached involved carts, 2: warning in log and 'AND' the valid return values")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SELECT_CONFLICT_HANDLING_DA, "VÊlg hvordan I/O-kollisioner skal hÂndteres (0: fejlbesked og afbryd alle involverede cartridges, 1: fejlbesked og afbryd senest tilsluttede cartridge, 2: Advarsel i log og returner 'logisk OG' af de gyldige returvÊrdier)"},
	/* de */ {IDCLS_SELECT_CONFLICT_HANDLING_DE, "W‰hle, wie I/O Kollisionen behandelt werden sollen, (0: Fehler Meldung\nund Entfernen s‰mtlicher betroffener Module, 1: Fehler Meldung und\nEntfernen des letzten Moduls, 2: Warnung im Log und liefere logische\nUND-Verkn¸pfung g¸ltiger R¸ckgabewerte"},
	/* es */ {IDCLS_SELECT_CONFLICT_HANDLING_ES, "Seleccionar la forma en que las colisiones deben ser manejadas, (0: mensaje de error y desconectar todas los cartuchos involucrados, 1: mensaje de error y desconectar el ˙ltimo cartucho involucrado, 2: advertencia en  log y 'AND' los valores v·lidos de retorno"},
	/* fr */ {IDCLS_SELECT_CONFLICT_HANDLING_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SELECT_CONFLICT_HANDLING_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SELECT_CONFLICT_HANDLING_IT, "Seleziona come gestire le collisioni di I/O, (0: messaggio di errore e rimozione di tutte le cartucce coinvolte, 1: messaggio di errore e rimozione delle ultima cartucce coinvolte, 2: warning nei log e 'AND' il valore di ritorno valido"},
	/* ko */ {IDCLS_SELECT_CONFLICT_HANDLING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SELECT_CONFLICT_HANDLING_NL, "Selecteer de manier waarmee I/O conflicten worden afgehandeld, (0: fout melding en ontkoppel alle betroffene carridges, 1: fout melding en ontkoppel alle cartridges behalve de eerste cartrdige, 2: waarschuwing in het log bestand en doe een logische 'AND' met de terug gegeven waarden"},
	/* pl */ {IDCLS_SELECT_CONFLICT_HANDLING_PL, "Wybierz metodÍ obs≥ugi konfliktÛw we/wy, (0: komunikat b≥Ídu i od≥±czenie wszystkich konfliktuj±cych kartridøÛw, 1: komunikat b≥Ídu i od≥±czenie ostatnio pod≥±czonych konfliktuj±cych kartridøÛw, 2: ostrzeøenie w logu i 'AND' w≥a∂ciwe warto∂ci)"},
	/* ru */ {IDCLS_SELECT_CONFLICT_HANDLING_RU, "Select the way the I/O collisions should be handled, (0: error message and detach all involved carts, 1: error message and detach last attached involved carts, 2: warning in log and 'AND' the valid return values"},
	/* sv */ {IDCLS_SELECT_CONFLICT_HANDLING_SV, "V‰ljer hur I/O-kollisioner skall hanteras, (0: felmeddelande och koppla frÂn alla inblandade moduler, 1: felmeddelande och koppla frÂn sist anslutna inblandade modul, 2: varning i logg och logisk OCH pÂ giltiga returv‰rden)"},
	/* tr */ {IDCLS_SELECT_CONFLICT_HANDLING_TR, "G/« Áak˝˛malar˝n˝n deerlendirilme yˆntemini seÁ, (0: hata mesaj˝ ve t¸m ilgili cihazlar˝n Á˝kar˝lmas˝, 1: hata mesaj˝ ve en son tak˝lm˝˛ t¸m ilgili cihazlar˝n Á˝kar˝lmas˝, 2: log'a uyar˝ yaz˝lmas˝ ve geÁerli dˆn¸˛ deerlerinin 'VE'lenmesi"},
#endif
	
	/* c64/cart/c64tpi.c */
	/* en */ {IDCLS_ENABLE_IEEE488_INTERFACE,    N_("Enable the IEEE488 interface emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEEE488_INTERFACE_DA, "AktivÈr emulering af IEEE488-interface"},
	/* de */ {IDCLS_ENABLE_IEEE488_INTERFACE_DE, "IEEE488 Schnittstellen-Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_IEEE488_INTERFACE_ES, "Permitir emulaciÛn interface IEEE488"},
	/* fr */ {IDCLS_ENABLE_IEEE488_INTERFACE_FR, "Activer l'interface d'Èmulation IEEE488"},
	/* hu */ {IDCLS_ENABLE_IEEE488_INTERFACE_HU, "IEEE488 interfÈsz emul·ciÛ engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEEE488_INTERFACE_IT, "Attiva emulazione interfaccia IEEE488"},
	/* ko */ {IDCLS_ENABLE_IEEE488_INTERFACE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEEE488_INTERFACE_NL, "Activeer de IEEE488 interface emulatie"},
	/* pl */ {IDCLS_ENABLE_IEEE488_INTERFACE_PL, "W≥±cz emulacjÍ interfejsu IEEE488"},
	/* ru */ {IDCLS_ENABLE_IEEE488_INTERFACE_RU, "Enable the IEEE488 interface emulation"},
	/* sv */ {IDCLS_ENABLE_IEEE488_INTERFACE_SV, "Aktivera emulering av IEEE488-gr‰nssnitt"},
	/* tr */ {IDCLS_ENABLE_IEEE488_INTERFACE_TR, "IEEE488 arabirim em¸lasyonunu aktif et"},
#endif
	
	/* c64/cart/c64tpi.c */
	/* en */ {IDCLS_DISABLE_IEEE488_INTERFACE,    N_("Disable the IEEE488 interface emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEEE488_INTERFACE_DA, "DeaktivÈr emulering af IEEE488-interface"},
	/* de */ {IDCLS_DISABLE_IEEE488_INTERFACE_DE, "IEEE488 Schnittstellen-Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEEE488_INTERFACE_ES, "Deshabilitar emulaciÛn interface IEEE488"},
	/* fr */ {IDCLS_DISABLE_IEEE488_INTERFACE_FR, "DÈsactiver l'interface d'Èmulation IEEE488"},
	/* hu */ {IDCLS_DISABLE_IEEE488_INTERFACE_HU, "IEEE488 interfÈsz emul·ciÛ tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEEE488_INTERFACE_IT, "Disattiva emulazione interfaccia IEEE488"},
	/* ko */ {IDCLS_DISABLE_IEEE488_INTERFACE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEEE488_INTERFACE_NL, "De IEEE488 interface emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEEE488_INTERFACE_PL, "Wy≥±cz emulacjÍ interfejsu IEEE488"},
	/* ru */ {IDCLS_DISABLE_IEEE488_INTERFACE_RU, "Disable the IEEE488 interface emulation"},
	/* sv */ {IDCLS_DISABLE_IEEE488_INTERFACE_SV, "Inaktivera emulering av IEEE488-gr‰nssnitt"},
	/* tr */ {IDCLS_DISABLE_IEEE488_INTERFACE_TR, "IEEE488 arabirim em¸lasyonunu pasifle˛tir"},
#endif
	
	/* c64/cart/c64tpi.c */
	/* en */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME,    N_("specify IEEE488 interface image name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_DA, "angiv IEEE488-interface image navn"},
	/* de */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_DE, "IEEE488 Schnittstellenmodul Imagename"},
	/* es */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_ES, "Especificar nombre imagen interface IEEE488"},
	/* fr */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_IT, "specifica il nome immagine dell'interfaccia IEEE488"},
	/* ko */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_NL, "Geef de naam van het IEEE488 interface bestand"},
	/* pl */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_PL, "Okre∂l nazwÍ obrazu interfejsu IEEE488"},
	/* ru */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_RU, "specify IEEE488 interface image name"},
	/* sv */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_SV, "ange namn pÂ IEEE488-gr‰nssnittsfil"},
	/* tr */ {IDCLS_SPECIFY_IEEE488_INTERFACE_NAME_TR, "IEEE488 arabirimi imaj ismini belirleyin"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_ENABLE_GEORAM,    N_("Enable the GEO-RAM expansion unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_GEORAM_DA, "AktivÈr GEO-RAM-udviddelsesenheden"},
	/* de */ {IDCLS_ENABLE_GEORAM_DE, "GEO-RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_GEORAM_ES, "Permitir unidad expansiÛn GEO-RAM"},
	/* fr */ {IDCLS_ENABLE_GEORAM_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_GEORAM_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_GEORAM_IT, "Attiva l'espansione GEO-RAM"},
	/* ko */ {IDCLS_ENABLE_GEORAM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_GEORAM_NL, "Activeer de GEO-RAM uitbreidingseenheid"},
	/* pl */ {IDCLS_ENABLE_GEORAM_PL, "W≥±cz jednostkÍ rozszerzenia GEO-RAM"},
	/* ru */ {IDCLS_ENABLE_GEORAM_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_GEORAM_SV, "Aktivera GEORAM-expansionsenhet"},
	/* tr */ {IDCLS_ENABLE_GEORAM_TR, "GEO-RAM geni˛letme birimini aktif et"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_DISABLE_GEORAM,    N_("Disable the GEO-RAM expansion unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_GEORAM_DA, "DeaktivÈr GEO-RAM-udviddelsesenhed"},
	/* de */ {IDCLS_DISABLE_GEORAM_DE, "GEO-RAM Erweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_GEORAM_ES, "Deshabilitar unidad expansiÛn GEO-RAM"},
	/* fr */ {IDCLS_DISABLE_GEORAM_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_GEORAM_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_GEORAM_IT, "Disattiva l'espansione GEO-RAM"},
	/* ko */ {IDCLS_DISABLE_GEORAM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_GEORAM_NL, "De GEO-RAM uitbreidingseenheid uitschakelen"},
	/* pl */ {IDCLS_DISABLE_GEORAM_PL, "Wy≥±cz jednostkÍ rozszerzenia GEO-RAM"},
	/* ru */ {IDCLS_DISABLE_GEORAM_RU, "¿–·Ëÿ‡’›ÿ’ ﬂ–‹Ô‚ÿ GEORAM"},
	/* sv */ {IDCLS_DISABLE_GEORAM_SV, "Inaktivera GEO RAM-expansionsenhet"},
	/* tr */ {IDCLS_DISABLE_GEORAM_TR, "GEO-RAM geni˛letme birimini pasifle˛tir"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_SPECIFY_GEORAM_NAME,    N_("Specify name of GEORAM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_GEORAM_NAME_DA, "Angiv navn pÂ GEORAM-image"},
	/* de */ {IDCLS_SPECIFY_GEORAM_NAME_DE, "GEORAM Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_GEORAM_NAME_ES, "Especificar nombre imagen GEORAM"},
	/* fr */ {IDCLS_SPECIFY_GEORAM_NAME_FR, "SpÈcifier le nom de l'image GEORAM"},
	/* hu */ {IDCLS_SPECIFY_GEORAM_NAME_HU, "Adja meg a GEORAM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_GEORAM_NAME_IT, "Specifica il nome immagine GEORAM"},
	/* ko */ {IDCLS_SPECIFY_GEORAM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_GEORAM_NAME_NL, "Geef de naam van het GEORAM bestand"},
	/* pl */ {IDCLS_SPECIFY_GEORAM_NAME_PL, "Okre∂l nazwÍ obrazu GEORAM"},
	/* ru */ {IDCLS_SPECIFY_GEORAM_NAME_RU, "Specify name of GEORAM image"},
	/* sv */ {IDCLS_SPECIFY_GEORAM_NAME_SV, "Ange namn pÂ GEORAM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_GEORAM_NAME_TR, "GEORAM imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE,    N_("Allow writing to GEORAM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_DA, "Tillad skrivning til GEORAM-image."},
	/* de */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_DE, "Schreibzugriff auf GEORAM Image erlauben"},
	/* es */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_ES, "Permitir grabaciÛn sobre imagen GEORAM"},
	/* fr */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_IT, "Attiva la scrittura su immagine GEORAM"},
	/* ko */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_NL, "Aktiveer schrijven naar GEORAM bestand"},
	/* pl */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_PL, "PozwÛl na zapis do obrazu GEORAM"},
	/* ru */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_RU, "Allow writing to GEORAM image"},
	/* sv */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_SV, "TillÂt skrivning till GEORAM-avbildning"},
	/* tr */ {IDCLS_ALLOW_WRITING_TO_GEORAM_IMAGE_TR, "GEORAM imaj˝na yazmay˝ aktif et"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE,    N_("Do not write to GEORAM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_DA, "Skriv ikke til GEORAM-image"},
	/* de */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_DE, "Kein Schreibzugriff auf GEORAM Image"},
	/* es */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_ES, "No grabar en imagen GEORAM"},
	/* fr */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_IT, "Disattiva la scrittura su immagine GEORAM"},
	/* ko */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_NL, "Schrijf niet naar GEORAM bestand"},
	/* pl */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_PL, "Nie zapisuj do obrazu GEORAM"},
	/* ru */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_RU, "Do not write to GEORAM image"},
	/* sv */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_SV, "Skriv inte till GEORAM-avbildning"},
	/* tr */ {IDCLS_DO_NOT_WRITE_TO_GEORAM_IMAGE_TR, "GEORAM imaj˝na yazma"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_SWAP_CART_IO,    N_("Swap io mapping (map cart I/O-1 to VIC20 I/O-3 and cart I/O-2 to VIC20 I/O-2)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SWAP_CART_IO_DA, "Ombyt I/O-forbindelse (forbind cart I/O-1 til VIC20 I/O-3 og cart I/O-2 til VIC20 I/O-2)"},
	/* de */ {IDCLS_SWAP_CART_IO_DE, "Vertausche IO Zuordnung (cart I/O-1 auf VIC20 I/O-3 und cart I/O-2 auf VIC20 I/O-2)"},
	/* es */ {IDCLS_SWAP_CART_IO_ES, "Intercambiar mapeado IO (map cart I/O-1 to VIC20 I/O-3 and cart I/O-2 to VIC20 I/O-2)"},
	/* fr */ {IDCLS_SWAP_CART_IO_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SWAP_CART_IO_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SWAP_CART_IO_IT, "Scambia mapping di I/O (mappa I/O-1 cart su I/O-3 VIC20 e I/O-2 cart su I/O-2 VIC20)"},
	/* ko */ {IDCLS_SWAP_CART_IO_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SWAP_CART_IO_NL, "Verwissel de io toewijzing (verwijs cart I/O-1 naar VIC20 I/O-3 en cart I/O-2 naar VIC20 I/O-2)"},
	/* pl */ {IDCLS_SWAP_CART_IO_PL, "ZamieÒ mapowanie we/wy (mapuj  we/wy-1  kartridøa do we/wy-3 VIC20 i we/wy-2 kartidøa do we/wy-2 VIC20)"},
	/* ru */ {IDCLS_SWAP_CART_IO_RU, "Swap io mapping (map cart I/O-1 to VIC20 I/O-3 and cart I/O-2 to VIC20 I/O-2)"},
	/* sv */ {IDCLS_SWAP_CART_IO_SV, "V‰xla io-mappning (mappa modul-I/O 1 till VIC20-I/O 3 och modul-I/O 2 till VIC20-I/O 2)"},
	/* tr */ {IDCLS_SWAP_CART_IO_TR, "G/« haritalamas˝n˝ yer dei˛tir (harita kart˝ G/«-1 ile VIC20 G/«-3 ve kart G/«-2 ile VIC20 G/«-2)"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_DONT_SWAP_CART_IO,    N_("Don't swap io mapping (map cart I/O-1 to VIC20 I/O-2 and cart I/O-2 to VIC20 I/O-3)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_SWAP_CART_IO_DA, "Ombyt ikke I/O-forbindelse (forbind cart I/O-1 til VIC20 I/O-2 og cart I/O-2 til VIC20 I/O-3)"},
	/* de */ {IDCLS_DONT_SWAP_CART_IO_DE, "Keine Vertauschung der IO Zuordnung (cart I/O-1 auf VIC20 I/O-2 und cart I/O-2 auf VIC20 I/O-3)"},
	/* es */ {IDCLS_DONT_SWAP_CART_IO_ES, "No intercambiar mapeado IO (map cart I/O-1 to VIC20 I/O-2 and cart I/O-2 to VIC20 I/O-3)"},
	/* fr */ {IDCLS_DONT_SWAP_CART_IO_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DONT_SWAP_CART_IO_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DONT_SWAP_CART_IO_IT, "Non scambiare mapping di I/O (mappa I/O-1 cart su I/O-2 VIC20 e I/O-2 cart su I/O-3 VIC20)"},
	/* ko */ {IDCLS_DONT_SWAP_CART_IO_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_SWAP_CART_IO_NL, "Verwissel de io toewijzing niet (verwijs cart I/O-1 naar VIC20 I/O-2 en cart I/O-2 naar VIC20 I/O-3)"},
	/* pl */ {IDCLS_DONT_SWAP_CART_IO_PL, "Nie zamieniaj mapowania we/wy (mapuj  we/wy-1  kartridøa do we/wy-2 VIC20 i we/wy-2 kartidøa do we/wy-3 VIC20)"},
	/* ru */ {IDCLS_DONT_SWAP_CART_IO_RU, "Don't swap io mapping (map cart I/O-1 to VIC20 I/O-2 and cart I/O-2 to VIC20 I/O-3)"},
	/* sv */ {IDCLS_DONT_SWAP_CART_IO_SV, "V‰xla inte io-mappning (mappa modul-I/O 1 till VIC20-I/O 2 och modul-I/O 2 till VIC20-I/O 3)"},
	/* tr */ {IDCLS_DONT_SWAP_CART_IO_TR, "G/« haritalamas˝n˝ yer dei˛tirme (harita kart˝ G/«-1 ile VIC20 G/«-2 ve kart G/«-2 ile VIC20 G/«-3)"},
#endif
	
	/* c64/cart/sfx_soundexpander.c, c64/cart/sfx_soundsampler.c,
	 c64/cart/tfe.c */
	/* en */ {IDCLS_MAP_CART_IO_2,    N_("Swap io mapping (map cart I/O to VIC20 I/O-2)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MAP_CART_IO_2_DA, "Ombyt I/O-forbindelse (forbind cart I/O til VIC20 I/O-2)"},
	/* de */ {IDCLS_MAP_CART_IO_2_DE, "Vertasuche IO Zuordnung (cart I/O auf VIC20 I/O-2)"},
	/* es */ {IDCLS_MAP_CART_IO_2_ES, "Intercambiar mapeado IO (map cart I/O to VIC20 I/O-2)"},
	/* fr */ {IDCLS_MAP_CART_IO_2_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MAP_CART_IO_2_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MAP_CART_IO_2_IT, "Scambia mapping di I/O (mappa I/O cart su I/O-2 VIC20)"},
	/* ko */ {IDCLS_MAP_CART_IO_2_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MAP_CART_IO_2_NL, "Verwissel de io toewijzing (verwijs cart I/O naar VIC20 I/O-2)"},
	/* pl */ {IDCLS_MAP_CART_IO_2_PL, "ZamieÒ mapowanie we/wy (mapuj  we/wy  kartridøa do we/wy-2 VIC20)"},
	/* ru */ {IDCLS_MAP_CART_IO_2_RU, "Swap io mapping (map cart I/O to VIC20 I/O-2)"},
	/* sv */ {IDCLS_MAP_CART_IO_2_SV, "V‰xla io-mappning (mappa modul-I/O till VIC20-I/O 2)"},
	/* tr */ {IDCLS_MAP_CART_IO_2_TR, "G/« haritalamas˝n˝ yer dei˛tir (harita kart˝ G/« ile VIC20 G/«-2)"},
#endif
	
	/* c64/cart/sfx_soundexpander.c, c64/cart/sfx_soundsampler.c,
	 c64/cart/tfe.c */
	/* en */ {IDCLS_MAP_CART_IO_3,    N_("Don't swap io mapping (map cart I/O to VIC20 I/O-3)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MAP_CART_IO_3_DA, "Ombyt ikke I/O-forbindelse (forbind cart I/O til VIC20 I/O-3)"},
	/* de */ {IDCLS_MAP_CART_IO_3_DE, "Keine Vertauschung der IO Zuordnung (cart I/O auf VIC20 I/O-3)"},
	/* es */ {IDCLS_MAP_CART_IO_3_ES, "No intercambia mapeado IO (map cart I/O to VIC20 I/O-3)"},
	/* fr */ {IDCLS_MAP_CART_IO_3_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MAP_CART_IO_3_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MAP_CART_IO_3_IT, "Non scambiare mapping di I/O (mappa I/O cart su I/O-3 VIC20)"},
	/* ko */ {IDCLS_MAP_CART_IO_3_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MAP_CART_IO_3_NL, "Verwissel de io toewijzing niet (verwijs cart I/O naar VIC20 I/O-3)"},
	/* pl */ {IDCLS_MAP_CART_IO_3_PL, "Nie zamieniaj mapowania we/wy (mapuj  we/wy  kartridøa do we/wy-3 VIC20)"},
	/* ru */ {IDCLS_MAP_CART_IO_3_RU, "Don't swap io mapping (map cart I/O to VIC20 I/O-3)"},
	/* sv */ {IDCLS_MAP_CART_IO_3_SV, "V‰xla io-mappning (mappa modul-I/O till VIC20-I/O 3)"},
	/* tr */ {IDCLS_MAP_CART_IO_3_TR, "G/« haritalamas˝n˝ yer dei˛tirme (harita kart˝ G/« ile VIC20 G/«-3)"},
#endif
	
	/* c64/cart/georam.c, c64/cart/ramcart.c, c64/cart/reu.c, pet/petreu.c */
	/* en */ {IDCLS_P_SIZE_IN_KB,    N_("<size in KB>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_SIZE_IN_KB_DA, "<st¯rrelse i kB>"},
	/* de */ {IDCLS_P_SIZE_IN_KB_DE, "<Grˆﬂe in KB>"},
	/* es */ {IDCLS_P_SIZE_IN_KB_ES, "<tamaÒo en KB>"},
	/* fr */ {IDCLS_P_SIZE_IN_KB_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_SIZE_IN_KB_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_SIZE_IN_KB_IT, "<dimensione in KB>"},
	/* ko */ {IDCLS_P_SIZE_IN_KB_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_SIZE_IN_KB_NL, "<grootte in KB>"},
	/* pl */ {IDCLS_P_SIZE_IN_KB_PL, "<rozmiar w KB>"},
	/* ru */ {IDCLS_P_SIZE_IN_KB_RU, "<‡–◊‹’‡ “ ∫±>"},
	/* sv */ {IDCLS_P_SIZE_IN_KB_SV, "<storlek i KB>"},
	/* tr */ {IDCLS_P_SIZE_IN_KB_TR, "<KB cinsinden boyut>"},
#endif
	
	/* c64/cart/georam.c */
	/* en */ {IDCLS_GEORAM_SIZE,    N_("Size of the GEORAM expansion unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_GEORAM_SIZE_DA, "St¯rrelse af GEORAM-udviddelsesenhed"},
	/* de */ {IDCLS_GEORAM_SIZE_DE, "Grˆﬂe der GEORAM Erweiterung"},
	/* es */ {IDCLS_GEORAM_SIZE_ES, "TamaÒo de la unidad expansiÛn GEORAM"},
	/* fr */ {IDCLS_GEORAM_SIZE_FR, "Taille de l'unitÈ d'expansion GEORAM"},
	/* hu */ {IDCLS_GEORAM_SIZE_HU, "GEORAM Expansion Unit mÈrete"},
	/* it */ {IDCLS_GEORAM_SIZE_IT, "Dimensione dell'espansione GEORAM"},
	/* ko */ {IDCLS_GEORAM_SIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_GEORAM_SIZE_NL, "Grootte van de GEORAM uitbreidingseenheid"},
	/* pl */ {IDCLS_GEORAM_SIZE_PL, "Rozmiar jednostki rozszerzenia GEORAM"},
	/* ru */ {IDCLS_GEORAM_SIZE_RU, "Size of the GEORAM expansion unit"},
	/* sv */ {IDCLS_GEORAM_SIZE_SV, "Storlek pÂ GEORAM-expansionsenhet"},
	/* tr */ {IDCLS_GEORAM_SIZE_TR, "GEORAM geni˛letme biriminin boyutu"},
#endif
	
	/* pet/petreu.c */
	/* en */ {IDCLS_ENABLE_PETREU,    N_("Enable the PET Ram and Expansion Unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_PETREU_DA, "AktivÈr PET REU"},
	/* de */ {IDCLS_ENABLE_PETREU_DE, "PET RAM Speicher und Erweiterungsmodul aktivieren"},
	/* es */ {IDCLS_ENABLE_PETREU_ES, "Permitir PET ram y Unidad ExpansiÛn"},
	/* fr */ {IDCLS_ENABLE_PETREU_FR, "Activer l'expansion d'unitÈ et de RAM du PET"},
	/* hu */ {IDCLS_ENABLE_PETREU_HU, "PET RAM and Expansion Unit engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_PETREU_IT, "Attiva la RAM e l'unit‡ di espansione del PET"},
	/* ko */ {IDCLS_ENABLE_PETREU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_PETREU_NL, "Activeer de PET RAM en uitbreidingseenheid"},
	/* pl */ {IDCLS_ENABLE_PETREU_PL, "W≥±cz PET Ram i Expansion Unit"},
	/* ru */ {IDCLS_ENABLE_PETREU_RU, "Enable the PET Ram and Expansion Unit"},
	/* sv */ {IDCLS_ENABLE_PETREU_SV, "Aktivera PET Ram- och -expansionsenhet"},
	/* tr */ {IDCLS_ENABLE_PETREU_TR, "PET Ram ve Geni˛letme Birimi'ni aktif et"},
#endif
	
	/* pet/petreu.c */
	/* en */ {IDCLS_DISABLE_PETREU,    N_("Disable the PET Ram and Expansion Unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_PETREU_DA, "DeaktivÈr PET REU"},
	/* de */ {IDCLS_DISABLE_PETREU_DE, "PET RAM Speicher und Erweiterungsmodul dektivieren"},
	/* es */ {IDCLS_DISABLE_PETREU_ES, "Deshabilitar PET RAM y Unidad ExpansiÛn"},
	/* fr */ {IDCLS_DISABLE_PETREU_FR, "DÈsactiver l'expansion d'unitÈ et de RAM du PET"},
	/* hu */ {IDCLS_DISABLE_PETREU_HU, "PET RAM and Expansion Unit tilt·sa"},
	/* it */ {IDCLS_DISABLE_PETREU_IT, "Disattiva la RAM e l'unit‡ di espansione del PET"},
	/* ko */ {IDCLS_DISABLE_PETREU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_PETREU_NL, "De PET RAM en uitbreidingseenheid uitschakelen"},
	/* pl */ {IDCLS_DISABLE_PETREU_PL, "Wy≥±cz PET Ram i Expansion Unit"},
	/* ru */ {IDCLS_DISABLE_PETREU_RU, "Disable the PET Ram and Expansion Unit"},
	/* sv */ {IDCLS_DISABLE_PETREU_SV, "Inaktivera PET Ram- och -expansionsenhet"},
	/* tr */ {IDCLS_DISABLE_PETREU_TR, "PET Ram ve Geni˛letme Birimi'ni pasifle˛tir"},
#endif
	
	/* pet/petreu.c */
	/* en */ {IDCLS_SPECIFY_PETREU_NAME,    N_("Specify name of PET Ram and Expansion Unit image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PETREU_NAME_DA, "Angiv navn pÂ PET REU-image"},
	/* de */ {IDCLS_SPECIFY_PETREU_NAME_DE, "Namen f¸r PET RAM Speicher und Erweiterungsmodul definieren"},
	/* es */ {IDCLS_SPECIFY_PETREU_NAME_ES, "Especificar nombre imagen PET Ram y Unidad ExpansiÛn"},
	/* fr */ {IDCLS_SPECIFY_PETREU_NAME_FR, "SpÈcifier le nom de l'image díunitÈ d'expansion RAM"},
	/* hu */ {IDCLS_SPECIFY_PETREU_NAME_HU, "Adja meg a PET RAM and Expansion Unit kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_PETREU_NAME_IT, "Specifica il nome immagine della RAM e dell'unit‡ di espansione del PET"},
	/* ko */ {IDCLS_SPECIFY_PETREU_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PETREU_NAME_NL, "Geef de naam van het PET RAM en uitbreidingseenheid bestand"},
	/* pl */ {IDCLS_SPECIFY_PETREU_NAME_PL, "Okre∂l nazwÍ obrazu PET Ram i Expansion Unit"},
	/* ru */ {IDCLS_SPECIFY_PETREU_NAME_RU, "Specify name of PET Ram and Expansion Unit image"},
	/* sv */ {IDCLS_SPECIFY_PETREU_NAME_SV, "Ange namn pÂ PET Ram- och -expansionsenhet"},
	/* tr */ {IDCLS_SPECIFY_PETREU_NAME_TR, "PET Ram ve Geni˛letme Birimi'nin ismini belirt"},
#endif
	
	/* pet/petreu.c */
	/* en */ {IDCLS_PETREU_SIZE,    N_("Size of the PET Ram and Expansion Unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PETREU_SIZE_DA, "St¯rrelse pÂ PET REU"},
	/* de */ {IDCLS_PETREU_SIZE_DE, "Grˆﬂe des PET RAM Speicher und Erweiterungsmodul"},
	/* es */ {IDCLS_PETREU_SIZE_ES, "TamaÒo de PET Ram y Unidad ExpansiÛn"},
	/* fr */ {IDCLS_PETREU_SIZE_FR, "Taille de l'unitÈ d'expansion RAM"},
	/* hu */ {IDCLS_PETREU_SIZE_HU, "PET RAM and Expansion Unit mÈrete"},
	/* it */ {IDCLS_PETREU_SIZE_IT, "Dimensione della RAM e dell'unit‡ di espansione del PET"},
	/* ko */ {IDCLS_PETREU_SIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PETREU_SIZE_NL, "Grootte van de PET RAM en uitbreidingseenheid"},
	/* pl */ {IDCLS_PETREU_SIZE_PL, "Rozmiar PET Ram i Expansion Unit"},
	/* ru */ {IDCLS_PETREU_SIZE_RU, "Size of the PET Ram and Expansion Unit"},
	/* sv */ {IDCLS_PETREU_SIZE_SV, "Storlek pÂ PET Ram- och -expansionsenhet"},
	/* tr */ {IDCLS_PETREU_SIZE_TR, "PET Ram ve Geni˛letme Birimi'nin boyutu"},
#endif
	
	/* pet/petdww.c */
	/* en */ {IDCLS_SPECIFY_PETDWW_NAME,    N_("Specify name of PET DWW image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PETDWW_NAME_DA, "Angiv navn pÂ PET DWW-image"},
	/* de */ {IDCLS_SPECIFY_PETDWW_NAME_DE, "Namen f¸r PET DWW Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_PETDWW_NAME_ES, "Especificar nombre imagen PET DWW"},
	/* fr */ {IDCLS_SPECIFY_PETDWW_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_PETDWW_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_PETDWW_NAME_IT, "Specifica il nome immagine PET DWW"},
	/* ko */ {IDCLS_SPECIFY_PETDWW_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PETDWW_NAME_NL, "Geef de naam van het PET DWW bestand"},
	/* pl */ {IDCLS_SPECIFY_PETDWW_NAME_PL, "Okre∂l nazwÍ obrazu PET DWW"},
	/* ru */ {IDCLS_SPECIFY_PETDWW_NAME_RU, "Specify name of PET DWW image"},
	/* sv */ {IDCLS_SPECIFY_PETDWW_NAME_SV, "Ange namn pÂ PET DWW-avbildning"},
	/* tr */ {IDCLS_SPECIFY_PETDWW_NAME_TR, "PET DWW imaj˝n˝n ismini belirt"},
#endif
	
	/* pet/petdww.c */
	/* en */ {IDCLS_ENABLE_PETDWW,    N_("Enable the PET DWW hi-res board")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_PETDWW_DA, "AktivÈr PET DWW h¯jopl¯sningskort"},
	/* de */ {IDCLS_ENABLE_PETDWW_DE, "PET DWW hi-res Karte aktivieren"},
	/* es */ {IDCLS_ENABLE_PETDWW_ES, "Permitir tablero de alta resoluciÛn PET DWW"},
	/* fr */ {IDCLS_ENABLE_PETDWW_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_PETDWW_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_PETDWW_IT, "Attiva la scheda hi-res PET DWW"},
	/* ko */ {IDCLS_ENABLE_PETDWW_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_PETDWW_NL, "Activeer het PET DWW hi-res bord"},
	/* pl */ {IDCLS_ENABLE_PETDWW_PL, "W≥±cz uk≥ad PET DWW hi-res"},
	/* ru */ {IDCLS_ENABLE_PETDWW_RU, "Enable the PET DWW hi-res board"},
	/* sv */ {IDCLS_ENABLE_PETDWW_SV, "Aktivera PET DWW-hˆgupplˆsningskort"},
	/* tr */ {IDCLS_ENABLE_PETDWW_TR, "PET DWW hi-res boardunu aktif et"},
#endif
	
	/* pet/petdww.c */
	/* en */ {IDCLS_DISABLE_PETDWW,    N_("Disable the PET DWW hi-res board")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_PETDWW_DA, "DeaktivÈr PET DWW h¯jopl¯sningskort"},
	/* de */ {IDCLS_DISABLE_PETDWW_DE, "PET DWW Hi-Res Karte deaktivieren"},
	/* es */ {IDCLS_DISABLE_PETDWW_ES, "Deshabilitar tablero de alta resoluciÛn PET DWW"},
	/* fr */ {IDCLS_DISABLE_PETDWW_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_PETDWW_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_PETDWW_IT, "Disattiva la scheda hi-res PET DWW"},
	/* ko */ {IDCLS_DISABLE_PETDWW_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_PETDWW_NL, "Het PET DWW hi-res bord uitschakelen"},
	/* pl */ {IDCLS_DISABLE_PETDWW_PL, "Wy≥±cz p≥ytÍ PET DWW hi-res"},
	/* ru */ {IDCLS_DISABLE_PETDWW_RU, "Disable the PET DWW hi-res board"},
	/* sv */ {IDCLS_DISABLE_PETDWW_SV, "Inaktivera PET DWW-hˆgupplˆsningskort"},
	/* tr */ {IDCLS_DISABLE_PETDWW_TR, "PET DWW hi-res boardu pasifle˛tir"},
#endif
	
	/* userport/userport_dac.c */
	/* en */ {IDCLS_ENABLE_USERPORT_DAC,    N_("Enable Userport DAC for sound output")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_USERPORT_DAC_DA, "AktivÈr brugerport DAC for lydoutput"},
	/* de */ {IDCLS_ENABLE_USERPORT_DAC_DE, "Userport DAC Sound aktivieren"},
	/* es */ {IDCLS_ENABLE_USERPORT_DAC_ES, "Permitir puerto DAC para salida de sonido"},
	/* fr */ {IDCLS_ENABLE_USERPORT_DAC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_USERPORT_DAC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_USERPORT_DAC_IT, "Attiva DAC su userport per la riproduzione audio"},
	/* ko */ {IDCLS_ENABLE_USERPORT_DAC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_USERPORT_DAC_NL, "Activeer userport DAC voor geluidsuitvoer"},
	/* pl */ {IDCLS_ENABLE_USERPORT_DAC_PL, "W≥±cz userport DAC jako wyj∂cie dºwiÍku"},
	/* ru */ {IDCLS_ENABLE_USERPORT_DAC_RU, "Enable Userport DAC for sound output"},
	/* sv */ {IDCLS_ENABLE_USERPORT_DAC_SV, "Aktivera D/A-omvandlare pÂ anv‰ndarporten fˆr ljudutdata"},
	/* tr */ {IDCLS_ENABLE_USERPORT_DAC_TR, "Ses Á˝k˝˛˝ iÁin Userport DAC'˝ aktif et"},
#endif
	
	/* userport/userport_dac.c */
	/* en */ {IDCLS_DISABLE_USERPORT_DAC,    N_("Disable Userport DAC for sound output")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_USERPORT_DAC_DA, "DeaktivÈr brugerport DAC for lydoutput"},
	/* de */ {IDCLS_DISABLE_USERPORT_DAC_DE, "Userport DAC Sound deaktivieren"},
	/* es */ {IDCLS_DISABLE_USERPORT_DAC_ES, "Deshabilitar puerto DAC para salida de sonido"},
	/* fr */ {IDCLS_DISABLE_USERPORT_DAC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_USERPORT_DAC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_USERPORT_DAC_IT, "Disattiva DAC su userport per la riproduzione audio"},
	/* ko */ {IDCLS_DISABLE_USERPORT_DAC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_USERPORT_DAC_NL, "Userport DAC voor geluidsuitvoer uitschakelen"},
	/* pl */ {IDCLS_DISABLE_USERPORT_DAC_PL, "Wy≥±cz userport DAC jako wy∂cie dºwiÍku"},
	/* ru */ {IDCLS_DISABLE_USERPORT_DAC_RU, "Disable Userport DAC for sound output"},
	/* sv */ {IDCLS_DISABLE_USERPORT_DAC_SV, "Inaktivera D/A-omvandlare pÂ anv‰ndarporten fˆr ljudutdata"},
	/* tr */ {IDCLS_DISABLE_USERPORT_DAC_TR, "Ses Á˝k˝˛˝ iÁin Userport DAC'˝ pasifle˛tir"},
#endif
	
	/* userport/userport_rtc.c */
	/* en */ {IDCLS_ENABLE_USERPORT_RTC,    N_("Enable Userport DAC for sound output")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_USERPORT_RTC_DA, "AktivÈr brugerport DAC for lydoutput"},
	/* de */ {IDCLS_ENABLE_USERPORT_RTC_DE, "Userport DAC Sound aktivieren"},
	/* es */ {IDCLS_ENABLE_USERPORT_RTC_ES, "Permitir puerto DAC para salida de sonido"},
	/* fr */ {IDCLS_ENABLE_USERPORT_RTC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_USERPORT_RTC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_USERPORT_RTC_IT, "Attiva DAC su userport per la riproduzione audio"},
	/* ko */ {IDCLS_ENABLE_USERPORT_RTC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_USERPORT_RTC_NL, "Activeer userport DAC voor geluidsuitvoer"},
	/* pl */ {IDCLS_ENABLE_USERPORT_RTC_PL, "W≥±cz userport DAC jako wyj∂cie dºwiÍku"},
	/* ru */ {IDCLS_ENABLE_USERPORT_RTC_RU, "Enable Userport DAC for sound output"},
	/* sv */ {IDCLS_ENABLE_USERPORT_RTC_SV, "Aktivera D/A-omvandlare pÂ anv‰ndarporten fˆr ljudutdata"},
	/* tr */ {IDCLS_ENABLE_USERPORT_RTC_TR, "Ses Á˝k˝˛˝ iÁin Userport DAC'˝ aktif et"},
#endif
	
	/* userport/userport_rtc.c */
	/* en */ {IDCLS_DISABLE_USERPORT_RTC,    N_("Disable Userport DAC for sound output")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_USERPORT_RTC_DA, "DeaktivÈr brugerport DAC for lydoutput"},
	/* de */ {IDCLS_DISABLE_USERPORT_RTC_DE, "Userport DAC Sound deaktivieren"},
	/* es */ {IDCLS_DISABLE_USERPORT_RTC_ES, "Deshabilitar puerto DAC para salida de sonido"},
	/* fr */ {IDCLS_DISABLE_USERPORT_RTC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_USERPORT_RTC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_USERPORT_RTC_IT, "Disattiva DAC su userport per la riproduzione audio"},
	/* ko */ {IDCLS_DISABLE_USERPORT_RTC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_USERPORT_RTC_NL, "Userport DAC voor geluidsuitvoer uitschakelen"},
	/* pl */ {IDCLS_DISABLE_USERPORT_RTC_PL, "Wy≥±cz userport DAC jako wy∂cie dºwiÍku"},
	/* ru */ {IDCLS_DISABLE_USERPORT_RTC_RU, "Disable Userport DAC for sound output"},
	/* sv */ {IDCLS_DISABLE_USERPORT_RTC_SV, "Inaktivera D/A-omvandlare pÂ anv‰ndarporten fˆr ljudutdata"},
	/* tr */ {IDCLS_DISABLE_USERPORT_RTC_TR, "Ses Á˝k˝˛˝ iÁin Userport DAC'˝ pasifle˛tir"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_SID_PLAYER_MODE,    N_("SID player mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SID_PLAYER_MODE_DA, "SID-afspiller tilstand"},
	/* de */ {IDCLS_SID_PLAYER_MODE_DE, "SID Player Modus"},
	/* es */ {IDCLS_SID_PLAYER_MODE_ES, "Modo SID player"},
	/* fr */ {IDCLS_SID_PLAYER_MODE_FR, "Mode jukebox SID"},
	/* hu */ {IDCLS_SID_PLAYER_MODE_HU, "SID lej·tszÛ mÛd"},
	/* it */ {IDCLS_SID_PLAYER_MODE_IT, "Modalit‡ del SID player"},
	/* ko */ {IDCLS_SID_PLAYER_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SID_PLAYER_MODE_NL, "SID playermodus"},
	/* pl */ {IDCLS_SID_PLAYER_MODE_PL, "Tryb odtwarzacza SID"},
	/* ru */ {IDCLS_SID_PLAYER_MODE_RU, "SID player mode"},
	/* sv */ {IDCLS_SID_PLAYER_MODE_SV, "SID-spelarl‰ge"},
	/* tr */ {IDCLS_SID_PLAYER_MODE_TR, "SID Áalar modu"},
#endif
	
	/* c64/psid.c */
	/* en */ {IDCLS_OVERWRITE_PSID_SETTINGS,    N_("Override PSID settings for Video standard and SID model")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_OVERWRITE_PSID_SETTINGS_DA, "Overstyr PSID-indstillinger for Video-standard og SID-model"},
	/* de */ {IDCLS_OVERWRITE_PSID_SETTINGS_DE, "PSID Einstellung f¸r Video Standard und SID Modell ver‰ndern"},
	/* es */ {IDCLS_OVERWRITE_PSID_SETTINGS_ES, "Sobreescrivir ajustes para video standard y modelo SID"},
	/* fr */ {IDCLS_OVERWRITE_PSID_SETTINGS_FR, "…craser les paramËtres PSID pour le standard vidÈo et le modËle SID"},
	/* hu */ {IDCLS_OVERWRITE_PSID_SETTINGS_HU, "A videÛ szabv·ny Ès a SID modell PSID be·llÌt·sainak fel¸lbÌr·l·sa"},
	/* it */ {IDCLS_OVERWRITE_PSID_SETTINGS_IT, "Non tener conto delle impostazioni del PSID per lo standard video e il modello di SID"},
	/* ko */ {IDCLS_OVERWRITE_PSID_SETTINGS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_OVERWRITE_PSID_SETTINGS_NL, "Overschrijf PSID instellingen voor videostandaard en SID model"},
	/* pl */ {IDCLS_OVERWRITE_PSID_SETTINGS_PL, "Zast±p ustawienia PSID standardu wideo i modelu SID"},
	/* ru */ {IDCLS_OVERWRITE_PSID_SETTINGS_RU, "Override PSID settings for Video standard and SID model"},
	/* sv */ {IDCLS_OVERWRITE_PSID_SETTINGS_SV, "Ers‰tt PSID-inst‰llningar fˆr videostandard och SID-modell"},
	/* tr */ {IDCLS_OVERWRITE_PSID_SETTINGS_TR, "Video standard˝ ve SID modeli iÁin PSID ayarlar˝n˝ geÁersiz k˝l"},
#endif
	
	/* c64/psid.c */
	/* en */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER,    N_("Specify PSID tune <number>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_DA, "VÊlg PSID-nummer <nummer>"},
	/* de */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_DE, "PSID St¸ck <Nummer> definieren"},
	/* es */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_ES, "Especificar PSID tono <n˙mero>"},
	/* fr */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_FR, "SpÈcifier le <numero> de piste PSID"},
	/* hu */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_HU, "Adja meg a PSID hangzatok <sz·m>"},
	/* it */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_IT, "Specifica la melodia <numero> del PSID"},
	/* ko */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_NL, "Geef PSID deuntje <nummer>"},
	/* pl */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_PL, "Okre∂l ton PSID <numer>"},
	/* ru */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_RU, "Specify PSID tune <number>"},
	/* sv */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_SV, "Ange PSID-lÂt <nummer>"},
	/* tr */ {IDCLS_SPECIFY_PSID_TUNE_NUMBER_TR, "PSID parÁa <numara>'s˝n˝ belirt"},
#endif
	
	/* c64/cart/ramcart.c */
	/* en */ {IDCLS_ENABLE_RAMCART,    N_("Enable the RamCart expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RAMCART_DA, "AktivÈr RamCart-udviddelsen"},
	/* de */ {IDCLS_ENABLE_RAMCART_DE, "RamCart Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_RAMCART_ES, "Permitir expansiÛn RAMCART"},
	/* fr */ {IDCLS_ENABLE_RAMCART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_RAMCART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_RAMCART_IT, "Attiva l'espansione RamCart"},
	/* ko */ {IDCLS_ENABLE_RAMCART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RAMCART_NL, "Activeer de RamCart uitbreiding"},
	/* pl */ {IDCLS_ENABLE_RAMCART_PL, "W≥±cz rozszerzenie RamCart"},
	/* ru */ {IDCLS_ENABLE_RAMCART_RU, "Enable the RamCart expansion"},
	/* sv */ {IDCLS_ENABLE_RAMCART_SV, "Aktivera RamCart-expansion"},
	/* tr */ {IDCLS_ENABLE_RAMCART_TR, "RamCart geni˛lemesini aktif et"},
#endif
	
	/* c64/cart/ramcart.c */
	/* en */ {IDCLS_DISABLE_RAMCART,    N_("Disable the RamCart expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RAMCART_DA, "DeaktivÈr RamCart-udviddelse"},
	/* de */ {IDCLS_DISABLE_RAMCART_DE, "RamCart Erweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_RAMCART_ES, "Deshabilitar expansiÛn RamCart"},
	/* fr */ {IDCLS_DISABLE_RAMCART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_RAMCART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_RAMCART_IT, "Disattiva l'espansione RamCart"},
	/* ko */ {IDCLS_DISABLE_RAMCART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RAMCART_NL, "De RamCart uitbreiding uitschakelen"},
	/* pl */ {IDCLS_DISABLE_RAMCART_PL, "Wy≥±cz rozszerzenie RamCart"},
	/* ru */ {IDCLS_DISABLE_RAMCART_RU, "Disable the RamCart expansion"},
	/* sv */ {IDCLS_DISABLE_RAMCART_SV, "Inaktivera RamCart-expansion"},
	/* tr */ {IDCLS_DISABLE_RAMCART_TR, "RamCart geni˛lemesini pasifle˛tir"},
#endif
	
	/* c64/cart/ramcart.c */
	/* en */ {IDCLS_SPECIFY_RAMCART_NAME,    N_("Specify name of RAMCART image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RAMCART_NAME_DA, "Angiv navn pÂ RAMCART-image"},
	/* de */ {IDCLS_SPECIFY_RAMCART_NAME_DE, "Name f¸r RAMCART Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_RAMCART_NAME_ES, "Especificar nombre imagen RAMCART"},
	/* fr */ {IDCLS_SPECIFY_RAMCART_NAME_FR, "SpÈcifier le nom de l'image RAMCART"},
	/* hu */ {IDCLS_SPECIFY_RAMCART_NAME_HU, "Adja meg a RAMCART kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_RAMCART_NAME_IT, "Specifica il nome immagine RAMCART"},
	/* ko */ {IDCLS_SPECIFY_RAMCART_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RAMCART_NAME_NL, "Geef de naam van het RAMCART bestand"},
	/* pl */ {IDCLS_SPECIFY_RAMCART_NAME_PL, "Okre∂l nazwÍ obrazu RAMCART"},
	/* ru */ {IDCLS_SPECIFY_RAMCART_NAME_RU, "Specify name of RAMCART image"},
	/* sv */ {IDCLS_SPECIFY_RAMCART_NAME_SV, "Ange namn pÂ RAMCART-avbildning"},
	/* tr */ {IDCLS_SPECIFY_RAMCART_NAME_TR, "RAMCART imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/cart/ramcart.c */
	/* en */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE,    N_("Allow writing to RAMCart image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_DA, "Tillad skrivning til RAMCart-image."},
	/* de */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_DE, "Schreibzugriff auf RAMCart Image erlauben"},
	/* es */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_ES, "Permitir grabar en imagen RAMCart"},
	/* fr */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_IT, "Attiva scrittura su immagine RAMCart"},
	/* ko */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_NL, "Aktiveer schrijven naar RAMCart bestand"},
	/* pl */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_PL, "PozwÛl na zapis do obrazu RAMCart"},
	/* ru */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_RU, "Allow writing to RAMCart image"},
	/* sv */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_SV, "TillÂt skrivning till RAMCart-avbildning"},
	/* tr */ {IDCLS_ALLOW_WRITING_TO_RAMCART_IMAGE_TR, "RAMCart imaj˝na yazmay˝ aktif et"},
#endif
	
	/* c64/cart/ramcart.c */
	/* en */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE,    N_("Do not write to RAMCart image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_DA, "Skriv ikke til RAMcart-image"},
	/* de */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_DE, "Kein Schreibzugriff auf RAMCart Image"},
	/* es */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_ES, "No permitir grabar en imagen RAMCart"},
	/* fr */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_IT, "Disattiva scrittura su immagine RAMCart"},
	/* ko */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_NL, "Schrijf niet naar RAMCart bestand"},
	/* pl */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_PL, "Nie zapisuj do obrazu RAMCart"},
	/* ru */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_RU, "Do not write to RAMCart image"},
	/* sv */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_SV, "Skriv inte till RAMCart-avbildning"},
	/* tr */ {IDCLS_DO_NOT_WRITE_TO_RAMCART_IMAGE_TR, "RAMCart imaj˝na yazma"},
#endif
	
	/* c64/cart/ramcart.c */
	/* en */ {IDCLS_RAMCART_SIZE,    N_("Size of the RAMCART expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RAMCART_SIZE_DA, "St¯rrelse pÂ RAMCART-udviddelse"},
	/* de */ {IDCLS_RAMCART_SIZE_DE, "Grˆﬂe der RAMCART Erweiterung"},
	/* es */ {IDCLS_RAMCART_SIZE_ES, "TamaÒo expansiÛn RAMCart"},
	/* fr */ {IDCLS_RAMCART_SIZE_FR, "Taille de l'expansion RAMCART"},
	/* hu */ {IDCLS_RAMCART_SIZE_HU, "RAMCART bıvÌtÈs mÈrete"},
	/* it */ {IDCLS_RAMCART_SIZE_IT, "Dimensione dell'espansione RAMCART"},
	/* ko */ {IDCLS_RAMCART_SIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_RAMCART_SIZE_NL, "Grootte van de RAMCART uitbreiding"},
	/* pl */ {IDCLS_RAMCART_SIZE_PL, "Rozmiar rozszerzenia RAMCART"},
	/* ru */ {IDCLS_RAMCART_SIZE_RU, "Size of the RAMCART expansion"},
	/* sv */ {IDCLS_RAMCART_SIZE_SV, "Storlek pÂ RAMCART-expansion"},
	/* tr */ {IDCLS_RAMCART_SIZE_TR, "RAMCART geni˛lemesinin boyutu"},
#endif
	
	/* c64/cart/dqbb.c */
	/* en */ {IDCLS_ENABLE_DQBB,    N_("Enable Double Quick Brown Box")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DQBB_DA, "AktivÈr Double Quick Brown Box"},
	/* de */ {IDCLS_ENABLE_DQBB_DE, "Double Quick Brown Box aktivieren"},
	/* es */ {IDCLS_ENABLE_DQBB_ES, "Permitir Double Quick Brown Box"},
	/* fr */ {IDCLS_ENABLE_DQBB_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DQBB_HU, "Double Quick Brown Box engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_DQBB_IT, "Attiva Double Quick Brown Box"},
	/* ko */ {IDCLS_ENABLE_DQBB_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DQBB_NL, "Activeer de Double Quick Brown Box cartridge"},
	/* pl */ {IDCLS_ENABLE_DQBB_PL, "W≥±cz Double Quick Brown Box"},
	/* ru */ {IDCLS_ENABLE_DQBB_RU, "Enable Double Quick Brown Box"},
	/* sv */ {IDCLS_ENABLE_DQBB_SV, "Aktivera Double Quick Brown Box"},
	/* tr */ {IDCLS_ENABLE_DQBB_TR, "Double Quick Brown Box'˝ aktif et"},
#endif
	
	/* c64/cart/dqbb.c */
	/* en */ {IDCLS_DISABLE_DQBB,    N_("Disable Double Quick Brown Box")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DQBB_DA, "DeaktivÈr Double Quick Brown Box"},
	/* de */ {IDCLS_DISABLE_DQBB_DE, "Double Quick Brown Box Modul deaktivieren"},
	/* es */ {IDCLS_DISABLE_DQBB_ES, "Deshabilitar Double Quick Brown Box"},
	/* fr */ {IDCLS_DISABLE_DQBB_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DQBB_HU, "Double Quick Brown Box tilt·sa"},
	/* it */ {IDCLS_DISABLE_DQBB_IT, "Disattiva Double Quick Brown Box"},
	/* ko */ {IDCLS_DISABLE_DQBB_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DQBB_NL, "De Double Quick Brown Box cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DQBB_PL, "Wy≥±cz Double Quick Brown Box"},
	/* ru */ {IDCLS_DISABLE_DQBB_RU, "Disable Double Quick Brown Box"},
	/* sv */ {IDCLS_DISABLE_DQBB_SV, "Inaktivera Double Quick Brown Box"},
	/* tr */ {IDCLS_DISABLE_DQBB_TR, "Double Quick Brown Box'˝ pasifle˛tir"},
#endif
	
	/* c64/cart/dqbb.c */
	/* en */ {IDCLS_SPECIFY_DQBB_NAME,    N_("Specify Double Quick Brown Box filename")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_DQBB_NAME_DA, "Angiv filnavn for Double Quick Brown Box"},
	/* de */ {IDCLS_SPECIFY_DQBB_NAME_DE, "Double Quick Brown Box Dateiname spezifizieren"},
	/* es */ {IDCLS_SPECIFY_DQBB_NAME_ES, "Especificar fichero imagen Double Quick Brown Box"},
	/* fr */ {IDCLS_SPECIFY_DQBB_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_DQBB_NAME_HU, "Adja meg a Double Quick Brown Box f·jlnevet"},
	/* it */ {IDCLS_SPECIFY_DQBB_NAME_IT, "Specifica il nome del file Double Quick Brown Box"},
	/* ko */ {IDCLS_SPECIFY_DQBB_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_DQBB_NAME_NL, "Geef de naam van het Double Quick Brown Box cartridge bestand"},
	/* pl */ {IDCLS_SPECIFY_DQBB_NAME_PL, "Okre∂l nazwÍ pliku Double Quick Brown Box"},
	/* ru */ {IDCLS_SPECIFY_DQBB_NAME_RU, "Specify Double Quick Brown Box filename"},
	/* sv */ {IDCLS_SPECIFY_DQBB_NAME_SV, "Ange filnamn fˆr Double Quick Brown Box"},
	/* tr */ {IDCLS_SPECIFY_DQBB_NAME_TR, "Double Quick Brown Box dosya ismi belirt"},
#endif
	
	/* c64/cart/dqbb.c */
	/* en */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE,    N_("Allow writing to DQBB image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_DA, "Tillad skrivning til DQBB-image."},
	/* de */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_DE, "Schreibzugriff auf DQBB Image erlauben"},
	/* es */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_ES, "Permitir grabaciÛn en imagen DQBB "},
	/* fr */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_IT, "Attiva scrittura su immagine DQBB"},
	/* ko */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_NL, "Aktiveer schrijven naar DQBB bestand"},
	/* pl */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_PL, "PozwÛl na zapis do obrazu DQBB"},
	/* ru */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_RU, "Allow writing to DQBB image"},
	/* sv */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_SV, "TillÂt skrivning till DQBB-avbildning"},
	/* tr */ {IDCLS_ALLOW_WRITING_TO_DQBB_IMAGE_TR, "DQBB imaj˝na yazmay˝ aktif et"},
#endif
	
	/* c64/cart/dqbb.c */
	/* en */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE,    N_("Do not write to DQBB image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_DA, "Skriv ikke til DQBB-image"},
	/* de */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_DE, "Kein Schreibzugriff auf DQBB Image"},
	/* es */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_ES, "No permitir grabaciÛn en imagen DQBB "},
	/* fr */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_IT, "Disattiva scrittura su immagine DQBB"},
	/* ko */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_NL, "Schrijf niet naar DQBB bestand"},
	/* pl */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_PL, "Nie zapisuj do obrazu DQBB"},
	/* ru */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_RU, "Do not write to DQBB image"},
	/* sv */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_SV, "Skriv inte till DQBB-avbildning"},
	/* tr */ {IDCLS_DO_NOT_WRITE_TO_DQBB_IMAGE_TR, "DQBB imaj˝na yazma"},
#endif
	
	/* c64/cart/isepic.c */
	/* en */ {IDCLS_ENABLE_ISEPIC,    N_("Enable the ISEPIC cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_ISEPIC_DA, "AktivÈr ISEPIC-cartridge"},
	/* de */ {IDCLS_ENABLE_ISEPIC_DE, "ISEPIC Modul aktivieren"},
	/* es */ {IDCLS_ENABLE_ISEPIC_ES, "Permitir cartucho ISEPIC"},
	/* fr */ {IDCLS_ENABLE_ISEPIC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_ISEPIC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_ISEPIC_IT, "Attiva la cartuccia ISEPIC"},
	/* ko */ {IDCLS_ENABLE_ISEPIC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_ISEPIC_NL, "*Activeer de ISEPIC cartridge"},
	/* pl */ {IDCLS_ENABLE_ISEPIC_PL, "W≥±cz kartridø ISEPIC"},
	/* ru */ {IDCLS_ENABLE_ISEPIC_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_ISEPIC_SV, "Aktivera ISEPIC-modul"},
	/* tr */ {IDCLS_ENABLE_ISEPIC_TR, "ISEPIC kartu˛unu aktif et"},
#endif
	
	/* c64/cart/isepic.c */
	/* en */ {IDCLS_DISABLE_ISEPIC,    N_("Disable the ISEPIC cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_ISEPIC_DA, "DeaktivÈr ISEPIC-cartridget"},
	/* de */ {IDCLS_DISABLE_ISEPIC_DE, "ISEPIC Modul deaktivieren"},
	/* es */ {IDCLS_DISABLE_ISEPIC_ES, "Deshabilitar cartucho ISEPIC"},
	/* fr */ {IDCLS_DISABLE_ISEPIC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_ISEPIC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_ISEPIC_IT, "Disattiva la cartuccia ISEPIC"},
	/* ko */ {IDCLS_DISABLE_ISEPIC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_ISEPIC_NL, "De ISEPIC cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_ISEPIC_PL, "Wy≥±cz kartridø ISEPIC"},
	/* ru */ {IDCLS_DISABLE_ISEPIC_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_ISEPIC_SV, "Inaktivera ISEPIC-modul"},
	/* tr */ {IDCLS_DISABLE_ISEPIC_TR, "ISEPIC kartu˛unu pasifle˛tir"},
#endif
	
	/* c64/cart/isepic.c */
	/* en */ {IDCLS_SET_ISEPIC_FILENAME,    N_("Set ISEPIC image name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_ISEPIC_FILENAME_DA, "VÊlg ISEPIC image-navn"},
	/* de */ {IDCLS_SET_ISEPIC_FILENAME_DE, "ISEPIC Imagedateiname setzen"},
	/* es */ {IDCLS_SET_ISEPIC_FILENAME_ES, "Seleccionar nombre imagen ISEPIC"},
	/* fr */ {IDCLS_SET_ISEPIC_FILENAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_ISEPIC_FILENAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_ISEPIC_FILENAME_IT, "Imposta nome immagine ISEPIC"},
	/* ko */ {IDCLS_SET_ISEPIC_FILENAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_ISEPIC_FILENAME_NL, "Geef de naam op van het ISEPIC cartridge bestand"},
	/* pl */ {IDCLS_SET_ISEPIC_FILENAME_PL, "Okre∂l nazwÍ obrazu ISEPIC"},
	/* ru */ {IDCLS_SET_ISEPIC_FILENAME_RU, "Set ISEPIC image name"},
	/* sv */ {IDCLS_SET_ISEPIC_FILENAME_SV, "Namn pÂ ISEPIC-avbildning"},
	/* tr */ {IDCLS_SET_ISEPIC_FILENAME_TR, "ISEPIC imaj ismini belirle"},
#endif
	
	/* c64/cart/isepic.c */
	/* en */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE,    N_("Allow writing to ISEPIC image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_DA, "Tillad skrivning til ISEPIC-image"},
	/* de */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_DE, "Schreibzugriff auf ISEPIC Image erlauben"},
	/* es */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_ES, "Permitir grabaciÛn en imagen ISEPIC"},
	/* fr */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_IT, "Attiva scrittura su immagine ISEPIC"},
	/* ko */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_NL, "Aktiveer schrijven naar ISEPIC bestand"},
	/* pl */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_PL, "PozwÛl na zapis do obrazu ISEPIC"},
	/* ru */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_RU, "Allow writing to ISEPIC image"},
	/* sv */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_SV, "TillÂt skrivning till ISEPIC-avbildning"},
	/* tr */ {IDCLS_ALLOW_WRITING_TO_ISEPIC_IMAGE_TR, "ISEPIC imaj˝na yazmay˝ aktif et"},
#endif
	
	/* c64/cart/isepic.c */
	/* en */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE,    N_("Do not write to ISEPIC image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_DA, "Skriv ikke til ISEPIC-image"},
	/* de */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_DE, "Kein Schreibzugriff auf ISEPIC Image"},
	/* es */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_ES, "No permitir grabaciÛn en imagen ISEPIC"},
	/* fr */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_IT, "Disattiva scrittura su immagine ISEPIC"},
	/* ko */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_NL, "Schrijf niet naar ISEPIC bestand"},
	/* pl */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_PL, "Nie zapisuj do obrazu ISEPIC"},
	/* ru */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_RU, "Do not write to ISEPIC image"},
	/* sv */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_SV, "Skriv inte till ISEPIC-avbildning"},
	/* tr */ {IDCLS_DO_NOT_WRITE_TO_ISEPIC_IMAGE_TR, "ISEPIC imaj˝na yazma"},
#endif
	
	/* c64/cart/mmc64.c */
	/* en */ {IDCLS_ENABLE_MMC64,    N_("Enable the MMC64 expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_MMC64_DA, "AktivÈr MMC64-udviddelse"},
	/* de */ {IDCLS_ENABLE_MMC64_DE, "MMC64 Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_MMC64_ES, "Permitir expansiÛn MMC64"},
	/* fr */ {IDCLS_ENABLE_MMC64_FR, "Activer l'expansion MMC64"},
	/* hu */ {IDCLS_ENABLE_MMC64_HU, "MMC64 bıvÌtÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_MMC64_IT, "Attiva l'espansione MMC64"},
	/* ko */ {IDCLS_ENABLE_MMC64_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_MMC64_NL, "Activeer de MMC64 uitbreiding"},
	/* pl */ {IDCLS_ENABLE_MMC64_PL, "W≥±cz rozszerzenie MMC64"},
	/* ru */ {IDCLS_ENABLE_MMC64_RU, "Enable the MMC64 expansion"},
	/* sv */ {IDCLS_ENABLE_MMC64_SV, "Aktivera MMC64-expansion"},
	/* tr */ {IDCLS_ENABLE_MMC64_TR, "MMC64 geni˛lemesini aktif et"},
#endif
	
	/* c64/cart/mmc64.c */
	/* en */ {IDCLS_DISABLE_MMC64,    N_("Disable the MMC64 expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_MMC64_DA, "DeaktivÈr MMC64-udviddelse"},
	/* de */ {IDCLS_DISABLE_MMC64_DE, "MMC64 Erweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_MMC64_ES, "Deshabilitar expansiÛn MMC64"},
	/* fr */ {IDCLS_DISABLE_MMC64_FR, "DÈsactiver l'expansion MMC64"},
	/* hu */ {IDCLS_DISABLE_MMC64_HU, "MMC64 bıvÌtÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_MMC64_IT, "Disattiva l'espansione MMC64"},
	/* ko */ {IDCLS_DISABLE_MMC64_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_MMC64_NL, "De MMC64 uitbreiding uitschakelen"},
	/* pl */ {IDCLS_DISABLE_MMC64_PL, "Wy≥±cz rozszerzenie MMC64"},
	/* ru */ {IDCLS_DISABLE_MMC64_RU, "Disable the MMC64 expansion"},
	/* sv */ {IDCLS_DISABLE_MMC64_SV, "Inaktivera MMC64-expansion"},
	/* tr */ {IDCLS_DISABLE_MMC64_TR, "MMC64 geni˛lemesini pasifle˛tir"},
#endif
	
	/* c64/cart/mmc64.c */
	/* en */ {IDCLS_SPECIFY_MMC64_BIOS_NAME,    N_("Specify name of MMC64 BIOS image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_DA, "Angiv navn pÂ MMC64-BIOS-image"},
	/* de */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_DE, "Name f¸r MMC64 BIOS Datei spezifizieren"},
	/* es */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_ES, "Especificar nombre imagen BIOS MMC64"},
	/* fr */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_FR, "SpÈcifier le nom de l'image MMC64 BIOS"},
	/* hu */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_HU, "Adja meg az MMC64 BIOS kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_IT, "Specifica il nome immagine del BIOS MMC64"},
	/* ko */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_NL, "Geef de naam van het MMC64 BIOS bestand"},
	/* pl */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_PL, "Okre∂l nazwÍ obrazu BIOS MMC64"},
	/* ru */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_RU, "Specify name of MMC64 BIOS image"},
	/* sv */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_SV, "Ange namn pÂ MMC64-BIOS-avbildning"},
	/* tr */ {IDCLS_SPECIFY_MMC64_BIOS_NAME_TR, "MMC64 BIOS imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/cart/mmc64.c */
	/* en */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME,    N_("Specify name of MMC64 image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_DA, "Angiv navn pÂ MMC64-image"},
	/* de */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_DE, "Name der MMC64 Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_ES, "Especificar nombre imagen MMC64"},
	/* fr */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_FR, "SpÈcifier le nom de l'image MMC64"},
	/* hu */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_HU, "Adja meg az MMC64 kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_IT, "Specifica il nome immagine MMC64"},
	/* ko */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_NL, "Geef de naam van het MMC64 bestand"},
	/* pl */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_PL, "Okre∂l nazwÍ obrazu MMC64"},
	/* ru */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_RU, "Specify name of MMC64 image"},
	/* sv */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_SV, "Ange namn pÂ MMC64-avbildning"},
	/* tr */ {IDCLS_SPECIFY_MMC64_IMAGE_NAME_TR, "MMC64 imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/cart/mmc64.c */
	/* en */ {IDCLS_MMC64_READONLY,    N_("Set the MMC64 card to read-only")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC64_READONLY_DA, "Skrivebeskyt MMC64-kort"},
	/* de */ {IDCLS_MMC64_READONLY_DE, "MMC64 Karte Schreibschutz"},
	/* es */ {IDCLS_MMC64_READONLY_ES, "Seleccionar tarjeta MMC64 en modo sÛlo lectura"},
	/* fr */ {IDCLS_MMC64_READONLY_FR, "DÈfinir la carte MMC64 en lecture seule"},
	/* hu */ {IDCLS_MMC64_READONLY_HU, "MMC64 k·rtya csak olvashatÛ"},
	/* it */ {IDCLS_MMC64_READONLY_IT, "Imposta la card MMC64 in sola lettura"},
	/* ko */ {IDCLS_MMC64_READONLY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC64_READONLY_NL, "Zet de MMC64 als alleen-lezen"},
	/* pl */ {IDCLS_MMC64_READONLY_PL, "Ustaw kartÍ MMC64 na tryb tylko do odczytu"},
	/* ru */ {IDCLS_MMC64_READONLY_RU, "Set the MMC64 card to read-only"},
	/* sv */ {IDCLS_MMC64_READONLY_SV, "Skrivskydda MMC64-kort"},
	/* tr */ {IDCLS_MMC64_READONLY_TR, "MMC64 kart˝n˝ salt okunura Áevir"},
#endif
	
	/* c64/cart/mmc64.c */
	/* en */ {IDCLS_MMC64_READWRITE,    N_("Set the MMC64 card to read/write")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC64_READWRITE_DA, "Tillad skrivning pÂ MMC64-kort"},
	/* de */ {IDCLS_MMC64_READWRITE_DE, "MMC64 Karte Schreibzugriff"},
	/* es */ {IDCLS_MMC64_READWRITE_ES, "Seleccionar tarjeta MMC64 en modo lectura/grabaciÛn"},
	/* fr */ {IDCLS_MMC64_READWRITE_FR, "DÈfinir la carte MMC64 en lecture/Ècriture"},
	/* hu */ {IDCLS_MMC64_READWRITE_HU, "MMC64 k·rtya ÌrhatÛ/olvashatÛ"},
	/* it */ {IDCLS_MMC64_READWRITE_IT, "Imposta la card MMC64 in lettura/scrittura"},
	/* ko */ {IDCLS_MMC64_READWRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC64_READWRITE_NL, "Zet de MMC64 als lezen/schrijven"},
	/* pl */ {IDCLS_MMC64_READWRITE_PL, "Ustaw kartÍ MMC64 na tryb zapisu i odczytu"},
	/* ru */ {IDCLS_MMC64_READWRITE_RU, "Set the MMC64 card to read/write"},
	/* sv */ {IDCLS_MMC64_READWRITE_SV, "TillÂt skrivning pÂ MMC64-kort"},
	/* tr */ {IDCLS_MMC64_READWRITE_TR, "MMC64 kart˝n˝ okunur/yaz˝l˝ra Áevir"},
#endif
	
	/* c64/cart/mmc64.c */
	/* en */ {IDCLS_MMC64_BIOS_WRITE,    N_("Save the MMC64 bios when changed")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC64_BIOS_WRITE_DA, "Gem MMC64-BIOS ved Êndring"},
	/* de */ {IDCLS_MMC64_BIOS_WRITE_DE, "MMC64 BIOS speichern bei ƒnderung"},
	/* es */ {IDCLS_MMC64_BIOS_WRITE_ES, "Grabar BIOS MMC64 cuando cambie"},
	/* fr */ {IDCLS_MMC64_BIOS_WRITE_FR, "Sauvegarder le BIOS MMC64 lorsque modifiÈ"},
	/* hu */ {IDCLS_MMC64_BIOS_WRITE_HU, "MMC64 BIOS mentÈse v·ltoz·s ut·n"},
	/* it */ {IDCLS_MMC64_BIOS_WRITE_IT, "Salva il bios MMC64 al cambio"},
	/* ko */ {IDCLS_MMC64_BIOS_WRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC64_BIOS_WRITE_NL, "Sla de MMC64 BIOS op als er veranderingen zijn gemaakt"},
	/* pl */ {IDCLS_MMC64_BIOS_WRITE_PL, "Zapisuj bios MMC64 przy zmianie"},
	/* ru */ {IDCLS_MMC64_BIOS_WRITE_RU, "Save the MMC64 bios when changed"},
	/* sv */ {IDCLS_MMC64_BIOS_WRITE_SV, "Spara MMC64-BIOS vid ‰ndring"},
	/* tr */ {IDCLS_MMC64_BIOS_WRITE_TR, "MMC64 BIOS'unu dei˛tiinde kaydet"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME,    N_("Specify MMC Replay card image filename")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_DA, "Angiv filnavn for MMC Replay kort-image"},
	/* de */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_DE, "MMC Replay Modul imeage datei definieren"},
	/* es */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_ES, "Especificar fichero imagen tarjeta MMC Replay"},
	/* fr */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_IT, "Specifica il nome file immagine della card MMC Replay"},
	/* ko */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_NL, "Geef de naam van het MMC Replay card bestand"},
	/* pl */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_PL, "Okre∂l nazwÍ pliku obrazu karty MMC Replay"},
	/* ru */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_RU, "Specify MMC Replay card image filename"},
	/* sv */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_SV, "Ange namn pÂ avbildningsfil fˆr MMC Replay-kort"},
	/* tr */ {IDCLS_SELECT_MMC_REPLAY_CARD_IMAGE_FILENAME_TR, "MMC Replay kart imaj dosyaismini belirt"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE,    N_("Enable writes to MMC Replay card image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_DA, "Tillad skrivning til MMC Replay kort-image"},
	/* de */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_DE, "Erlaube Schreibzugriff auf MMC Replay Imagedatei"},
	/* es */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_ES, "Permitir grabaciÛn en imagen tarjeta MMC Replay"},
	/* fr */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_IT, "Attiva scrittura su immagine card MMC Replay"},
	/* ko */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_NL, "Aktiveer schrijven naar MMC Replay card bestand"},
	/* pl */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_PL, "W≥±cz zapis do obrazu karty MMC Replay"},
	/* ru */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_RU, "Enable writes to MMC Replay card image"},
	/* sv */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_SV, "Aktivera skrivning till MMC Replay-kortavbildning"},
	/* tr */ {IDCLS_MMC_REPLAY_CARD_WRITE_ENABLE_TR, "MMC Replay kart imaj˝nda yazmalar˝ aktif et"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE,    N_("Disable writes to MMC Replay card image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_DA, "Skriv ikke til MMC Replay kort-image"},
	/* de */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_DE, "Schreibzugriff auf MMC Replay Imagedatei verhindern"},
	/* es */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_ES, "Deshabilitar grabaciÛn en imagen tarjeta MMC Replay"},
	/* fr */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_IT, "Disattiva scrittura su immagine card MMC Replay"},
	/* ko */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_NL, "Schrijven naar het MMC Replay card bestand uitschakelen"},
	/* pl */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_PL, "Wy≥±cz zapis do obrazu karty MMC Replay"},
	/* ru */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_RU, "Disable writes to MMC Replay card image"},
	/* sv */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_SV, "Inaktivera skrivning till MMC Replay-kortavbildning"},
	/* tr */ {IDCLS_MMC_REPLAY_CARD_WRITE_DISABLE_TR, "MMC Replay kart imaj˝nda yazmalar˝ pasifle˛tir"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE,    N_("Specify MMC Replay EEPROM image filename")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_DA, "Angiv filnavn for MMC Replay EEPROM-image"},
	/* de */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_DE, "MMC Replay EEPROM Imagedatei definieren"},
	/* es */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_ES, "Especificar nombre fichero imagen EEPROM MMC Replay"},
	/* fr */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_IT, "Specifica il nome file immagine della EEPROM MMC Replay"},
	/* ko */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_NL, "Geef de naam van het MMC Replay EEPROM bestand"},
	/* pl */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_PL, "Okre∂l nazwÍ pliku obrazu EEPROM MMC Replay"},
	/* ru */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_RU, "Specify MMC Replay EEPROM image filename"},
	/* sv */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_SV, "Ange filnamn fˆr MMC Replay EEPROM-avbildning"},
	/* tr */ {IDCLS_SELECT_MMC_REPLAY_EEPROM_IMAGE_TR, "MMC Replay EEPROM imaj dosyaismini belirt"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE,    N_("Enable writes to MMC Replay EEPROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_DA, "Tillad skrivning til MMC Replay EEPROM-image"},
	/* de */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_DE, "Erlaube Schreibzugriff auf MMC Replay EEPROM Imagedatei"},
	/* es */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_ES, "Permitir grabaciÛn en imagen EEPROM MMC Replay"},
	/* fr */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_IT, "Attiva scrittura su immagine EEPROM MMC Replay"},
	/* ko */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_KO, "MMC Replay EEPROM ¿ÃπÃ¡ˆ ø° æ≤±‚ ∞°¥…«œ∞‘ «œ±‚"},
	/* nl */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_NL, "Aktiveer schrijven naar MMC Replay EEPROM bestand"},
	/* pl */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_PL, "W≥±cz zapis do obrazu EEPROM MMC Replay"},
	/* ru */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_RU, "Enable writes to MMC Replay EEPROM image"},
	/* sv */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_SV, "Aktivera skrivning till MMC Replay EEPROM-avbildning"},
	/* tr */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_ENABLE_TR, "MMC Replay EEPROM imaj˝nda yazmalar˝ aktif et"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE,    N_("Disable writes to MMC Replay EEPROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_DA, "Skriv ikke til MMC Replay EEPROM-image"},
	/* de */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_DE, "Schreibzugriff auf MMC Replay EEPROM Imagedatei verhindern"},
	/* es */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_ES, "Deshabilitar grabaciÛn en imagen EEPROM MMC Replay"},
	/* fr */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_IT, "Disattiva scrittura su immagine EEPROM MMC Replay"},
	/* ko */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_NL, "Schrijven naar MMC Replay EEPROM bestand uitschakelen"},
	/* pl */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_PL, "Wy≥±cz zapis do obrazu EEPROM MMC Replay"},
	/* ru */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_RU, "Disable writes to MMC Replay EEPROM image"},
	/* sv */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_SV, "Inaktivera skrivning till MMC Replay EEPROM-avbildning"},
	/* tr */ {IDCLS_MMC_REPLAY_EEPROM_WRITE_DISABLE_TR, "MMC Replay EEPROM imaj˝nda yazmalar˝ pasifle˛tir"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE,    N_("Enable MMC Replay rescue mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_DA, "AktivÈr MMC Replay fejlsikret tilstand"},
	/* de */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_DE, "MMC Replay Rescue Modus aktivieren"},
	/* es */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_ES, "Permitir modo rescate MMC Replay "},
	/* fr */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_IT, "Attiva modalit‡ ripristino MMC Replay"},
	/* ko */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_NL, "Activeer MMC Replay reddingsmodus"},
	/* pl */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_PL, "W≥±cz tryb ratunkowy MMC Replay"},
	/* ru */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_RU, "Enable MMC Replay rescue mode"},
	/* sv */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_SV, "Aktivera MMC Replay-r‰ddningsl‰ge"},
	/* tr */ {IDCLS_MMC_REPLAY_RESCUE_MODE_ENABLE_TR, "MMC Replay kurtarma modunu aktif et"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE,    N_("Disable MMC Replay rescue mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_DA, "DeaktivÈr MMC Replay fejlsikret tilstand"},
	/* de */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_DE, "MMC Replay Rescue Modus deaktivieren"},
	/* es */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_ES, "Deshabilitar modo rescate MMC Replay "},
	/* fr */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_IT, "Disattiva modalit‡ ripristino MMC Replay"},
	/* ko */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_NL, "MMC Replay reddingsmodus uitschakelen"},
	/* pl */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_PL, "Wy≥±cz tryb ratunkowy MMC Replay"},
	/* ru */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_RU, "Disable MMC Replay rescue mode"},
	/* sv */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_SV, "Inaktivera MMC Replay-r‰ddningsl‰ge"},
	/* tr */ {IDCLS_MMC_REPLAY_RESCUE_MODE_DISABLE_TR, "MMC Replay kurtarma modunu pasifle˛tir"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE,    N_("Allow writing to MMC Replay image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_DA, "Tillad skrivning til MMC Replay-image"},
	/* de */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_DE, "Erlaube Schreibzugriff auf MMC Replay Image"},
	/* es */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_ES, "Permtir grabaciÛn en imagen MMC Replay"},
	/* fr */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_IT, "Attiva scrittura su immagine MMC Replay"},
	/* ko */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_NL, "Aktiveer schrijven naar MMC Replay bestand"},
	/* pl */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_PL, "PozwÛl na zapis do obrazu MMC Replay"},
	/* ru */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_RU, "Allow writing to MMC Replay image"},
	/* sv */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_SV, "TillÂt skrivning till MMC Replay-avbildning"},
	/* tr */ {IDCLS_ALLOW_WRITING_TO_MMC_REPLAY_IMAGE_TR, "MMC Replay imaj˝na yazmay˝ aktif et"},
#endif
	
	/* c64/cart/mmcreplay.c */
	/* en */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE,    N_("Do not write to MMC Replay image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_DA, "Skriv ikke til MMC Replay-image"},
	/* de */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_DE, "Kein Schreibzugriff auf MMC Replay Image"},
	/* es */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_ES, "No grabar en imagen MMC Replay"},
	/* fr */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_IT, "Disattiva scrittura su immagine MMC Replay"},
	/* ko */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_NL, "Schrijf niet naar MMC Replay bestand"},
	/* pl */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_PL, "Nie zapisuj do obrazu MMC Replay"},
	/* ru */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_RU, "Do not write to MMC Replay image"},
	/* sv */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_SV, "Skriv inte till MMC Replay-avbildning"},
	/* tr */ {IDCLS_DO_NOT_WRITE_TO_MMC_REPLAY_IMAGE_TR, "MMC Replay imaj˝na yazma"},
#endif
	
	/* c64/cart/retroreplay.c */
	/* en */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT,    N_("Enable saving of the RR ROM at exit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_DA, "AktivÈr skrivning af RR ROM ved afslutning"},
	/* de */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_DE, "Speichern des RR ROMs beim Beenden aktivieren"},
	/* es */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_ES, "Permitir grabar ROM RR al salir"},
	/* fr */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_IT, "Attiva salvataggio ROM della RR all'uscita"},
	/* ko */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_NL, "Activeer opslaan van het RR ROM bestand bij afsluiten"},
	/* pl */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_PL, "W≥±cz zapis ROM RR przy wyj∂ciu"},
	/* ru */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_RU, "Enable saving of the RR ROM at exit"},
	/* sv */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_SV, "Aktivera sparande av RR-ROM vid avslutning"},
	/* tr */ {IDCLS_ENABLE_SAVE_RR_ROM_AT_EXIT_TR, "«˝k˝˛ta RR ROM'un kaydedilmesini aktif et"},
#endif
	
	/* c64/cart/retroreplay.c */
	/* en */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT,    N_("Disable saving of the RR ROM at exit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_DA, "DektivÈr skrivning af RR ROM ved afslutning"},
	/* de */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_DE, "Speichern des RR ROMs beim Beenden deaktivieren"},
	/* es */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_ES, "Deshabilitar grabar ROM RR al salir"},
	/* fr */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_IT, "Disattiva salvataggio ROM della RR all'uscita"},
	/* ko */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_NL, "Uitschakelen van het opslaan van het RR ROM bestand bij afsluiten"},
	/* pl */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_PL, "Wy≥±cz zapis ROM RR przy wyj∂ciu"},
	/* ru */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_RU, "Disable saving of the RR ROM at exit"},
	/* sv */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_SV, "Inaktivera sparande av RR-ROM vid avslutning"},
	/* tr */ {IDCLS_DISABLE_SAVE_RR_ROM_AT_EXIT_TR, "«˝k˝˛ta RR ROM'un kaydedilmesini pasifle˛tir"},
#endif
	
	/* c64/cart/retroreplay.c */
	/* en */ {IDCLS_SET_RR_BANK_JUMPER,    N_("Set RR Bank Jumper")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_RR_BANK_JUMPER_DA, "Tilslut RR Bank Jumper"},
	/* de */ {IDCLS_SET_RR_BANK_JUMPER_DE, "Aktiviere RR Bank Jumper"},
	/* es */ {IDCLS_SET_RR_BANK_JUMPER_ES, "Seleccionar conmutador banco RR"},
	/* fr */ {IDCLS_SET_RR_BANK_JUMPER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_RR_BANK_JUMPER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_RR_BANK_JUMPER_IT, "Imposta ponticello bank della RR"},
	/* ko */ {IDCLS_SET_RR_BANK_JUMPER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_RR_BANK_JUMPER_NL, "Zet RR bank jumper"},
	/* pl */ {IDCLS_SET_RR_BANK_JUMPER_PL, "Ustaw prze≥±cznik RR Bank"},
	/* ru */ {IDCLS_SET_RR_BANK_JUMPER_RU, "Set RR Bank Jumper"},
	/* sv */ {IDCLS_SET_RR_BANK_JUMPER_SV, "Aktivera RR-bankbygel"},
	/* tr */ {IDCLS_SET_RR_BANK_JUMPER_TR, "RR Bank Jumper'˝ tak"},
#endif
	
	/* c64/cart/retroreplay.c */
	/* en */ {IDCLS_UNSET_RR_BANK_JUMPER,    N_("Unset RR Bank Jumper")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_UNSET_RR_BANK_JUMPER_DA, "Afbryd RR Bank Jumper"},
	/* de */ {IDCLS_UNSET_RR_BANK_JUMPER_DE, "Deaktiviere RR Bank Jumper"},
	/* es */ {IDCLS_UNSET_RR_BANK_JUMPER_ES, "Quitar conmutador banco RR"},
	/* fr */ {IDCLS_UNSET_RR_BANK_JUMPER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_UNSET_RR_BANK_JUMPER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_UNSET_RR_BANK_JUMPER_IT, "Rimuovi ponticello bank della RR"},
	/* ko */ {IDCLS_UNSET_RR_BANK_JUMPER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_UNSET_RR_BANK_JUMPER_NL, "Zet RR bank jumper niet"},
	/* pl */ {IDCLS_UNSET_RR_BANK_JUMPER_PL, "Wy≥±cz prze≥±cznik RR Bank"},
	/* ru */ {IDCLS_UNSET_RR_BANK_JUMPER_RU, "Unset RR Bank Jumper"},
	/* sv */ {IDCLS_UNSET_RR_BANK_JUMPER_SV, "Inaktivera RR-bankbygel"},
	/* tr */ {IDCLS_UNSET_RR_BANK_JUMPER_TR, "RR Bank Jumper'˝ Á˝kart"},
#endif
	
	/* c64/cart/retroreplay.c */
	/* en */ {IDCLS_SET_RR_FLASH_JUMPER,    N_("Set RR Flash Jumper")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_RR_FLASH_JUMPER_DA, "Tilslut RR Flash jumper"},
	/* de */ {IDCLS_SET_RR_FLASH_JUMPER_DE, "Aktviere RR Flash Jumper"},
	/* es */ {IDCLS_SET_RR_FLASH_JUMPER_ES, "Seleccionar conmutador RR Flash"},
	/* fr */ {IDCLS_SET_RR_FLASH_JUMPER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_RR_FLASH_JUMPER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_RR_FLASH_JUMPER_IT, "Imposta ponticello flash della RR"},
	/* ko */ {IDCLS_SET_RR_FLASH_JUMPER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_RR_FLASH_JUMPER_NL, "Zet RR Flash Jumper"},
	/* pl */ {IDCLS_SET_RR_FLASH_JUMPER_PL, "Ustaw prze≥±cznik RR Flash"},
	/* ru */ {IDCLS_SET_RR_FLASH_JUMPER_RU, "Set RR Flash Jumper"},
	/* sv */ {IDCLS_SET_RR_FLASH_JUMPER_SV, "S‰tt RR-flashbygel"},
	/* tr */ {IDCLS_SET_RR_FLASH_JUMPER_TR, "RR Flash Jumper'˝ tak"},
#endif
	
	/* c64/cart/retroreplay.c */
	/* en */ {IDCLS_UNSET_RR_FLASH_JUMPER,    N_("Unset RR Bank Jumper")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_UNSET_RR_FLASH_JUMPER_DA, "Afbryd RR Bank Jumper"},
	/* de */ {IDCLS_UNSET_RR_FLASH_JUMPER_DE, "Deaktiviere RR Bank Jumper"},
	/* es */ {IDCLS_UNSET_RR_FLASH_JUMPER_ES, "Quitar conmutador banco RR"},
	/* fr */ {IDCLS_UNSET_RR_FLASH_JUMPER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_UNSET_RR_FLASH_JUMPER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_UNSET_RR_FLASH_JUMPER_IT, "Rimuovi ponticello bank della RR"},
	/* ko */ {IDCLS_UNSET_RR_FLASH_JUMPER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_UNSET_RR_FLASH_JUMPER_NL, "Zet RR bank jumper niet"},
	/* pl */ {IDCLS_UNSET_RR_FLASH_JUMPER_PL, "Wy≥±cz prze≥±cznik RR Bank"},
	/* ru */ {IDCLS_UNSET_RR_FLASH_JUMPER_RU, "Unset RR Bank Jumper"},
	/* sv */ {IDCLS_UNSET_RR_FLASH_JUMPER_SV, "Inaktivera RR-bankbygel"},
	/* tr */ {IDCLS_UNSET_RR_FLASH_JUMPER_TR, "RR Bank Jumper'˝ Á˝kart"},
#endif
	
	/* c64/cart/reu.c */
	/* en */ {IDCLS_ENABLE_REU,    N_("Enable the RAM Expansion Unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_REU_DA, "AktivÈr RAM-udviddelsesenheden"},
	/* de */ {IDCLS_ENABLE_REU_DE, "RAM Speichererweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_REU_ES, "Permitir unidad RAM expansion"},
	/* fr */ {IDCLS_ENABLE_REU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_REU_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_REU_IT, "Attiva l'espansione di RAM"},
	/* ko */ {IDCLS_ENABLE_REU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_REU_NL, "Activeer de RAM uitbreidingseenheid (REU)"},
	/* pl */ {IDCLS_ENABLE_REU_PL, "W≥±cz RAM Expansion Unit"},
	/* ru */ {IDCLS_ENABLE_REU_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_REU_SV, "Aktivera RAM-expansionsenhet"},
	/* tr */ {IDCLS_ENABLE_REU_TR, "RAM Geni˛letme Birimi'ni aktif et"},
#endif
	
	/* c64/cart/reu.c */
	/* en */ {IDCLS_DISABLE_REU,    N_("Disable the RAM Expansion Unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_REU_DA, "DeaktivÈr RAM-udviddelsesenhed"},
	/* de */ {IDCLS_DISABLE_REU_DE, "RAM Speichererweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_REU_ES, "Deshabilitar unidad RAM Expansion"},
	/* fr */ {IDCLS_DISABLE_REU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_REU_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_REU_IT, "Disattiva l'espansione di RAM"},
	/* ko */ {IDCLS_DISABLE_REU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_REU_NL, "De RAM uitbreidingseenheid (REU) uitschakelen"},
	/* pl */ {IDCLS_DISABLE_REU_PL, "Wy≥±cz RAM Expansion Unit"},
	/* ru */ {IDCLS_DISABLE_REU_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_REU_SV, "Inaktivera RAM-expansionsenhet"},
	/* tr */ {IDCLS_DISABLE_REU_TR, "RAM Geni˛letme Birimi'ni pasifle˛tir"},
#endif
	
	/* c64/cart/reu.c */
	/* en */ {IDCLS_SPECIFY_REU_NAME,    N_("Specify name of REU image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_REU_NAME_DA, "Angiv navn pÂ REU-image"},
	/* de */ {IDCLS_SPECIFY_REU_NAME_DE, "Namen f¸r REU Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_REU_NAME_ES, "Especificar nombre imagen REU"},
	/* fr */ {IDCLS_SPECIFY_REU_NAME_FR, "SpÈcifier le nom de l'image REU"},
	/* hu */ {IDCLS_SPECIFY_REU_NAME_HU, "Adja meg a REU kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_REU_NAME_IT, "Specifica il nome immagine REU"},
	/* ko */ {IDCLS_SPECIFY_REU_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_REU_NAME_NL, "Geef de naam van het REU bestand"},
	/* pl */ {IDCLS_SPECIFY_REU_NAME_PL, "Okre∂l nazwÍ obrazu REU"},
	/* ru */ {IDCLS_SPECIFY_REU_NAME_RU, "Specify name of REU image"},
	/* sv */ {IDCLS_SPECIFY_REU_NAME_SV, "Ange namn pÂ REU-avbildning"},
	/* tr */ {IDCLS_SPECIFY_REU_NAME_TR, "REU imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/cart/reu.c */
	/* en */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE,    N_("Allow writing to REU image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_DA, "Tillad skrivning til REU-image"},
	/* de */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_DE, "Schreibzugriff auf REU Image erlauben"},
	/* es */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_ES, "Permitir grabar en imagen REU"},
	/* fr */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_IT, "Attiva scrittura su immagine REU"},
	/* ko */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_NL, "Aktiveer schrijven naar REU bestand"},
	/* pl */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_PL, "PozwÛl na zapis do obrazu REU"},
	/* ru */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_RU, "Allow writing to REU image"},
	/* sv */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_SV, "TillÂt skrivning till REU-avbildning"},
	/* tr */ {IDCLS_ALLOW_WRITING_TO_REU_IMAGE_TR, "REU imaj˝na yazmay˝ aktif et"},
#endif
	
	/* c64/cart/reu.c */
	/* en */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE,    N_("Do not write to REU image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_DA, "Skriv ikke til REU-image"},
	/* de */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_DE, "Kein Schreibzugriff auf REU Image"},
	/* es */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_ES, "No grabar en imagen REU"},
	/* fr */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_IT, "Disattiva scrittura su immagine REU"},
	/* ko */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_NL, "Schrijf niet naar REU bestand"},
	/* pl */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_PL, "Nie zapisuj do obrazu REU"},
	/* ru */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_RU, "Do not write to REU image"},
	/* sv */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_SV, "Skriv inte till REU-avbildning"},
	/* tr */ {IDCLS_DO_NOT_WRITE_TO_REU_IMAGE_TR, "REU imaj˝na yazma"},
#endif
	
	/* c64/cart/reu.c */
	/* en */ {IDCLS_REU_SIZE,    N_("Size of the RAM expansion unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_REU_SIZE_DA, "St¯rrelse pÂ RAM-udviddelsesenhed"},
	/* de */ {IDCLS_REU_SIZE_DE, "Grˆﬂe der RAM Speichererweiterung"},
	/* es */ {IDCLS_REU_SIZE_ES, "TamaÒo unidad expansion RAM"},
	/* fr */ {IDCLS_REU_SIZE_FR, "Taille de l'unitÈ d'expansion RAM"},
	/* hu */ {IDCLS_REU_SIZE_HU, "RAM Expansion Unit mÈrete"},
	/* it */ {IDCLS_REU_SIZE_IT, "Dimensione dell'espansione di RAM"},
	/* ko */ {IDCLS_REU_SIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_REU_SIZE_NL, "Grootte van de RAM uitbreidingseenheid (REU)"},
	/* pl */ {IDCLS_REU_SIZE_PL, "Rozmiar jednostki rozszerzenia RAM"},
	/* ru */ {IDCLS_REU_SIZE_RU, "Size of the RAM expansion unit"},
	/* sv */ {IDCLS_REU_SIZE_SV, "Storlek pÂ RAM-expansionsenhet"},
	/* tr */ {IDCLS_REU_SIZE_TR, "RAM geni˛letme biriminin boyutu"},
#endif
	
#ifdef HAVE_TFE
	/* c64/cart/tfe.c */
	/* en */ {IDCLS_ENABLE_TFE,    N_("Enable the TFE (\"The Final Ethernet\") unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_TFE_DA, "AktivÈr TFE-enhed (\"The Final Ethernet\")"},
	/* de */ {IDCLS_ENABLE_TFE_DE, "TFE (\"the final ethernet\") Erweiterung aktivitieren"},
	/* es */ {IDCLS_ENABLE_TFE_ES, "Permitir unidad TFE (\"The Final Ethernet\")"},
	/* fr */ {IDCLS_ENABLE_TFE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_TFE_HU, "TFE (\"the final ethernet\") egysÈg engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_TFE_IT, "Attiva l'unit‡ TFE (\"The Final Ethernet\")"},
	/* ko */ {IDCLS_ENABLE_TFE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_TFE_NL, "Activeer de TFE (\"The Final Ethernet\") eenheid"},
	/* pl */ {IDCLS_ENABLE_TFE_PL, "W≥±cz jednostkÍ TFE (\"The Final Ethernet\")"},
	/* ru */ {IDCLS_ENABLE_TFE_RU, "Enable the TFE (\"The Final Ethernet\") unit"},
	/* sv */ {IDCLS_ENABLE_TFE_SV, "Aktivera TFE-enhet (\"The Final Ethernet\")"},
	/* tr */ {IDCLS_ENABLE_TFE_TR, "TFE (\"The Final Ethernet\") birimini aktif et"},
#endif
	
	/* c64/cart/tfe.c */
	/* en */ {IDCLS_DISABLE_TFE,    N_("Disable the TFE (\"The Final Ethernet\") unit")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_TFE_DA, "DeaktivÈr TFE-enhed (\"The Final Ethernet\")"},
	/* de */ {IDCLS_DISABLE_TFE_DE, "TFE (\"the final ethernet\") Erweiterung deaktivitieren"},
	/* es */ {IDCLS_DISABLE_TFE_ES, "Deshabilitar unidad TFE (\"The Final Ethernet\")"},
	/* fr */ {IDCLS_DISABLE_TFE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_TFE_HU, "TFE (\"The Final Ethernet\") egysÈg tilt·sa"},
	/* it */ {IDCLS_DISABLE_TFE_IT, "Disattiva l'unit‡ TFE (\"The Final Ethernet\")"},
	/* ko */ {IDCLS_DISABLE_TFE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_TFE_NL, "De TFE (\"The Final Ethernet\") eenheid uitschakelen"},
	/* pl */ {IDCLS_DISABLE_TFE_PL, "Wy≥±cz jednostkÍ TFE (\"The Final Ethernet\")"},
	/* ru */ {IDCLS_DISABLE_TFE_RU, "Disable the TFE (\"The Final Ethernet\") unit"},
	/* sv */ {IDCLS_DISABLE_TFE_SV, "Inaktivera TFE-enhet (\"The Final Ethernet\")"},
	/* tr */ {IDCLS_DISABLE_TFE_TR, "TFE (\"The Final Ethernet\") birimini pasifle˛tir"},
#endif
	
	/* c64/cart/tfe.c */
	/* en */ {IDCLS_TFE_INTERFACE,    N_("Set the system ethernet interface for TFE emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TFE_INTERFACE_DA, "Indstil systemets netkort til TFE-emulering"},
	/* de */ {IDCLS_TFE_INTERFACE_DE, "Setze die System Ethernet Schnittstelle f¸r die TFE Emulation"},
	/* es */ {IDCLS_TFE_INTERFACE_ES, "Seleccionar interface sistema ethernet para emulaciÛn TFE"},
	/* fr */ {IDCLS_TFE_INTERFACE_FR, "DÈfinir líinterface ethernet pour líÈmulation TFE"},
	/* hu */ {IDCLS_TFE_INTERFACE_HU, "Rendszer ethernet eszkˆz be·llÌt·sa TFE emul·ciÛhoz"},
	/* it */ {IDCLS_TFE_INTERFACE_IT, "Imposta l'interfaccia ethernet per l'emulazione TFE"},
	/* ko */ {IDCLS_TFE_INTERFACE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TFE_INTERFACE_NL, "Zet de systeem ethernetinterface voor de TFE emulatie"},
	/* pl */ {IDCLS_TFE_INTERFACE_PL, "Ustaw interfejs systemowy ethernet emulacji TFE"},
	/* ru */ {IDCLS_TFE_INTERFACE_RU, "Set the system ethernet interface for TFE emulation"},
	/* sv */ {IDCLS_TFE_INTERFACE_SV, "St‰ll in systemets ethernetgr‰nssnitt fˆr TFE-emulering"},
	/* tr */ {IDCLS_TFE_INTERFACE_TR, "Sistem ethernet arabirimini TFE em¸lasyonu iÁin ayarla"},
#endif
	
	/* c64/cart/tfe.c */
	/* en */ {IDCLS_ENABLE_TFE_AS_RRNET,    N_("Enable RRNet mode of TFE emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_TFE_AS_RRNET_DA, "AktivÈr RRNet-tilstand af TFE-emulering"},
	/* de */ {IDCLS_ENABLE_TFE_AS_RRNET_DE, "RRNet Modus der TFE Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_TFE_AS_RRNET_ES, "Permitir emulaciÛn TFE en modo RRNet"},
	/* fr */ {IDCLS_ENABLE_TFE_AS_RRNET_FR, "Activer le mode RRNet de líÈmulation TFE"},
	/* hu */ {IDCLS_ENABLE_TFE_AS_RRNET_HU, "RRNet mÛd engedÈlyezÈse TFE emul·ciÛhoz"},
	/* it */ {IDCLS_ENABLE_TFE_AS_RRNET_IT, "Attiva la modalit‡ RRNet dell'emulazione TFE"},
	/* ko */ {IDCLS_ENABLE_TFE_AS_RRNET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_TFE_AS_RRNET_NL, "Activeer RRNet modus van de TFE emulatie"},
	/* pl */ {IDCLS_ENABLE_TFE_AS_RRNET_PL, "W≥±cz tryb RRNet emulacji TFE"},
	/* ru */ {IDCLS_ENABLE_TFE_AS_RRNET_RU, "Enable RRNet mode of TFE emulation"},
	/* sv */ {IDCLS_ENABLE_TFE_AS_RRNET_SV, "Aktivera RRNet-l‰ge pÂ TFE-emulering"},
	/* tr */ {IDCLS_ENABLE_TFE_AS_RRNET_TR, "TFE em¸lasyonunun RRNet modunu aktif et"},
#endif
	
	/* c64/cart/tfe.c */
	/* en */ {IDCLS_DISABLE_TFE_AS_RRNET,    N_("Disable RRNet mode of TFE emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_TFE_AS_RRNET_DA, "DeaktivÈr RRNet-l‰ge af TFE-emulering"},
	/* de */ {IDCLS_DISABLE_TFE_AS_RRNET_DE, "RRNet Modus der TFE Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_TFE_AS_RRNET_ES, "Deshabilitar emulaciÛn TFE en modo RRNet"},
	/* fr */ {IDCLS_DISABLE_TFE_AS_RRNET_FR, "DÈsactiver le mode RRNet de líÈmulation TFE"},
	/* hu */ {IDCLS_DISABLE_TFE_AS_RRNET_HU, "RRNet mÛd tilt·sa TFE emul·ciÛhoz"},
	/* it */ {IDCLS_DISABLE_TFE_AS_RRNET_IT, "Disattiva la modalit‡ RRNet dell'emulazione TFE"},
	/* ko */ {IDCLS_DISABLE_TFE_AS_RRNET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_TFE_AS_RRNET_NL, "RRNet modus van de TFE emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_TFE_AS_RRNET_PL, "Wy≥±cz tryb RRNet emulacji TFE"},
	/* ru */ {IDCLS_DISABLE_TFE_AS_RRNET_RU, "Disable RRNet mode of TFE emulation"},
	/* sv */ {IDCLS_DISABLE_TFE_AS_RRNET_SV, "Inaktivera RRNet-l‰ge pÂ TFE-emulering"},
	/* tr */ {IDCLS_DISABLE_TFE_AS_RRNET_TR, "TFE em¸lasyonunun RRNet modunu pasifle˛tir"},
#endif
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_CART_ATTACH_DETACH_RESET,    N_("Reset machine if a cartridge is attached or detached")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_CART_ATTACH_DETACH_RESET_DA, "Reset maskinen hvis et cartridge tilsluttes eller frakobles"},
	/* de */ {IDCLS_CART_ATTACH_DETACH_RESET_DE, "Reset der Maschine wenn ein Erweiterungsmodul eingelegt oder entfernt wird"},
	/* es */ {IDCLS_CART_ATTACH_DETACH_RESET_ES, "Reiniciar m·quina si un cartucho es insertado o extraido"},
	/* fr */ {IDCLS_CART_ATTACH_DETACH_RESET_FR, "RÈinitialiser si une cartouche est insÈrÈe ou retirÈe"},
	/* hu */ {IDCLS_CART_ATTACH_DETACH_RESET_HU, "Reset a cartridge csatol·sakorgy lev·laszt·sakor"},
	/* it */ {IDCLS_CART_ATTACH_DETACH_RESET_IT, "Fare il reset della macchina se una cartuccia Ë collegata o rimossa"},
	/* ko */ {IDCLS_CART_ATTACH_DETACH_RESET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_CART_ATTACH_DETACH_RESET_NL, "Reset machine als een cartridge wordt gekoppeld of ontkoppeld"},
	/* pl */ {IDCLS_CART_ATTACH_DETACH_RESET_PL, "Resetuj maszynÍ przy zamontowaniu i odmontowaniu kartridøa"},
	/* ru */ {IDCLS_CART_ATTACH_DETACH_RESET_RU, "Reset machine if a cartridge is attached or detached"},
	/* sv */ {IDCLS_CART_ATTACH_DETACH_RESET_SV, "Nollst‰ll maskinen om en insticksmodul kopplas till eller frÂn"},
	/* tr */ {IDCLS_CART_ATTACH_DETACH_RESET_TR, "Bir kartu˛ tak˝l˝r ya da Á˝kart˝l˝rsa makineyi resetle"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_CART_ATTACH_DETACH_NO_RESET,    N_("Do not reset machine if a cartridge is attached or detached")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_DA, "Reset ikke maskinen hvis et cartridge tilsluttes eller frakobles"},
	/* de */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_DE, "Kein Reset der Maschine wenn ein Erweiterungsmodul eingelegt oder entfernt wird"},
	/* es */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_ES, "No reiniciar m·quina si un cartucho es insertado o extraido"},
	/* fr */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_FR, "Ne pas rÈinitialiser si une cartouche est insÈrÈe ou retirÈe"},
	/* hu */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_HU, "Nincs reset a cartridge csatol·sakorgy lev·laszt·sakor"},
	/* it */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_IT, "Non fare il reset della macchina se una cartuccia Ë collegata o rimossa"},
	/* ko */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_NL, "Reset machine niet als een cartridge wordt gekoppeld of ontkoppeld"},
	/* pl */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_PL, "Nie resetuj maszyny przy zamontowaniu i odmontowaniu kartridøa"},
	/* ru */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_RU, "Do not reset machine if a cartridge is attached or detached"},
	/* sv */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_SV, "Nollst‰ll inte maskinen om en insticksmodul kopplas till eller frÂn"},
	/* tr */ {IDCLS_CART_ATTACH_DETACH_NO_RESET_TR, "Bir kartu˛ tak˝l˝r ya da Á˝kart˝l˝rsa makineyi resetleme"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_CRT_CART,    N_("Attach CRT cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_CRT_CART_DA, "Tilslut CRT-cartridge image"},
	/* de */ {IDCLS_ATTACH_CRT_CART_DE, "CRT Erweiterungsmodul Image einlegen"},
	/* es */ {IDCLS_ATTACH_CRT_CART_ES, "Insertar imagen de cartucho CRT"},
	/* fr */ {IDCLS_ATTACH_CRT_CART_FR, "InsÈrer une cartouche CRT"},
	/* hu */ {IDCLS_ATTACH_CRT_CART_HU, "CRT cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_CRT_CART_IT, "Seleziona immagine cartuccia CRT"},
	/* ko */ {IDCLS_ATTACH_CRT_CART_KO, "CRT ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿø©≥÷¿∏Ω√ø¿"},
	/* nl */ {IDCLS_ATTACH_CRT_CART_NL, "Koppel CRT cartridge bestand aan"},
	/* pl */ {IDCLS_ATTACH_CRT_CART_PL, "Zamontuj obraz kartridøa CRT"},
	/* ru */ {IDCLS_ATTACH_CRT_CART_RU, "Attach CRT cartridge image"},
	/* sv */ {IDCLS_ATTACH_CRT_CART_SV, "Anslut CRT-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_CRT_CART_TR, "CRT kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_GENERIC_8KB_CART,    N_("Attach raw 8KB cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_GENERIC_8KB_CART_DA, "Tilslut rÂt 8kB-cartridge image"},
	/* de */ {IDCLS_ATTACH_GENERIC_8KB_CART_DE, "8KB Erweiterungsmodul (raw) Image einlegen"},
	/* es */ {IDCLS_ATTACH_GENERIC_8KB_CART_ES, "Insertar imagen de cartucho 8KB"},
	/* fr */ {IDCLS_ATTACH_GENERIC_8KB_CART_FR, "InsÈrer une cartouche 8KO"},
	/* hu */ {IDCLS_ATTACH_GENERIC_8KB_CART_HU, "Nyers 8KB-os cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_GENERIC_8KB_CART_IT, "Seleziona immagine cartuccia di 8KB"},
	/* ko */ {IDCLS_ATTACH_GENERIC_8KB_CART_KO, "8kb ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_GENERIC_8KB_CART_NL, "Koppel binair 8KB cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_GENERIC_8KB_CART_PL, "Zamontuj surowy obraz kartridøa 8KB"},
	/* ru */ {IDCLS_ATTACH_GENERIC_8KB_CART_RU, "ø‡ÿ⁄‡’ﬂÿ‚Ï ﬂ‡ﬁ’⁄‚ ﬁ—‡–◊– 8∫— ⁄–‡‚‡ÿ‘÷–"},
	/* sv */ {IDCLS_ATTACH_GENERIC_8KB_CART_SV, "Anslut rÂ 8KB-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_GENERIC_8KB_CART_TR, "D¸z 8KB kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_GENERIC_16KB_CART,    N_("Attach raw 16KB cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_GENERIC_16KB_CART_DA, "Tilslut rÂt 16kB-cartridge image"},
	/* de */ {IDCLS_ATTACH_GENERIC_16KB_CART_DE, "16KB Erweiterungsmodul (raw) Image einlegen"},
	/* es */ {IDCLS_ATTACH_GENERIC_16KB_CART_ES, "Insertar imagen de cartucho 16KB"},
	/* fr */ {IDCLS_ATTACH_GENERIC_16KB_CART_FR, "InsÈrer une cartouche 16KO"},
	/* hu */ {IDCLS_ATTACH_GENERIC_16KB_CART_HU, "Nyers 16KB-os cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_GENERIC_16KB_CART_IT, "Seleziona immagine cartuccia di 16KB"},
	/* ko */ {IDCLS_ATTACH_GENERIC_16KB_CART_KO, "16kb ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_GENERIC_16KB_CART_NL, "Koppel binair 16KB cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_GENERIC_16KB_CART_PL, "Zamontuj surowy obraz kartridøa 16KB"},
	/* ru */ {IDCLS_ATTACH_GENERIC_16KB_CART_RU, "ø‡ÿ⁄‡’ﬂÿ‚Ï ﬂ‡ﬁ’⁄‚ ﬁ—‡–◊– 16∫— ⁄–‡‚‡ÿ‘÷–"},
	/* sv */ {IDCLS_ATTACH_GENERIC_16KB_CART_SV, "Anslut rÂ 16KB-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_GENERIC_16KB_CART_TR, "D¸z 16KB kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART,    N_("Attach generic 16kB Ultimax cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_DA, "Tilslut standard 16kB Ultimax cartridge image"},
	/* de */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_DE, "Generisches 16kB Ultimax Erweiterungsmodul Image einlegen"},
	/* es */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_ES, "Insertar imagen cartucho generico Ultimax 16KB"},
	/* fr */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_IT, "Seleziona immagine cartuccia Ultimax generica di 16kB"},
	/* ko */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_NL, "Koppel algemeen 16KB Ultimax cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_PL, "Zamontuj standardowy obraz kartridøa 16kB Ultimax"},
	/* ru */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_RU, "Attach generic 16kB Ultimax cartridge image"},
	/* sv */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_SV, "Anslut vanlig 16KB Ultimax-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_GENERIC_16KB_ULTIMAX_CART_TR, "Jenerik 16KB Ultimax kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_STARDOS_CART,    N_("Attach raw 16KB Stardos cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_STARDOS_CART_DA, "Tilslut rÂt 16KB StarDOS cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_STARDOS_CART_DE, "16kB Stardos Erweiterungsmodul Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_STARDOS_CART_ES, "Insertar imagen cartucho Stardos 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_STARDOS_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_STARDOS_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_STARDOS_CART_IT, "Seleziona immagine cartuccia Stardos di 16KB"},
	/* ko */ {IDCLS_ATTACH_RAW_STARDOS_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_STARDOS_CART_NL, "Koppel binair 16KB Stardos cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_STARDOS_CART_PL, "Zamontuj surowy obraz kartridøa 16KB Stardos"},
	/* ru */ {IDCLS_ATTACH_RAW_STARDOS_CART_RU, "Attach raw 16KB Stardos cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_STARDOS_CART_SV, "Anslut rÂ 16KB Stardos-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_STARDOS_CART_TR, "D¸z 16KB Stardos kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART,    N_("Attach raw 32KB Action Replay MK4 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_DA, "Tilslut rÂt 32KB Action Replay MK4 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_DE, "32kB Action Replay MK4 Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_ES, "Insertar imagen cartucho Action Replay MK4 32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_IT, "Seleziona immagine cartuccia Action Replay MK4 di 326KB"},
	/* ko */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_NL, "Koppel binair 32KB Action Replay MK4 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_PL, "Zamontuj surowy obraz kartridøa 32KB Action Replay MK4"},
	/* ru */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_RU, "Attach raw 32KB Action Replay MK4 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_SV, "Anslut rÂ 32KB-Action Replay MK4-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY4_CART_TR, "D¸z 32KB Action Replay MK4 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART,    N_("Attach raw 16kB Action Replay MK2 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_DA, "Tilslut rÂt 16kB Action Replay MK2 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_DE, "16kB Action Replay MK2 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_ES, "Insertar imagen cartucho Action Replay MK2 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_IT, "Seleziona immagine cartuccia Action Replay MK2 di 16KB"},
	/* ko */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_NL, "Koppel binair 16kB Action Replay MK2 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_PL, "Zamontuj surowy obraz kartridøa 16kB Action Replay MK2"},
	/* ru */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_RU, "Attach raw 16kB Action Replay MK2 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_SV, "Anslut rÂ 16KB-Action Replay MK2-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY2_CART_TR, "D¸z 16kB Action Replay MK2 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART,    N_("Attach raw 16KB Action Replay MK3 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_DA, "Tilslut rÂt 16KB Action Replay MK3 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_DE, "16kB Action Replay MK3 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_ES, "Insertar imagen cartucho Action Replay MK3 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_IT, "Seleziona immagine cartuccia Action Replay MK3 di 16KB"},
	/* ko */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_NL, "Koppel binair 16KB Action Replay MK3 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_PL, "Zamontuj surowy obraz kartridøa 16KB Action Replay MK3"},
	/* ru */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_RU, "Attach raw 16KB Action Replay MK3 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_SV, "Anslut rÂ 16KB-Action Replay MK3-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY3_CART_TR, "D¸z 16KB Action Replay MK3 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART,    N_("Attach raw 32KB Action Replay cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_DA, "Tilslut rÂt 32KB Action Replay cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_DE, "32kB Action Replay Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_ES, "Insertar imagen cartucho Action Replay 32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_FR, "InsÈrer une cartouche Action Replay 32KO"},
	/* hu */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_HU, "32KB-os Action Replay cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_IT, "Seleziona immagine cartuccia Action Replay di 32KB"},
	/* ko */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_NL, "Koppel binair 32KB Action Replay cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_PL, "Zamontuj surowy obraz kartidøa 32KB Action Replay"},
	/* ru */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_RU, "Attach raw 32KB Action Replay cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_SV, "Anslut rÂ 32KB-Action Replay-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_ACTION_REPLAY_CART_TR, "D¸z 32KB Action Replay kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_CAPTURE_CART,    N_("Attach raw 8kB Capture cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_CAPTURE_CART_DA, "Tilslut rÂt 8kB Capture cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_CAPTURE_CART_DE, "8kB Capture Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_CAPTURE_CART_ES, "Insertar imagen cartucho Capture 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_CAPTURE_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_CAPTURE_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_CAPTURE_CART_IT, "Seleziona immagine cartuccia Capture di 8KB"},
	/* ko */ {IDCLS_ATTACH_RAW_CAPTURE_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_CAPTURE_CART_NL, "Koppel binair 8kB Capture cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_CAPTURE_CART_PL, "Zamontuj surowy obraz kartridøa 8kB Capture"},
	/* ru */ {IDCLS_ATTACH_RAW_CAPTURE_CART_RU, "Attach raw 8kB Capture cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_CAPTURE_CART_SV, "Anslut rÂ 8KB Capture-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_CAPTURE_CART_TR, "D¸z 8kB Capture kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_COMAL80_CART,    N_("Attach raw 64kB Comal 80 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_COMAL80_CART_DA, "Tilslut rÂt 64kB Comal 80 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_COMAL80_CART_DE, "64kB Comal 80 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_COMAL80_CART_ES, "Insertar imagen cartucho Comal 80 64KB"},
	/* fr */ {IDCLS_ATTACH_RAW_COMAL80_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_COMAL80_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_COMAL80_CART_IT, "Seleziona immagine cartuccia Comal 80 di 64kB"},
	/* ko */ {IDCLS_ATTACH_RAW_COMAL80_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_COMAL80_CART_NL, "Koppel binair 64kB Comal 80 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_COMAL80_CART_PL, "Zamontuj surowy obraz kartridøa 64kB Comal 80"},
	/* ru */ {IDCLS_ATTACH_RAW_COMAL80_CART_RU, "Attach raw 64kB Comal 80 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_COMAL80_CART_SV, "Anslut rÂ 64kB Comal 80-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_COMAL80_CART_TR, "D¸z 64kB Comal 80 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_DELA_EP256_CART,    N_("Attach raw Dela EP256 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_DA, "Tilslut rÂt Dela EP256 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_DE, "Dela EP256 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_ES, "Insertar imagen cartucho Dela EP256"},
	/* fr */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_IT, "Seleziona immagine cartuccia Dela EP256"},
	/* ko */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_NL, "Koppel binair Dela EP256 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_PL, "Zamontuj surowy obraz kartridøa Dela EP256"},
	/* ru */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_RU, "Attach raw Dela EP256 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_SV, "Anslut rÂ dela EP256-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_DELA_EP256_CART_TR, "D¸z Dela EP256 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_DELA_EP64_CART,    N_("Attach raw Dela EP64 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_DA, "Tilslut rÂt Dela EP64 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_DE, "Dela EP64 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_ES, "Insertar imagen cartucho Dela EP64"},
	/* fr */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_IT, "Seleziona immagine cartuccia Dela EP64"},
	/* ko */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_NL, "Koppel binair Dela EO64 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_PL, "Zamontuj surowy obraz kartridøa EP64"},
	/* ru */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_RU, "Attach raw Dela EP64 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_SV, "Anslut rÂ Dela EP64-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_DELA_EP64_CART_TR, "D¸z Dela EP64 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART,    N_("Attach raw Dela EP7x8 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_DA, "Tilslut rÂt Dela EP7x8 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_DE, "Dela EP7x8 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_ES, "Insertar imagen cartucho Dela EP 7x8"},
	/* fr */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_IT, "Seleziona immagine cartuccia Dela EP7x8"},
	/* ko */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_NL, "Koppel binair Dela ep7x8 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_PL, "Zamontuj surowy obraz kartridøa Dela EP7x8"},
	/* ru */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_RU, "Attach raw Dela EP7x8 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_SV, "Anslut rÂ Dela EP7x8-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_DELA_EP7X8_CART_TR, "D¸z Dela EP7x8 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_DINAMIC_CART,    N_("Attach raw 128kB Dinamic cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_DINAMIC_CART_DA, "Tilslut rÂt 128kB Dinamic cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_DINAMIC_CART_DE, "128kB Dinamic Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_DINAMIC_CART_ES, "Insertar imagen cartucho Dinamic 128KB"},
	/* fr */ {IDCLS_ATTACH_RAW_DINAMIC_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_DINAMIC_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_DINAMIC_CART_IT, "Seleziona immagine cartuccia Dinamic di 128kB"},
	/* ko */ {IDCLS_ATTACH_RAW_DINAMIC_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_DINAMIC_CART_NL, "Koppel binair 128kB Dinamic cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_DINAMIC_CART_PL, "Zamontuj surowy obraz kartridøa 128kB Dinamic"},
	/* ru */ {IDCLS_ATTACH_RAW_DINAMIC_CART_RU, "Attach raw 128kB Dinamic cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_DINAMIC_CART_SV, "Anslut rÂ 12kB Dinamic-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_DINAMIC_CART_TR, "D¸z 128kB Dinamic kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART,    N_("Attach raw 8kB Diashow-Maker cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_DA, "Tilslut rÂt 8kB Diashow-Maker cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_DE, "8kB Diashow-Maker Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_ES, "Insertar imagen cartucho Diashow-Maker 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_IT, "Seleziona immagine cartuccia Diashow-Maker di 8KB"},
	/* ko */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_NL, "Koppel binair 8kB Diashow-Maker cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_PL, "Zamontuj surowy obraz kartridøa 8kB Diashow-Maker"},
	/* ru */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_RU, "Attach raw 8kB Diashow-Maker cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_SV, "Anslut rÂ 8kB Diashow-Maker-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_DIASHOW_MAKER_CART_TR, "D¸z 8kB Diashow-Maker kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_DQBB_CART,    N_("Attach raw 16kB Double Quick Brown Box cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_DQBB_CART_DA, "Tilslut rÂt 16kB Double Quick Brown Box cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_DQBB_CART_DE, "16kB Double Quick Brown Box Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_DQBB_CART_ES, "Insertar imagen cartucho DBQQ 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_DQBB_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_DQBB_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_DQBB_CART_IT, "Seleziona immagine cartuccia Double Quick Brown Box di 16kB"},
	/* ko */ {IDCLS_ATTACH_RAW_DQBB_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_DQBB_CART_NL, "Koppel binair 16kB Double Quick Brown Box cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_DQBB_CART_PL, "Zamontuj surowy obraz kartridøa Double Quick Brown Box"},
	/* ru */ {IDCLS_ATTACH_RAW_DQBB_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ATTACH_RAW_DQBB_CART_SV, "Anslut rÂ 16KB Double Quick Brown Box-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_DQBB_CART_TR, "D¸z 16kB Double Quick Brown Box kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART,    N_("Attach raw EasyFlash cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_DA, "Tilslut rÂt EasyFlash cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_DE, "Easyflash Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_ES, "Insertar imagen cartucho  EasyFlash"},
	/* fr */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_IT, "Seleziona immagine cartuccia EasyFlash"},
	/* ko */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_KO, "EasyFlash ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_NL, "Koppel binair EasyFlash cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_PL, "Zamontuj surowy obraz kartridøa EasyFlash"},
	/* ru */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_SV, "Anslut rÂ EasyFlash-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_EASY_FLASH_CART_TR, "D¸z EasyFlash kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART,    N_("Attach raw 64KB Retro Replay cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_DA, "Tilslut rÂt 64kB-Retro Replay-cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_DE, "64kB Retro Replay Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_ES, "Insertar imagen cartucho Retro Replay 64KB"},
	/* fr */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_FR, "InsÈrer une cartouche Retro Replay 64KO"},
	/* hu */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_HU, "64KB-os Retro Replay cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_IT, "Seleziona immagine cartuccia Retro Replay di 64KB"},
	/* ko */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_KO, "64KB Retro Replay ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_NL, "Koppel binair 64KB Retro Replay cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_PL, "Zamontuj surowy obraz kartridøa 64KB Retro Replay"},
	/* ru */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_RU, "Attach raw 64KB Retro Replay cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_SV, "Anslut rÂ 64KB-Retro Replay-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_RETRO_REPLAY_CART_TR, "D¸z 64KB Retro Replay kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART,    N_("Attach raw 8kB REX Utility cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_DA, "Tilslut rÂt 8kB REX Utility cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_DE, "8kB REX Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_ES, "Insertar imagen cartucho REX Utility 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_IT, "Seleziona immagine cartuccia REX Utility di 8kB"},
	/* ko */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_NL, "Koppel binair 8kB REX Utility cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_PL, "Zamontuj surowy obraz kartridøa 8kB REX Utility"},
	/* ru */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_RU, "Attach raw 8kB REX Utility cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_SV, "Anslut rÂ 8kB REX Utility-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_REX_UTILITY_CART_TR, "D¸z 8kB REX Utility kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_SS64_CART,    N_("Attach raw 4kB Snapshot 64 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_SS64_CART_DA, "Tilslut rÂt 4kB Snapshot 64 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_SS64_CART_DE, "4kB Snapshot 64 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_SS64_CART_ES, "Insertar imagen cartucho Snapshot 64 4KB"},
	/* fr */ {IDCLS_ATTACH_RAW_SS64_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_SS64_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_SS64_CART_IT, "Seleziona immagine cartuccia Snapshot 64 di 4kB"},
	/* ko */ {IDCLS_ATTACH_RAW_SS64_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_SS64_CART_NL, "Koppel binair 4kB Snapshot 64 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_SS64_CART_PL, "Zamontuj surowy obraz kartridøa 4kB Snapshot 64"},
	/* ru */ {IDCLS_ATTACH_RAW_SS64_CART_RU, "Attach raw 4kB Snapshot 64 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_SS64_CART_SV, "Anslut rÂ 4kB Snapshot 64-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_SS64_CART_TR, "D¸z 4kB Snapshot 64 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_IDE64_CART,    N_("Attach raw 64KB IDE64 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_IDE64_CART_DA, "Tilslut rÂt 64kB IDE64-cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_IDE64_CART_DE, "64kB IDE64 Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_IDE64_CART_ES, "Insertar imagen cartucho IDE64 64KB"},
	/* fr */ {IDCLS_ATTACH_RAW_IDE64_CART_FR, "InsÈrer une cartouche IDE64 64KO"},
	/* hu */ {IDCLS_ATTACH_RAW_IDE64_CART_HU, "64KB-os IDE64 cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_RAW_IDE64_CART_IT, "Seleziona immagine cartuccia IDE64 di 64KB"},
	/* ko */ {IDCLS_ATTACH_RAW_IDE64_CART_KO, "64kb IDE64 ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_IDE64_CART_NL, "Koppel binair 64KB IDE64 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_IDE64_CART_PL, "Zamontuj surowy obraz kartridøa 64KB IDE64"},
	/* ru */ {IDCLS_ATTACH_RAW_IDE64_CART_RU, "Attach raw 64KB IDE64 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_IDE64_CART_SV, "Anslut rÂ 64KB IDE64-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_IDE64_CART_TR, "D¸z 64KB IDE64 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART,    N_("Attach raw 32KB Atomic Power cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_DA, "Tilslut rÂt 32kB Atomic Power-cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_DE, "32kB Atomic Power Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_ES, "Insertar imagen cartucho Atomic Power 32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_FR, "InsÈrer une cartouche Atomic Power 32KO"},
	/* hu */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_HU, "32KB-os Atomic Power cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_IT, "Seleziona immagine cartuccia Atomic Power di 32KB"},
	/* ko */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_KO, "32kb Atomic Power ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_NL, "Koppel binair 32KB Atomic Power cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_PL, "Zamontuj surowy obraz kartridøa 32KB Atomic Power"},
	/* ru */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_RU, "Attach raw 32KB Atomic Power cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_SV, "Anslut rÂ 32KB Atomic Power-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_ATOMIC_POWER_CART_TR, "D¸z 32KB Atomic Power kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART,    N_("Attach raw 8KB Epyx FastLoad cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_DA, "Tilslut rÂt 8kB Epyx FastLoad cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_DE, "8kB Epyx Fastload Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_ES, "Insertar imagen cartucho Epyx Fastload 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_IT, "Seleziona immagine cartuccia Epyx FastLoad di 8KB"},
	/* ko */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_KO, "8kb Epyx FastLoad ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_NL, "Koppel binair 8KB Epyx FastLoad cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_PL, "Zamontuj surowy obraz kartridøa 8KB Epyx FastLoad"},
	/* ru */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_RU, "Attach raw 8KB Epyx FastLoad cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_SV, "Anslut rÂ 8KB Epyx FastLoad-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_EPYX_FASTLOAD_CART_TR, "D¸z 8KB Epyx FastLoad kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_EXOS_CART,    N_("Attach raw 8kB EXOS cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_EXOS_CART_DA, "Tilslut rÂt 8kB EXOS cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_EXOS_CART_DE, "8kB EXOS Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_EXOS_CART_ES, "Insertar imagen cartucho EXOS 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_EXOS_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_EXOS_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_EXOS_CART_IT, "Seleziona immagine cartuccia EXOS di 8KB"},
	/* ko */ {IDCLS_ATTACH_RAW_EXOS_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_EXOS_CART_NL, "Koppel binair 8kB EXOS cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_EXOS_CART_PL, "Zamontuj surowy obraz kartridøa 8kB EXOS"},
	/* ru */ {IDCLS_ATTACH_RAW_EXOS_CART_RU, "Attach raw 8kB EXOS cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_EXOS_CART_SV, "Anslut rÂ 8kB EXOS-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_EXOS_CART_TR, "D¸z 8kB EXOS kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_EXPERT_CART,    N_("Attach raw 8kB Expert Cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_EXPERT_CART_DA, "Tilslut rÂt 8kB Expert Cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_EXPERT_CART_DE, "8kB Expert Cartridge Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_EXPERT_CART_ES, "Insertar imagen cartucho Expert 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_EXPERT_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_EXPERT_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_EXPERT_CART_IT, "Seleziona immagine cartuccia Expert Cartridge di 8kB"},
	/* ko */ {IDCLS_ATTACH_RAW_EXPERT_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_EXPERT_CART_NL, "Koppel binair 8kB Expert Cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_EXPERT_CART_PL, "Zamontuj surowy obraz 8kB Expert Cartridge"},
	/* ru */ {IDCLS_ATTACH_RAW_EXPERT_CART_RU, "Attach raw 8kB Expert Cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_EXPERT_CART_SV, "Anslut rÂ 8kB Expert Cartridge-avbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_EXPERT_CART_TR, "D¸z 8kB Expert Kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_F64_CART,    N_("Attach raw 32kB Formel 64 image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_F64_CART_DA, "Tilslut rÂt 32kB Formel 64 image"},
	/* de */ {IDCLS_ATTACH_RAW_F64_CART_DE, "32kB Formel 64 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_F64_CART_ES, "Insertar imagen cartucho Formel 64 de 32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_F64_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_F64_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_F64_CART_IT, "Seleziona immagine cartuccia Formel 64 di 32kb"},
	/* ko */ {IDCLS_ATTACH_RAW_F64_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_F64_CART_NL, "Koppel binair 32kB Formel 64 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_F64_CART_PL, "Zamontuj surowy obraz 32kB Formel 64"},
	/* ru */ {IDCLS_ATTACH_RAW_F64_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ATTACH_RAW_F64_CART_SV, "Anslut rÂ 32kB Formel 64-avbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_F64_CART_TR, "D¸z 32kB Formel 64 imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_FC1_CART,    N_("Attach raw 16kB Final Cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_FC1_CART_DA, "Tilslut rÂt 16kB Final Cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_FC1_CART_DE, "16kB Final Cartridge Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_FC1_CART_ES, "Insertar imagen cartucho Final Cartridge 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_FC1_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_FC1_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_FC1_CART_IT, "Seleziona immagine cartuccia Final Cartridge di 16kB"},
	/* ko */ {IDCLS_ATTACH_RAW_FC1_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_FC1_CART_NL, "Koppel binair 16kB Final Cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_FC1_CART_PL, "Zamontuj surowy obraz 16kB Final Cartridge"},
	/* ru */ {IDCLS_ATTACH_RAW_FC1_CART_RU, "Attach raw 16kB Final Cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_FC1_CART_SV, "Anslut rÂ 16kB Final Cartridge-avbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_FC1_CART_TR, "D¸z 16kB Final kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_FC3_CART,    N_("Attach raw 64kB Final Cartridge III image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_FC3_CART_DA, "Tilslut rÂt 64kB Final Cartridge III image"},
	/* de */ {IDCLS_ATTACH_RAW_FC3_CART_DE, "64kB Final Cartridge Image III (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_FC3_CART_ES, "Insertar imagen cartucho Final Cartridge III 64KB"},
	/* fr */ {IDCLS_ATTACH_RAW_FC3_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_FC3_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_FC3_CART_IT, "Seleziona immagine cartuccia Final Cartridge III di 64kB"},
	/* ko */ {IDCLS_ATTACH_RAW_FC3_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_FC3_CART_NL, "Koppel binair 16kB Final Cartridge III bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_FC3_CART_PL, "Zamontuj surowy obraz Final Cartridge III"},
	/* ru */ {IDCLS_ATTACH_RAW_FC3_CART_RU, "Attach raw 64kB Final Cartridge III image"},
	/* sv */ {IDCLS_ATTACH_RAW_FC3_CART_SV, "Anslut rÂ 64kB Final Cartridge III-avbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_FC3_CART_TR, "D¸z 64kB Final Cartridge III imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_FCPLUS_CART,    N_("Attach raw 32kB Final Cartridge Plus image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_FCPLUS_CART_DA, "Tilslut rÂt 32kB Final Cartridge Plus image"},
	/* de */ {IDCLS_ATTACH_RAW_FCPLUS_CART_DE, "32kB Final Cartridge Plus Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_FCPLUS_CART_ES, "Insertar imagen cartucho Final Cartridge PLUS 32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_FCPLUS_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_FCPLUS_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_FCPLUS_CART_IT, "Seleziona immagine cartuccia Final Cartridge Plus di 32kB"},
	/* ko */ {IDCLS_ATTACH_RAW_FCPLUS_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_FCPLUS_CART_NL, "Koppel binair 32kB Final Cartridge Plus bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_FCPLUS_CART_PL, "Zamontuj surowy obraz 32kB Final Cartridge Plus"},
	/* ru */ {IDCLS_ATTACH_RAW_FCPLUS_CART_RU, "Attach raw 32kB Final Cartridge Plus image"},
	/* sv */ {IDCLS_ATTACH_RAW_FCPLUS_CART_SV, "Anslut rÂ 32kB Final Cartridge Plus-fil"},
	/* tr */ {IDCLS_ATTACH_RAW_FCPLUS_CART_TR, "D¸z 32kB Final Cartridge Plus imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART,    N_("Attach raw 8kB Freeze Frame image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_DA, "Tilslut rÂt 8kB Freeze Frame image"},
	/* de */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_DE, "8kB Freeze Frame Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_ES, "Insertar imagen cartucho Freeze Frame 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_IT, "Seleziona immagine cartuccia Freeze Frame di 8kb"},
	/* ko */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_NL, "Koppel binair 8kB Freeze Frame cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_PL, "Zamontuj surowy obraz 8kB Freeze Frame"},
	/* ru */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_RU, "Attach raw 8kB Freeze Frame image"},
	/* sv */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_SV, "Anslut rÂ 8kB Freeze Frame-avbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_FREEZE_FRAME_CART_TR, "D¸z 8kB Freeze Frame imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART,    N_("Attach raw 32kB Freeze Machine image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_DA, "Tilslut rÂt 32kB Freeze Machine image"},
	/* de */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_DE, "8kB Freeze Machine Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_ES, "Insertar imagen cartucho Freeze Machine 32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_IT, "Seleziona immagine cartuccia Freeze Machine di 32kb"},
	/* ko */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_NL, "Koppel binair 32kB Freeze Machine cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_PL, "Zamontuj surowy obraz 32kB Freeze Machine"},
	/* ru */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_RU, "Attach raw 32kB Freeze Machine image"},
	/* sv */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_SV, "Anslut rÂ 32kB Freeze Machine-avbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_FREEZE_MACHINE_CART_TR, "D¸z 32kB Freeze Machine imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_FP_PP_CART,    N_("Attach raw 128kB Fun Play/Power Play cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_FP_PP_CART_DA, "Tilslut rÂt 128kB Fun Play/Power Play cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_FP_PP_CART_DE, "128kB Fun Play/Power Play Cartridge  Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_FP_PP_CART_ES, "Insertar imagen cartucho Fun Play/Power Play 128KB"},
	/* fr */ {IDCLS_ATTACH_RAW_FP_PP_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_FP_PP_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_FP_PP_CART_IT, "Seleziona immagine cartuccia Fun Play/Power Play di 128kB"},
	/* ko */ {IDCLS_ATTACH_RAW_FP_PP_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_FP_PP_CART_NL, "Koppel binair 128kB Fun Play/Power Play cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_FP_PP_CART_PL, "Zamontuj surowy obraz kartridøa 128kB Fun Play/Power Play"},
	/* ru */ {IDCLS_ATTACH_RAW_FP_PP_CART_RU, "Attach raw 128kB Fun Play/Power Play cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_FP_PP_CART_SV, "Anslut rÂ 128kB Fun Play/Power Play-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_FP_PP_CART_TR, "D¸z 128kB Fun Play/Power Play kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_SS4_CART,    N_("Attach raw 32KB Super Snapshot V4 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_SS4_CART_DA, "Tilslut rÂt 32kB Super Snapshot V4 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_SS4_CART_DE, "32kB Super Snapshot V4 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_SS4_CART_ES, "Insertar imagen cartucho Super Snapshot V4 32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_SS4_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_SS4_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_SS4_CART_IT, "Seleziona immagine cartuccia Super Snapshot V4 di 32KB"},
	/* ko */ {IDCLS_ATTACH_RAW_SS4_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_SS4_CART_NL, "Koppel binair 32KB Super Snapshot V4 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_SS4_CART_PL, "Zamontuj surowy obraz kartridøa 32KB Super Snapshot V4"},
	/* ru */ {IDCLS_ATTACH_RAW_SS4_CART_RU, "Attach raw 32KB Super Snapshot V4 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_SS4_CART_SV, "Anslut rÂ 32KB Super Snapshot V4-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_SS4_CART_TR, "D¸z 32KB Super Snapshot V4 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_SS5_CART,    N_("Attach raw 64KB Super Snapshot V5 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_SS5_CART_DA, "Tilslut rÂt 64kB Super Snapshot V5 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_SS5_CART_DE, "64kB Super Snapshot V5 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_SS5_CART_ES, "Insertar imagen cartucho Super Snapshot V5 64KB"},
	/* fr */ {IDCLS_ATTACH_RAW_SS5_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_SS5_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_SS5_CART_IT, "Seleziona immagine cartuccia Super Snapshot V5 di 64KB"},
	/* ko */ {IDCLS_ATTACH_RAW_SS5_CART_KO, "64KB Super Snapshot V5 ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_SS5_CART_NL, "Koppel binair 64KB Super Snapshot V5 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_SS5_CART_PL, "Zamontuj surowy obraz kartridøa Super Snapshot V5"},
	/* ru */ {IDCLS_ATTACH_RAW_SS5_CART_RU, "Attach raw 64KB Super Snapshot V5 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_SS5_CART_SV, "Anslut rÂ 64KB-Super Snapshot V5-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_SS5_CART_TR, "D¸z 64KB Super Snapshot V5 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_CBM_IEEE488_CART,    N_("Attach IEEE-488 Interface cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_CBM_IEEE488_CART_DA, "Tilslut IEEE-488 interface cartridge image"},
	/* de */ {IDCLS_ATTACH_CBM_IEEE488_CART_DE, "IEEE Schnittstellen Erweiterungsmodul Image einlegen"},
	/* es */ {IDCLS_ATTACH_CBM_IEEE488_CART_ES, "Insertar imagen de cartucho Interface IEEE-488"},
	/* fr */ {IDCLS_ATTACH_CBM_IEEE488_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_CBM_IEEE488_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_CBM_IEEE488_CART_IT, "Seleziona immagine cartuccia interfaccia IEEE"},
	/* ko */ {IDCLS_ATTACH_CBM_IEEE488_CART_KO, "IEEE-488 ¿Œ≈Õ∆–¿ÃΩ∫ ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿø©≥÷¿∏ººø‰"},
	/* nl */ {IDCLS_ATTACH_CBM_IEEE488_CART_NL, "Koppel IEEE-488 Interface cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_CBM_IEEE488_CART_PL, "Zamontuj obraz kartridøa IEEE-488 Interface"},
	/* ru */ {IDCLS_ATTACH_CBM_IEEE488_CART_RU, "Attach IEEE-488 Interface cartridge image"},
	/* sv */ {IDCLS_ATTACH_CBM_IEEE488_CART_SV, "Anslut IEEE-488-gr‰nssnittsavbildningsfil"},
	/* tr */ {IDCLS_ATTACH_CBM_IEEE488_CART_TR, "IEEE-488 Arabirimi kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ISEPIC_CART,    N_("Attach raw 2kB ISEPIC cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ISEPIC_CART_DA, "Tilslut rÂt 2kB ISEPIC-cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ISEPIC_CART_DE, "2kB ISEPIC Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ISEPIC_CART_ES, "Insertar imagen cartucho ISEPIC 2KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ISEPIC_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_ISEPIC_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_ISEPIC_CART_IT, "Seleziona immagine cartuccia ISEPIC di 2kB"},
	/* ko */ {IDCLS_ATTACH_RAW_ISEPIC_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_ISEPIC_CART_NL, "Koppel binair 2kB ISEPIC cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ISEPIC_CART_PL, "Zamontuj surowy obraz kartridøa 2kB ISEPIC"},
	/* ru */ {IDCLS_ATTACH_RAW_ISEPIC_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ATTACH_RAW_ISEPIC_CART_SV, "Anslut rÂ 2kB ISEPIC-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_ISEPIC_CART_TR, "D¸z 2kB ISEPIC kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_KCS_CART,    N_("Attach raw 16kB KCS Power cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_KCS_CART_DA, "Tilslut rÂt 16kB KCS Power Cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_KCS_CART_DE, "16kB KCS Power Cartridge Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_KCS_CART_ES, "Insertar imagen cartucho KCS Power Cartridge 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_KCS_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_KCS_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_KCS_CART_IT, "Seleziona immagine cartuccia KCS Power di 16kB"},
	/* ko */ {IDCLS_ATTACH_RAW_KCS_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_KCS_CART_NL, "Koppel binair 16kB KSC Power cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_KCS_CART_PL, "Zamontuj surowy obraz kartridøa 16kB KCS Power"},
	/* ru */ {IDCLS_ATTACH_RAW_KCS_CART_RU, "Attach raw 16kB KCS Power cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_KCS_CART_SV, "Anslut rÂ 16KB KCS Power-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_KCS_CART_TR, "D¸z 16kB KCS Power kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_KINGSOFT_CART,    N_("Attach raw 24kB Kingsoft cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_DA, "Tilslut rÂt 24kB Snapshot 64 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_DE, "24kB Kingsoft Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_ES, "Insertar imagen cartucho 24KB Kingsoft"},
	/* fr */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_IT, "Seleziona immagine cartuccia Kingsoft di 24kB"},
	/* ko */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_NL, "Koppel binair 24kB Kingsoft cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_PL, "Zamontuj surowy obraz kartridøa 24kB Kingsoft"},
	/* ru */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_SV, "Anslut rÂ 24kB-Kingsoft-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_KINGSOFT_CART_TR, "D¸z 24kB Kingsoft kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_MACH5_CART,    N_("Attach raw 8kB MACH 5 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_MACH5_CART_DA, "Tilslut rÂt 8kB MACH 5 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_MACH5_CART_DE, "8kB MAC 5 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_MACH5_CART_ES, "Insertar imagen cartucho MACH 5 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_MACH5_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_MACH5_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_MACH5_CART_IT, "Seleziona immagine cartuccia MACH 5 di 8kB"},
	/* ko */ {IDCLS_ATTACH_RAW_MACH5_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_MACH5_CART_NL, "Koppel binair 8kB MACH 5 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_MACH5_CART_PL, "Zamontuj surowy obraz kartridøa 8kB MACH 5"},
	/* ru */ {IDCLS_ATTACH_RAW_MACH5_CART_RU, "Attach raw 8kB MACH 5 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_MACH5_CART_SV, "Anslut rÂ 8kB MACH 5-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_MACH5_CART_TR, "D¸z 8kB MACH 5 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART,    N_("Attach raw 32/64/128kB Magic Desk cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_DA, "Tilslut rÂt 32/64/128kB Magic Desk cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_DE, "32/64/128kB Magic Desk Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_ES, "Insertar imagen cartucho Magic Desc 32/64/128KB"},
	/* fr */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_IT, "Seleziona immagine cartuccia Magic Desk di 32/64/128kB"},
	/* ko */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_NL, "Koppel binair 32/64/128kB Magic Desk cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_PL, "Zamontuj surowy obraz kartridøa 32/64/128kB Magic Desk"},
	/* ru */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_RU, "Attach raw 32/64/128kB Magic Desk cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_SV, "Anslut rÂ 32/64/128kB Magic Desk-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_MAGIC_DESK_CART_TR, "D¸z 32/64/128kB Magic Desk kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART,    N_("Attach raw Magic Formel cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_DA, "Tilslut rÂt Magic Formel cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_DE, "Magic Formel Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_ES, "Insertar imagen cartucho Magic Formel"},
	/* fr */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_IT, "Seleziona immagine cartuccia Magic Formel"},
	/* ko */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_KO, "Magic Formel ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_NL, "Koppel binair Magic Formel cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_PL, "Zamontuj surowy obraz kartridøa Magic Formel"},
	/* ru */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_RU, "Attach raw Magic Formel cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_SV, "Anslut rÂ Magic Romel-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_MAGIC_FORMEL_CART_TR, "D¸z Magic Formel kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART,    N_("Attach raw 8kB Mikro Assembler cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_DA, "Tilslut rÂt 8kB Mikro Assembler cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_DE, "8kB Mikro Assembler Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_ES, "Insertar imagen cartucho Mikro Assembler 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_IT, "Seleziona immagine cartuccia Mikro Assembler di 8kB"},
	/* ko */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_NL, "Koppel binair 8KB Mikro Assembler cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_PL, "Zamontuj surowy obraz kartridøa 8kB Mikro Assembler"},
	/* ru */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_RU, "Attach raw 8kB Mikro Assembler cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_SV, "Anslut rÂ 8kB Mikro Assembler-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_MIKRO_ASSEMBLER_CART_TR, "D¸z 8kB Mikro Assembler kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_MMC64_CART,    N_("Attach raw 8kB MMC64 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_MMC64_CART_DA, "Tilslut rÂt 8kB MMC64 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_MMC64_CART_DE, "8kB MMC64 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_MMC64_CART_ES, "Insertar imagen cartucho MMC64 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_MMC64_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_MMC64_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_MMC64_CART_IT, "Seleziona immagine cartuccia MMC64 di 8kB"},
	/* ko */ {IDCLS_ATTACH_RAW_MMC64_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_MMC64_CART_NL, "Koppel binair 8kB MMC64 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_MMC64_CART_PL, "Zamontuj surowy obraz kartridøa 8kB MMC64"},
	/* ru */ {IDCLS_ATTACH_RAW_MMC64_CART_RU, "Attach raw 8kB MMC64 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_MMC64_CART_SV, "Anslut rÂ 8kB MMC64-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_MMC64_CART_TR, "D¸z 8kB MMC64 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART,    N_("Attach raw 512kB MMC Replay cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_DA, "Tilslut rÂt 512kB MMC Replay cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_DE, "512kB MMC Replay Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_ES, "Insertar imagen cartucho MMC Replay 512KB"},
	/* fr */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_IT, "Seleziona immagine cartuccia MMC Replay di 512kB"},
	/* ko */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_KO, "512KB MMC Replay ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ ∫Ÿ¿Ãººø‰"},
	/* nl */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_NL, "Koppel binair 512kB MMC Replay cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_PL, "Zamontuj surowy obraz kartridøa 512kB MMC Replay"},
	/* ru */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_RU, "Attach raw 512kB MMC Replay cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_SV, "Anslut rÂ 512kB MMC Replay-avbildningsfil"},
	/* tr */ {IDCLS_ATTACH_RAW_MMC_REPLAY_CART_TR, "D¸z 512kB MMC Replay kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART,    N_("Attach raw 16kB Magic Voice cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_DA, "Tilslut rÂt 16kB Magic Voice cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_DE, "16kB Magic Voice Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_ES, "Insertar imagen cartucho Magic Voice 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_IT, "Seleziona immagine cartuccia Magic Voice di 16kB"},
	/* ko */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_NL, "Koppel binair 16kB Magic Voice cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_PL, "Zamontuj surowy obraz kartridøa 16kB Magic Voice"},
	/* ru */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_RU, "Attach raw 16kB Magic Voice cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_SV, "Anslut rÂ 16kB Magic Voice-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_MAGIC_VOICE_CART_TR, "D¸z 16kB Magic Voice kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_OCEAN_CART,    N_("Attach raw Ocean cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_OCEAN_CART_DA, "Tilslut rÂt Ocean cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_OCEAN_CART_DE, "Ocean Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_OCEAN_CART_ES, "Insertar imagen cartucho Ocean"},
	/* fr */ {IDCLS_ATTACH_RAW_OCEAN_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_OCEAN_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_OCEAN_CART_IT, "Seleziona immagine cartuccia Ocean"},
	/* ko */ {IDCLS_ATTACH_RAW_OCEAN_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_OCEAN_CART_NL, "Koppel binair Ocean cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_OCEAN_CART_PL, "Zamontuj surowy obraz kartridøa Ocean"},
	/* ru */ {IDCLS_ATTACH_RAW_OCEAN_CART_RU, "Attach raw Ocean cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_OCEAN_CART_SV, "Anslut rÂ Ocean-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_OCEAN_CART_TR, "D¸z Ocean kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_WESTERMANN_CART,    N_("Attach raw 16KB Westermann Learning cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_DA, "Tilslut rÂt 16kB Westermann Learning cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_DE, "16kB Westermann learning Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_ES, "Insertar imagen cartucho Wstermann Learning 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_IT, "Seleziona immagine cartuccia Westermann Learning di 16KB"},
	/* ko */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_NL, "Koppel binair 16kB Westermann Learning cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_PL, "Zamontuj surowy obraz kartridøa 16KB Westermann Learning"},
	/* ru */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_RU, "Attach raw 16KB Westermann Learning cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_SV, "Anslut rÂ 16KB Westermann Learning-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_WESTERMANN_CART_TR, "D¸z 16KB Westermann Learning kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_WARPSPEED_CART,    N_("Attach raw 8kB Warp Speed cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_DA, "Tilslut rÂt 8kB Warp Speed cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_DE, "8kB Warp Speed Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_ES, "Insertar imagen cartucho Warp Speed 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_IT, "Seleziona immagine cartuccia Warp Speed di 8kB"},
	/* ko */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_NL, "Koppel binair 8kB Warp Speed cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_PL, "Zamontuj surowy obraz kartridøa 8kB Warp Speed"},
	/* ru */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_RU, "Attach raw 8kB Warp Speed cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_SV, "Anslut rÂ 8kB-Warp Speed-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_WARPSPEED_CART_TR, "D¸z 8kB Warp Speed kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ZAXXON_CART,    N_("Attach raw 16kB Zaxxon cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ZAXXON_CART_DA, "Tilslut rÂt 16kB Zaxxon cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ZAXXON_CART_DE, "16kB Zaxxon Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ZAXXON_CART_ES, "Insertar imagen cartucho Zaxxon 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ZAXXON_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_ZAXXON_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_ZAXXON_CART_IT, "Seleziona immagine cartuccia Zaxxon di 16kB"},
	/* ko */ {IDCLS_ATTACH_RAW_ZAXXON_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_ZAXXON_CART_NL, "Koppel binair 16kB Zaxxon cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ZAXXON_CART_PL, "Zamontuj surowy obraz kartridøa 16kB Zaxxon"},
	/* ru */ {IDCLS_ATTACH_RAW_ZAXXON_CART_RU, "Attach raw 16kB Zaxxon cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_ZAXXON_CART_SV, "Anslut rÂ 16kB Zaxxon-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_ZAXXON_CART_TR, "D¸z 16kB Zaxxon kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_PAGEFOX_CART,    N_("Attach raw 64KB Pagefox cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_DA, "Tilslut rÂt 64kB Pagefox cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_DE, "Pagefox Erweiterungsmodul Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_ES, "Insertar imagen cartucho 64KB Pagefox"},
	/* fr */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_IT, "Seleziona immagine cartuccia Pagefox di 64KB"},
	/* ko */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_NL, "Koppel binair 64KB Pagefox cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_PL, "Zamontuj surowy obraz kartridøa 64KB Pagefox"},
	/* ru */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_SV, "Anslut rÂ 64KB-Pagefox-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_PAGEFOX_CART_TR, "D¸z 64KB Pagefox kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_P64_CART,    N_("Attach raw 256KB Prophet 64 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_P64_CART_DA, "Tilslut rÂt 256kB Prophet 64 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_P64_CART_DE, "256KB Prophet 64 Erweiterungsmodul Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_P64_CART_ES, "Insertar imagen cartucho Prohet 64 256KB"},
	/* fr */ {IDCLS_ATTACH_RAW_P64_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_P64_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_P64_CART_IT, "Seleziona immagine cartuccia Prophet 64 di 256KB"},
	/* ko */ {IDCLS_ATTACH_RAW_P64_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_P64_CART_NL, "Koppel binair 256KB Prophet 64 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_P64_CART_PL, "Zamontuj surowy obraz kartridøa 256KB Prophet 64"},
	/* ru */ {IDCLS_ATTACH_RAW_P64_CART_RU, "Attach raw 256KB Prophet 64 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_P64_CART_SV, "Anslut rÂ 256KB Prophet 64-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_P64_CART_TR, "D¸z 256KB Prophet 64 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_RAMCART_CART,    N_("Attach raw RamCart cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_RAMCART_CART_DA, "Tilslut rÂt RamCart cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_RAMCART_CART_DE, "RamCart Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_RAMCART_CART_ES, "Insertar imagen cartucho RamCart"},
	/* fr */ {IDCLS_ATTACH_RAW_RAMCART_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_RAMCART_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_RAMCART_CART_IT, "Seleziona immagine cartuccia RamCart"},
	/* ko */ {IDCLS_ATTACH_RAW_RAMCART_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_RAMCART_CART_NL, "Koppel binair RamCart cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_RAMCART_CART_PL, "Zamontuj surowy obraz kartridøa RamCart"},
	/* ru */ {IDCLS_ATTACH_RAW_RAMCART_CART_RU, "Attach raw RamCart cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_RAMCART_CART_SV, "Anslut rÂ RamCart-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_RAMCART_CART_TR, "D¸z RamCart kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_REU_CART,    N_("Attach raw REU cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_REU_CART_DA, "Tilslut rÂt REU cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_REU_CART_DE, "REU Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_REU_CART_ES, "Insertar imagen cartucho REU"},
	/* fr */ {IDCLS_ATTACH_RAW_REU_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_REU_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_REU_CART_IT, "Seleziona immagine cartuccia REU"},
	/* ko */ {IDCLS_ATTACH_RAW_REU_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_REU_CART_NL, "Koppel binair REU cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_REU_CART_PL, "Zamontuj surowy obraz kartridøa REU"},
	/* ru */ {IDCLS_ATTACH_RAW_REU_CART_RU, "Attach raw REU cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_REU_CART_SV, "Anslut rÂ REU-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_REU_CART_TR, "D¸z REU kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_REX_EP256_CART,    N_("Attach raw REX EP256 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_REX_EP256_CART_DA, "Tilslut rÂt REX EP256 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_REX_EP256_CART_DE, "REX EP256 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_REX_EP256_CART_ES, "Insertar imagen cartucho REX EP256"},
	/* fr */ {IDCLS_ATTACH_RAW_REX_EP256_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_REX_EP256_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_REX_EP256_CART_IT, "Seleziona immagine cartuccia REX EP256"},
	/* ko */ {IDCLS_ATTACH_RAW_REX_EP256_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_REX_EP256_CART_NL, "Koppel binair REX EP256 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_REX_EP256_CART_PL, "Zamontuj surowy obraz kartridøa REX EP256"},
	/* ru */ {IDCLS_ATTACH_RAW_REX_EP256_CART_RU, "Attach raw REX EP256 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_REX_EP256_CART_SV, "Anslut rÂ REX EP256-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_REX_EP256_CART_TR, "D¸z REX EP256 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_ROSS_CART,    N_("Attach raw 16/32kB ROSS cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_ROSS_CART_DA, "Tilslut rÂt 16/32kB ROSS cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_ROSS_CART_DE, "16/32kB ROSS Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_ROSS_CART_ES, "Insertar imagen cartucho ROSS 16/32KB"},
	/* fr */ {IDCLS_ATTACH_RAW_ROSS_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_ROSS_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_ROSS_CART_IT, "Seleziona immagine cartuccia ROSS di 16/32kB"},
	/* ko */ {IDCLS_ATTACH_RAW_ROSS_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_ROSS_CART_NL, "Koppel binair 16/32kB ROSS cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_ROSS_CART_PL, "Zamontuj surowy obraz kartridøa 12/32kB ROSS"},
	/* ru */ {IDCLS_ATTACH_RAW_ROSS_CART_RU, "Attach raw 16/32kB ROSS cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_ROSS_CART_SV, "Anslut rÂ 16/32kB ROSS-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_ROSS_CART_TR, "D¸z 16/32kB ROSS kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART,    N_("Attach raw 8KB Game Killer cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_DA, "Tilslut rÂt 8kB Game Killer cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_DE, "8KB Game Killer Erweiterungsmodul (raw) Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_ES, "Insertar imagen cartucho Game Killer 8KB"},
	/* fr */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_IT, "Seleziona immagine cartuccia Game Killer di 8KB"},
	/* ko */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_NL, "Koppel binair 8KB Game Killer cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_PL, "Zamontuj surowy obraz kartridøa 8KB Game Killer"},
	/* ru */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_RU, "Attach raw 8KB Game Killer cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_SV, "Anslut rÂ 8KB Game Killer-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_GAME_KILLER_CART_TR, "D¸z 8KB Game Killer kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_GEORAM_CART,    N_("Attach raw GEO-RAM cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_GEORAM_CART_DA, "Tilslut rÂt GEO-RAM cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_GEORAM_CART_DE, "GEO-RAM Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_GEORAM_CART_ES, "Insertar imagen cartucho GEO-RAM"},
	/* fr */ {IDCLS_ATTACH_RAW_GEORAM_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_GEORAM_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_GEORAM_CART_IT, "Seleziona immagine cartuccia GEO-RAM"},
	/* ko */ {IDCLS_ATTACH_RAW_GEORAM_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_GEORAM_CART_NL, "Koppel binair GEO-RAM cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_GEORAM_CART_PL, "Zamontuj surowy obraz kartridøa GEO-RAM"},
	/* ru */ {IDCLS_ATTACH_RAW_GEORAM_CART_RU, "Attach raw GEO-RAM cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_GEORAM_CART_SV, "Anslut rÂ GEO-RAM-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_GEORAM_CART_TR, "D¸z GEO-RAM kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART,    N_("Attach raw 512kB Game System cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_DA, "Tilslut rÂt 512kB Game System cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_DE, "512kB Game System Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_ES, "Insertar imagen cartucho Game System 512KB"},
	/* fr */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_IT, "Seleziona immagine cartuccia Game System di 512kB"},
	/* ko */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_NL, "Koppel binair 512kB Game System cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_PL, "Zamontuj surowy obraz kartridøa 512kB Game System"},
	/* ru */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_RU, "Attach raw 512kB Game System cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_SV, "Anslut rÂ 512kB Game System-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_GAME_SYSTEM_CART_TR, "D¸z 512kB Game System kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c, c64/expert.c */
	/* en */ {IDCLS_ENABLE_EXPERT_CART,    N_("Enable the Expert Cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_EXPERT_CART_DA, "AktivÈr Expert Cartridge"},
	/* de */ {IDCLS_ENABLE_EXPERT_CART_DE, "Expert Cartridge aktivieren"},
	/* es */ {IDCLS_ENABLE_EXPERT_CART_ES, "Permitir Expert Cartridge"},
	/* fr */ {IDCLS_ENABLE_EXPERT_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_EXPERT_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_EXPERT_CART_IT, "Attiva Expert Cartridge"},
	/* ko */ {IDCLS_ENABLE_EXPERT_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_EXPERT_CART_NL, "Activeer Expert Cartridge"},
	/* pl */ {IDCLS_ENABLE_EXPERT_CART_PL, "W≥±cz Expert Cartridge"},
	/* ru */ {IDCLS_ENABLE_EXPERT_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_EXPERT_CART_SV, "Aktivera Expert Cartridge"},
	/* tr */ {IDCLS_ENABLE_EXPERT_CART_TR, "Expert Kartu˛u'nu aktif et"},
#endif
	
	/* c64/expert.c */
	/* en */ {IDCLS_DISABLE_EXPERT_CART,    N_("Disable the Expert Cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_EXPERT_CART_DA, "DeaktivÈr Expert Cartridge"},
	/* de */ {IDCLS_DISABLE_EXPERT_CART_DE, "Expert Cartridge deaktivieren"},
	/* es */ {IDCLS_DISABLE_EXPERT_CART_ES, "Deshabilitar Expert Cartridge"},
	/* fr */ {IDCLS_DISABLE_EXPERT_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_EXPERT_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_EXPERT_CART_IT, "Disattiva Expert Cartridge"},
	/* ko */ {IDCLS_DISABLE_EXPERT_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_EXPERT_CART_NL, "Expert Cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_EXPERT_CART_PL, "Wy≥±cz Expert Cartridge"},
	/* ru */ {IDCLS_DISABLE_EXPERT_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_EXPERT_CART_SV, "Inaktivera Expert Cartridge"},
	/* tr */ {IDCLS_DISABLE_EXPERT_CART_TR, "Expert Kartu˛u'nu pasifle˛tir"},
#endif
	
	/* c64/expert.c */
	/* en */ {IDCLS_SET_EXPERT_FILENAME,    N_("Set Expert Cartridge image name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_EXPERT_FILENAME_DA, "VÊlg Expert Cartridge image-navn"},
	/* de */ {IDCLS_SET_EXPERT_FILENAME_DE, "Expert Cartridge Imagedateiname setzen"},
	/* es */ {IDCLS_SET_EXPERT_FILENAME_ES, "Seleccionar nombre imagen Expert Cartridge"},
	/* fr */ {IDCLS_SET_EXPERT_FILENAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_EXPERT_FILENAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_EXPERT_FILENAME_IT, "Imposta nome immagine Expert Cartridge"},
	/* ko */ {IDCLS_SET_EXPERT_FILENAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_EXPERT_FILENAME_NL, "Zet Expert Cartridge bestandsnaam"},
	/* pl */ {IDCLS_SET_EXPERT_FILENAME_PL, "Okre∂l nazwÍ obrazu Expert Cartridge"},
	/* ru */ {IDCLS_SET_EXPERT_FILENAME_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_SET_EXPERT_FILENAME_SV, "V‰lj Expert Cartridge-modulfil"},
	/* tr */ {IDCLS_SET_EXPERT_FILENAME_TR, "Expert Kartu˛ imaj ismini belirle"},
#endif
	
	/* c64/expert.c */
	/* en */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE,    N_("Allow writing to Expert Cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_DA, "Tillad skrivning til Expert Cartridge image"},
	/* de */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_DE, "Schreibzugriff auf Expert Cartridge Image erlauben"},
	/* es */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_ES, "Permitir grabaciÛn en Expert Cartridge"},
	/* fr */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_IT, "Attiva scrittura su immagine Expert Cartridge"},
	/* ko */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_NL, "Activeer schrijven naar Expert Cartridge bestand"},
	/* pl */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_PL, "PozwÛl na zapis do obrazu Expert Cartridge"},
	/* ru */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_RU, "Allow writing to Expert Cartridge image"},
	/* sv */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_SV, "TillÂt skrivning till Expert Cartridge-avbildning"},
	/* tr */ {IDCLS_ALLOW_WRITING_TO_EXPERT_IMAGE_TR, "Expert Kartu˛ imaj˝na yazmaya izin ver"},
#endif
	
	/* c64/expert.c */
	/* en */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE,    N_("Do not write to Expert Cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_DA, "Skriv ikke til Expert Cartridge image"},
	/* de */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_DE, "Kein Schreibzugriff auf Expert Cartridge Image"},
	/* es */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_ES, "Deshabilitar grabaciÛn en Expert Cartridge"},
	/* fr */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_IT, "Disattiva scrittura su immagine Expert Cartridge"},
	/* ko */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_NL, "Schrijf niet naar Expert Cartridge bestand"},
	/* pl */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_PL, "Nie zapisuj do obrazu Expert Cartridge"},
	/* ru */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_RU, "Do not write to Expert Cartridge image"},
	/* sv */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_SV, "Skriv inte till Expert Cartridge-avbildning"},
	/* tr */ {IDCLS_DO_NOT_WRITE_TO_EXPERT_IMAGE_TR, "Expert Kartu˛ imaj˝na yazma"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_DISABLE_CART,    N_("Disable default cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_CART_DA, "DeaktivÈr standard cartridge"},
	/* de */ {IDCLS_DISABLE_CART_DE, "Standard Modul deaktivieren"},
	/* es */ {IDCLS_DISABLE_CART_ES, "Deshabilitar cartucho por defecto"},
	/* fr */ {IDCLS_DISABLE_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_CART_HU, "Alap cartridge tilt·sa"},
	/* it */ {IDCLS_DISABLE_CART_IT, "Disattiva cartuccia predefinita"},
	/* ko */ {IDCLS_DISABLE_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_CART_NL, "De standaard cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_CART_PL, "Wy≥±cz domy∂lny kartridø"},
	/* ru */ {IDCLS_DISABLE_CART_RU, "Disable default cartridge"},
	/* sv */ {IDCLS_DISABLE_CART_SV, "Inaktivera standardinsticksmodul"},
	/* tr */ {IDCLS_DISABLE_CART_TR, "Varsay˝lan kartu˛u pasifle˛tir"},
#endif
	
	/* plus4/plus4cart.c */
	/* en */ {IDCLS_SMART_ATTACH_CART,    N_("Smart-attach cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SMART_ATTACH_CART_DA, "Smart-tilslut cartridge-image"},
	/* de */ {IDCLS_SMART_ATTACH_CART_DE, "Smart-Einlegen Modul Image"},
	/* es */ {IDCLS_SMART_ATTACH_CART_ES, "Insertar imagen cartucho inteligentemente"},
	/* fr */ {IDCLS_SMART_ATTACH_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SMART_ATTACH_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SMART_ATTACH_CART_IT, "Seleziona una cartuccia"},
	/* ko */ {IDCLS_SMART_ATTACH_CART_KO, "ƒ´∆Æ∏Æ¡ˆ ¿ÃπÃ¡ˆ∏¶ Ω∫∏∂∆Æ-∫Ÿ¿Ã±‚ «œ±‚"},
	/* nl */ {IDCLS_SMART_ATTACH_CART_NL, "Slim-koppel cartridge bestand"},
	/* pl */ {IDCLS_SMART_ATTACH_CART_PL, "Inteligentnie zamontuj obraz kartridøa"},
	/* ru */ {IDCLS_SMART_ATTACH_CART_RU, "Smart-attach cartridge image"},
	/* sv */ {IDCLS_SMART_ATTACH_CART_SV, "Smartanslut insticksmodulfil"},
	/* tr */ {IDCLS_SMART_ATTACH_CART_TR, "Ak˝ll˝ kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_SPECIFY_IDE64_NAME,    N_("Specify name of IDE64 image file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_IDE64_NAME_DA, "Angiv navn pÂ IDE64-cartridge image"},
	/* de */ {IDCLS_SPECIFY_IDE64_NAME_DE, "Namen f¸r IDE64 Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_IDE64_NAME_ES, "Especificar nombre fichero imagen IDE64"},
	/* fr */ {IDCLS_SPECIFY_IDE64_NAME_FR, "SpÈcifier le nom de l'image IDE64"},
	/* hu */ {IDCLS_SPECIFY_IDE64_NAME_HU, "Adja meg az IDE64 kÈpm·s f·jlnevÈt"},
	/* it */ {IDCLS_SPECIFY_IDE64_NAME_IT, "Specifica il nome del file immagine dell'IDE64"},
	/* ko */ {IDCLS_SPECIFY_IDE64_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_IDE64_NAME_NL, "Geef de naam van het IDE64 bestand"},
	/* pl */ {IDCLS_SPECIFY_IDE64_NAME_PL, "Okre∂l nazwÍ pliku obrazu IDE64"},
	/* ru */ {IDCLS_SPECIFY_IDE64_NAME_RU, "Specify name of IDE64 image file"},
	/* sv */ {IDCLS_SPECIFY_IDE64_NAME_SV, "Ange namn pÂ IDE64-insticksmodulfil"},
	/* tr */ {IDCLS_SPECIFY_IDE64_NAME_TR, "IDE64 imaj dosyas˝n˝n ismini belirt"},
#endif
	
	/* c64/cart/ide64.c, gfxoutputdrv/ffmpegdrv.c, datasette.c,
	 debug.c, mouse.c, ram.c, sound.c, vsync.c */
	/* en */ {IDCLS_P_VALUE,    N_("<value>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_VALUE_DA, "<vÊrdi>"},
	/* de */ {IDCLS_P_VALUE_DE, "<Wert>"},
	/* es */ {IDCLS_P_VALUE_ES, "<valor>"},
	/* fr */ {IDCLS_P_VALUE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_VALUE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_VALUE_IT, "<valore>"},
	/* ko */ {IDCLS_P_VALUE_KO, "<∞°ƒ°>"},
	/* nl */ {IDCLS_P_VALUE_NL, "<waarde>"},
	/* pl */ {IDCLS_P_VALUE_PL, "<warto∂Ê>"},
	/* ru */ {IDCLS_P_VALUE_RU, "<value>"},
	/* sv */ {IDCLS_P_VALUE_SV, "<v‰rde>"},
	/* tr */ {IDCLS_P_VALUE_TR, "<deer>"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64,    N_("Set number of cylinders for the IDE64 emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_DA, "VÊlg antal cylindrer for IDE64-emuleringen"},
	/* de */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_DE, "Anzahl der Zylinder f¸r IDE64 Emulation"},
	/* es */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_ES, "Seleccionar n˙mero de cilindros para emulaciÛn IDE64"},
	/* fr */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_FR, "RÈgler le nombre de cylindres pour l'Èmulation IDE64"},
	/* hu */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_HU, "Adja meg a s·vok sz·m·t IDE64 emul·ciÛhoz"},
	/* it */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_IT, "Imposta il numero di cilindri dell'emulazione IDE64"},
	/* ko */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_NL, "Stel het aantal cylinders voor de IDE64 emulatie in"},
	/* pl */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_PL, "Ustaw liczbÍ cylindrÛw w emulacji IDE64"},
	/* ru */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_RU, "Set number of cylinders for the IDE64 emulation"},
	/* sv */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_SV, "V‰lj antal cylindrar fˆr IDE64-emuleringen"},
	/* tr */ {IDCLS_SET_AMOUNT_CYLINDERS_IDE64_TR, "IDE64 em¸lasyonu iÁin silindir adedini girin"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_SET_AMOUNT_HEADS_IDE64,    N_("Set number of heads for the IDE64 emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_AMOUNT_HEADS_IDE64_DA, "VÊlg antal hoveder for IDE64-emuleringen"},
	/* de */ {IDCLS_SET_AMOUNT_HEADS_IDE64_DE, "Anzahl der Laufwerkskˆpfe f¸r IDE64 Emulation"},
	/* es */ {IDCLS_SET_AMOUNT_HEADS_IDE64_ES, "Seleccionar n˙mero de cabezas para emulaciÛn IDE64"},
	/* fr */ {IDCLS_SET_AMOUNT_HEADS_IDE64_FR, "RÈgler le nombre de tÍtes pour l'Èmulation IDE64"},
	/* hu */ {IDCLS_SET_AMOUNT_HEADS_IDE64_HU, "Adja meg a fejek sz·m·t IDE64 emul·ciÛhoz"},
	/* it */ {IDCLS_SET_AMOUNT_HEADS_IDE64_IT, "Imposta il numero di testine dell'emulazione IDE64"},
	/* ko */ {IDCLS_SET_AMOUNT_HEADS_IDE64_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_AMOUNT_HEADS_IDE64_NL, "Stel het aantal koppen voor de IDE64 emulatie in"},
	/* pl */ {IDCLS_SET_AMOUNT_HEADS_IDE64_PL, "Ustaw liczbÍ g≥owic w emulacji IDE64"},
	/* ru */ {IDCLS_SET_AMOUNT_HEADS_IDE64_RU, "Set number of heads for the IDE64 emulation"},
	/* sv */ {IDCLS_SET_AMOUNT_HEADS_IDE64_SV, "Ange antal huvuden fˆr IDE64-emuleringen"},
	/* tr */ {IDCLS_SET_AMOUNT_HEADS_IDE64_TR, "IDE64 em¸lasyonu iÁin kafa adedini girin"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_SET_AMOUNT_SECTORS_IDE64,    N_("Set number of sectors for the IDE64 emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_DA, "VÊlg antal sektorer for IDE64-emuleringen"},
	/* de */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_DE, "Anzahl der Sektoren f¸r IDE64 Emulation"},
	/* es */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_ES, "Seleccionar n˙mero de sectores para emulaciÛn IDE64"},
	/* fr */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_FR, "RÈgler le nombre de secteurs pour l'Èmulation IDE64"},
	/* hu */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_HU, "Adja meg a szektorok sz·m·t IDE64 emul·ciÛhoz"},
	/* it */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_IT, "Imposta il numero di settori dell'emulazione IDE64"},
	/* ko */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_NL, "Stel het aantal sectors voor de IDE64 emulatie in"},
	/* pl */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_PL, "Ustaw liczbÍ sektorÛw w emulacji IDE64"},
	/* ru */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_RU, "Set number of sectors for the IDE64 emulation"},
	/* sv */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_SV, "Ange antal sektorer fˆr IDE64-emuleringen"},
	/* tr */ {IDCLS_SET_AMOUNT_SECTORS_IDE64_TR, "IDE64 em¸lasyonu iÁin sektˆr adedini girin"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_AUTODETECT_IDE64_GEOMETRY,    N_("Autodetect image size")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_DA, "AutodetektÈr st¯rrelse pÂ image"},
	/* de */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_DE, "Image Grˆﬂe automatisch erkennen"},
	/* es */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_ES, "AutodetecciÛn del tamaÒo de la imagen"},
	/* fr */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_IT, "Rileva automaticamente immagine"},
	/* ko */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_KO, "¿ÃπÃ¡ˆ ≈©±‚ ¿⁄µø¿∏∑Œ √£±‚"},
	/* nl */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_NL, "Automatisch detecteren bestandsgrootte"},
	/* pl */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_PL, "Automatycznie wykrywaj rozmiar obrazu"},
	/* ru */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_RU, "∞“‚ﬁ‹–‚ÿÁ’·⁄ﬁ’ ﬁﬂ‡’‘’€’›ÿ’ ‡–◊‹’‡– ÿ◊ﬁ—‡–÷’›ÿÔ"},
	/* sv */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_SV, "Autodetektera storlek pÂ avbildning"},
	/* tr */ {IDCLS_AUTODETECT_IDE64_GEOMETRY_TR, "Imaj boyutunu otomatik alg˝la"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY,    N_("Do not autodetect geometry of formatted images")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_DA, "AutodetektÈr ikke geometri fra formatterede images"},
	/* de */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_DE, "Geometrie von formatierten Image Dateien nicht automatisch erkennen"},
	/* es */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_ES, "No autodetectar formato geometria imagenes"},
	/* fr */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_FR, "Ne pas dÈtecter automatiquement la gÈomÈtrie des images formattÈes"},
	/* hu */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_HU, "Form·zott kÈpm·sok geometri·j·t ne ismerje fel automatikusan"},
	/* it */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_IT, "Non rilevare automaticamente la geometrica delle immagini formattate"},
	/* ko */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_NL, "Niet automatisch de grootte van de geformateerde bestanden detecteren"},
	/* pl */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_PL, "Nie wykrywaj geometrii sformatowanych obrazÛw"},
	/* ru */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_RU, "Do not autodetect geometry of formatted images"},
	/* sv */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_SV, "Autodetektera inte geometri frÂn formaterad avbildningsfil"},
	/* tr */ {IDCLS_NO_AUTODETECT_IDE64_GEOMETRY_TR, "Formatlanm˝˛ imajlar˝n yap˝lar˝n˝ otomatik alg˝lama"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_IDE64_V4,    N_("Emulate version 4 hardware")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_IDE64_V4_DA, "EmulÈr version 4 hardware"},
	/* de */ {IDCLS_IDE64_V4_DE, "Emulation der Version 5 Hardware"},
	/* es */ {IDCLS_IDE64_V4_ES, "Emular versiÛn 4 hardware"},
	/* fr */ {IDCLS_IDE64_V4_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_IDE64_V4_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_IDE64_V4_IT, "Emula hardware versione 4"},
	/* ko */ {IDCLS_IDE64_V4_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_IDE64_V4_NL, "Emuleer versie 4 hardware"},
	/* pl */ {IDCLS_IDE64_V4_PL, "Emuluj sprzÍt w wersji 4"},
	/* ru */ {IDCLS_IDE64_V4_RU, "Emulate version 4 hardware"},
	/* sv */ {IDCLS_IDE64_V4_SV, "Emulera version 4-maskinvara"},
	/* tr */ {IDCLS_IDE64_V4_TR, "Versiyon 4 donan˝m˝n˝ em¸le et"},
#endif
	
	/* c64/cart/ide64.c */
	/* en */ {IDCLS_IDE64_PRE_V4,    N_("Emulate pre version 4 hardware")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_IDE64_PRE_V4_DA, "EmulÈr hardware f¯r version 4"},
	/* de */ {IDCLS_IDE64_PRE_V4_DE, "Emulation der pre-Version 4 Hardware"},
	/* es */ {IDCLS_IDE64_PRE_V4_ES, "Emular preversiÛn 4 hardware"},
	/* fr */ {IDCLS_IDE64_PRE_V4_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_IDE64_PRE_V4_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_IDE64_PRE_V4_IT, "Emula hardware pre-versione 4"},
	/* ko */ {IDCLS_IDE64_PRE_V4_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_IDE64_PRE_V4_NL, "Emuleer hardware van voor versie 4"},
	/* pl */ {IDCLS_IDE64_PRE_V4_PL, "Emuluj sprzÍt sprzed wersji 4"},
	/* ru */ {IDCLS_IDE64_PRE_V4_RU, "Emulate pre version 4 hardware"},
	/* sv */ {IDCLS_IDE64_PRE_V4_SV, "Emulera fˆr-version 4-maskinvara"},
	/* tr */ {IDCLS_IDE64_PRE_V4_TR, "÷n versiyon 4 donan˝m˝n˝ em¸le et"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_P_MODELNUMBER,    N_("<modelnumber>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_MODELNUMBER_DA, "<modelnummer>"},
	/* de */ {IDCLS_P_MODELNUMBER_DE, "<Modell Nummer>"},
	/* es */ {IDCLS_P_MODELNUMBER_ES, "<n˙mero modelo>"},
	/* fr */ {IDCLS_P_MODELNUMBER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_MODELNUMBER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_MODELNUMBER_IT, "<numero di modello>"},
	/* ko */ {IDCLS_P_MODELNUMBER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_MODELNUMBER_NL, "<modelnummer>"},
	/* pl */ {IDCLS_P_MODELNUMBER_PL, "<modelnumber>"},
	/* ru */ {IDCLS_P_MODELNUMBER_RU, "<modelnumber>"},
	/* sv */ {IDCLS_P_MODELNUMBER_SV, "<modellnummer>"},
	/* tr */ {IDCLS_P_MODELNUMBER_TR, "<modelnumaras˝>"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CBM2_MODEL,    N_("Specify CBM-II model to emulate")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CBM2_MODEL_DA, "Angiv emuleret CBM-II-model"},
	/* de */ {IDCLS_SPECIFY_CBM2_MODEL_DE, "CBM-II Modell f¸r Emulation definieren"},
	/* es */ {IDCLS_SPECIFY_CBM2_MODEL_ES, "Especificar modelo CBM-II para emular"},
	/* fr */ {IDCLS_SPECIFY_CBM2_MODEL_FR, "SpÈcifier le modËle CBM-II ‡ Èmuler"},
	/* hu */ {IDCLS_SPECIFY_CBM2_MODEL_HU, "Adja meg az emul·landÛ CBM-II modell sz·m·t"},
	/* it */ {IDCLS_SPECIFY_CBM2_MODEL_IT, "Specifica il modello di CBM II da emulare"},
	/* ko */ {IDCLS_SPECIFY_CBM2_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CBM2_MODEL_NL, "Geef CBM-II model om te emuleren"},
	/* pl */ {IDCLS_SPECIFY_CBM2_MODEL_PL, "Okre∂l emulowany model CBM-II"},
	/* ru */ {IDCLS_SPECIFY_CBM2_MODEL_RU, "Specify CBM-II model to emulate"},
	/* sv */ {IDCLS_SPECIFY_CBM2_MODEL_SV, "Ange CBM-II-modell att emulera"},
	/* tr */ {IDCLS_SPECIFY_CBM2_MODEL_TR, "Em¸le edilecek CBM-II modelini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_TO_USE_VIC_II,    N_("Specify to use VIC-II")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_TO_USE_VIC_II_DA, "Brug VIC-II"},
	/* de */ {IDCLS_SPECIFY_TO_USE_VIC_II_DE, "VIC-II Unterst¸tzung aktivieren"},
	/* es */ {IDCLS_SPECIFY_TO_USE_VIC_II_ES, "Especificar usar CBM-II"},
	/* fr */ {IDCLS_SPECIFY_TO_USE_VIC_II_FR, "SpÈcifier l'utilisation de VIC-II"},
	/* hu */ {IDCLS_SPECIFY_TO_USE_VIC_II_HU, "VIC-II haszn·lata"},
	/* it */ {IDCLS_SPECIFY_TO_USE_VIC_II_IT, "Specifica di utilizzare il VIC-II"},
	/* ko */ {IDCLS_SPECIFY_TO_USE_VIC_II_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_TO_USE_VIC_II_NL, "Gebruik de VIC-II"},
	/* pl */ {IDCLS_SPECIFY_TO_USE_VIC_II_PL, "Okre∂l uøycie VIC-II"},
	/* ru */ {IDCLS_SPECIFY_TO_USE_VIC_II_RU, "Specify to use VIC-II"},
	/* sv */ {IDCLS_SPECIFY_TO_USE_VIC_II_SV, "Ange fˆr att anv‰nda VIC-II"},
	/* tr */ {IDCLS_SPECIFY_TO_USE_VIC_II_TR, "VIC-II kullan˝m˝ iÁin seÁin"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_TO_USE_CRTC,    N_("Specify to use CRTC")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_TO_USE_CRTC_DA, "Brug CRTC"},
	/* de */ {IDCLS_SPECIFY_TO_USE_CRTC_DE, "CRTC Unterst¸tzung aktivieren"},
	/* es */ {IDCLS_SPECIFY_TO_USE_CRTC_ES, "Especificar usar CRT"},
	/* fr */ {IDCLS_SPECIFY_TO_USE_CRTC_FR, "SpÈcifier l'utilisation de CRTC"},
	/* hu */ {IDCLS_SPECIFY_TO_USE_CRTC_HU, "CRTC haszn·lata"},
	/* it */ {IDCLS_SPECIFY_TO_USE_CRTC_IT, "Specifica di utilizzare il CRTC"},
	/* ko */ {IDCLS_SPECIFY_TO_USE_CRTC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_TO_USE_CRTC_NL, "Gebruik de CRTC"},
	/* pl */ {IDCLS_SPECIFY_TO_USE_CRTC_PL, "Okre∂l uøycie CRTC"},
	/* ru */ {IDCLS_SPECIFY_TO_USE_CRTC_RU, "Specify to use CRTC"},
	/* sv */ {IDCLS_SPECIFY_TO_USE_CRTC_SV, "Ange fˆr att anv‰nda CRTC"},
	/* tr */ {IDCLS_SPECIFY_TO_USE_CRTC_TR, "CRTC kullan˝m˝ iÁin seÁin"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_P_LINENUMBER,    N_("<linenumber>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_LINENUMBER_DA, "<linjenummer>"},
	/* de */ {IDCLS_P_LINENUMBER_DE, "<Zeilennummer>"},
	/* es */ {IDCLS_P_LINENUMBER_ES, "<n˙mero linea>"},
	/* fr */ {IDCLS_P_LINENUMBER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_LINENUMBER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_LINENUMBER_IT, "<numero di linea>"},
	/* ko */ {IDCLS_P_LINENUMBER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_LINENUMBER_NL, "<lijnnummer>"},
	/* pl */ {IDCLS_P_LINENUMBER_PL, "<linenumber>"},
	/* ru */ {IDCLS_P_LINENUMBER_RU, "<linenumber>"},
	/* sv */ {IDCLS_P_LINENUMBER_SV, "<linjenummer>"},
	/* tr */ {IDCLS_P_LINENUMBER_TR, "<sat˝rnumaras˝>"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE,    N_("Specify CBM-II model hardware (0=6x0, 1=7x0)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_DA, "Angiv hardware for CBM-II-model (0=6x0, 1=7x0)"},
	/* de */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_DE, "CBM-II Hardware Modell definieren (0=6x0, 1=7x0)"},
	/* es */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_ES, "Especificar modelo hardware CBM-II (0=6x0, 1=7x0)"},
	/* fr */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_FR, "SpÈcifier le modËle hardware CBM-II (0=6x0, 1=7x0)"},
	/* hu */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_HU, "Adja meg a CBM-II hardver modellt (0=6x0, 1=7x0)"},
	/* it */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_IT, "Specifica il modello hardware del CBM-II (0=6x0, 1=7x0)"},
	/* ko */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_NL, "Geef CBM-II hardwaremodel (0=6x0, 1=7x0)"},
	/* pl */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_PL, "Okre∂l model sprzÍtu CBM-II (0=6x0, 1=7x0)"},
	/* ru */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_RU, "Specify CBM-II model hardware (0=6x0, 1=7x0)"},
	/* sv */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_SV, "Ange maskinvara fˆr CBM-II-modell (0=6x0, 1=7x0)"},
	/* tr */ {IDCLS_SPECIFY_CBM2_MODEL_HARDWARE_TR, "CBM-II modeli donan˝m˝n˝ belirt (0=6x0, 1=7x0)"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_P_RAMSIZE,    N_("<RAM size>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_RAMSIZE_DA, "<RAM-st¯rrelse>"},
	/* de */ {IDCLS_P_RAMSIZE_DE, "<RAM Grˆﬂe>"},
	/* es */ {IDCLS_P_RAMSIZE_ES, "<TamaÒo RAM>"},
	/* fr */ {IDCLS_P_RAMSIZE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_RAMSIZE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_RAMSIZE_IT, "<Dimensione RAM>"},
	/* ko */ {IDCLS_P_RAMSIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_RAMSIZE_NL, "<RAM grootte>"},
	/* pl */ {IDCLS_P_RAMSIZE_PL, "<Rozmiar RAM>"},
	/* ru */ {IDCLS_P_RAMSIZE_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_P_RAMSIZE_SV, "<RAM-storlek>"},
	/* tr */ {IDCLS_P_RAMSIZE_TR, "<RAM boyutu>"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_SIZE_OF_RAM,    N_("Specify size of RAM (64/128/256/512/1024 kByte)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SIZE_OF_RAM_DA, "Angiv st¯rrelse pÂ RAM (64/128/256/512/1024 kByte)"},
	/* de */ {IDCLS_SPECIFY_SIZE_OF_RAM_DE, "RAM Grˆﬂe definieren (64/128/256/512/1024 kByte)"},
	/* es */ {IDCLS_SPECIFY_SIZE_OF_RAM_ES, "Especificar tamaÒo RAM  (64/128/256/512/1024 KB)"},
	/* fr */ {IDCLS_SPECIFY_SIZE_OF_RAM_FR, "SpÈcifier la taille de la RAM (64/128/256/512/1024 KO)"},
	/* hu */ {IDCLS_SPECIFY_SIZE_OF_RAM_HU, "Adja meg a RAM mÈretÈt (64/128/256/512/1024 kB·jt)"},
	/* it */ {IDCLS_SPECIFY_SIZE_OF_RAM_IT, "Specifica la dimensione della RAM (4/128/256/512/1024 kByte)"},
	/* ko */ {IDCLS_SPECIFY_SIZE_OF_RAM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SIZE_OF_RAM_NL, "Geef geheugengrootte (64/128/256/512/1024 kByte)"},
	/* pl */ {IDCLS_SPECIFY_SIZE_OF_RAM_PL, "Okre∂l rozmiar RAM-u (64/128/256/512/1024 kBajty)"},
	/* ru */ {IDCLS_SPECIFY_SIZE_OF_RAM_RU, "Specify size of RAM (64/128/256/512/1024 kByte)"},
	/* sv */ {IDCLS_SPECIFY_SIZE_OF_RAM_SV, "Ange storlek pÂ RAM (64/128/256/512/1024 kByte)"},
	/* tr */ {IDCLS_SPECIFY_SIZE_OF_RAM_TR, "RAM boyutunu belirt (64/128/256/512/1024 kByte)"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_ROM_1000_NAME,    N_("Specify name of cartridge ROM image for $1000")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_DA, "Angiv navn pÂ cartridge-ROM-image for $1000"},
	/* de */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_DE, "Name f¸r ROM Module Image Datei ($1000)"},
	/* es */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_ES, "Especificar nombre imagen cartucho ROM para $1000"},
	/* fr */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_FR, "SpÈcifier le nom de líimage de cartouche ROM pour $1000"},
	/* hu */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_HU, "Adja meg a $1000 cÌm˚ cartridge ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_IT, "Specifica il nome immagine della cartuccia ROM a $1000"},
	/* ko */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_NL, "Geef de naam van het cartridge ROM bestand voor $1000"},
	/* pl */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_PL, "Okre∂l nazwÍ obrazu ROM kartridøa w $1000"},
	/* ru */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_RU, "Specify name of cartridge ROM image for $1000"},
	/* sv */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_SV, "Ange namn pÂ insticksmodul-ROM-avbildning fˆr $1000"},
	/* tr */ {IDCLS_SPECIFY_CART_ROM_1000_NAME_TR, "$1000 adresi iÁin kartu˛ ROM imaj ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_ROM_2000_NAME,    N_("Specify name of cartridge ROM image for $2000-$3fff")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_DA, "Angiv navn pÂ cartridge-ROM-image for $2000-3fff"},
	/* de */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_DE, "Name f¸r ROM Module Image Datei ($2000-3fff)"},
	/* es */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_ES, "Especificar nombre imagen cartucho ROM para $2000-$3FFF"},
	/* fr */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_FR, "SpÈcifier le nom de líimage de cartouche ROM pour $2000-$3fff"},
	/* hu */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_HU, "Adja meg a $2000-$3fff cÌm˚ cartridge ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_IT, "Specifica il nome immagine della ROM della cartuccia per $2000-$3fff"},
	/* ko */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_NL, "Geef de naam van het cartridge ROM bestand voor $2000-$3fff"},
	/* pl */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_PL, "Okre∂l nazwÍ obrazu ROM kartridøa w $2000-$3fff"},
	/* ru */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_RU, "Specify name of cartridge ROM image for $2000-$3fff"},
	/* sv */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_SV, "Ange namn pÂ insticksmodul-ROM-avbildning fˆr $2000-3fff"},
	/* tr */ {IDCLS_SPECIFY_CART_ROM_2000_NAME_TR, "$2000-$3fff adres aral˝˝ iÁin kartu˛ ROM imaj ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_ROM_4000_NAME,    N_("Specify name of cartridge ROM image for $4000-$5fff")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_DA, "Angiv navn pÂ cartridge-ROM-image for $4000-$5fff"},
	/* de */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_DE, "Name f¸r ROM Module Image Datei ($4000-5fff)"},
	/* es */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_ES, "Especificar nombre imagen cartucho ROM para $4000-$5FFF"},
	/* fr */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_FR, "SpÈcifier le nom de líimage de cartouche ROM pour $4000-$5fff"},
	/* hu */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_HU, "Adja meg a $4000-$5fff cÌm˚ cartridge ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_IT, "Specifica il nome immagine della ROM della cartuccia per $4000-$5fff"},
	/* ko */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_NL, "Geef de naam van het cartridge ROM bestand voor $4000-$5fff"},
	/* pl */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_PL, "Okre∂l nazwÍ obrazu ROM kartridøa w $4000-$5fff"},
	/* ru */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_RU, "Specify name of cartridge ROM image for $4000-$5fff"},
	/* sv */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_SV, "Ange namn pÂ insticksmodul-ROM-avbildning fˆr $4000-$5fff"},
	/* tr */ {IDCLS_SPECIFY_CART_ROM_4000_NAME_TR, "$4000-$5fff adres aral˝˝ iÁin kartu˛ ROM imaj ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_ROM_6000_NAME,    N_("Specify name of cartridge ROM image for $6000-$7fff")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_DA, "Angiv navn pÂ cartridge-ROM-image for $6000-$7fff"},
	/* de */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_DE, "Name f¸r ROM Module Image Datei ($6000-7fff)"},
	/* es */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_ES, "Especificar nombre imagen cartucho ROM para $6000-$7FFF"},
	/* fr */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_FR, "SpÈcifier le nom de líimage de cartouche ROM pour $6000-$7fff"},
	/* hu */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_HU, "Adja meg a $6000-$7fff cÌm˚ cartridge ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_IT, "Specifica il nome immagine della ROM della cartuccia per $6000-$7fff"},
	/* ko */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_NL, "Geef de naam van het cartridge ROM bestand voor $6000-$7fff"},
	/* pl */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_PL, "Okre∂l nazwÍ obrazu ROM kartridøa w $6000-$7fff"},
	/* ru */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_RU, "Specify name of cartridge ROM image for $6000-$7fff"},
	/* sv */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_SV, "Ange namn pÂ insticksmodul-ROM-avbildning fˆr $6000-$7fff"},
	/* tr */ {IDCLS_SPECIFY_CART_ROM_6000_NAME_TR, "$6000-$7fff adres aral˝˝ iÁin kartu˛ ROM imaj ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800,    N_("Enable RAM mapping in $0800-$0FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_DA, "AktivÈr RAM-mappning pÂ $0800-$0FFF"},
	/* de */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_DE, "RAM Zuordnung in $0800-$0FFF aktivieren"},
	/* es */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_ES, "Permitir mapeado RAM en $0800-$0FFF"},
	/* fr */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_FR, "Activer le mappage RAM dans $0800-$0FFF"},
	/* hu */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_HU, "$0800-$0FFF RAM lekÈpzÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_IT, "Attiva mappatura della RAM a $0800-$0FFF"},
	/* ko */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_NL, "Activeer RAM op adres $0800-$0FFF"},
	/* pl */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_PL, "W≥±cz mapowanie RAM w $0800-$0FFF"},
	/* ru */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_RU, "Enable RAM mapping in $0800-$0FFF"},
	/* sv */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_SV, "Aktivera RAM-mappning pÂ $0800-$0FFF"},
	/* tr */ {IDCLS_ENABLE_RAM_MAPPING_IN_0800_TR, "$0800-$0FFF aral˝˝nda RAM e˛le˛tirmeyi aktif et"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800,    N_("Disable RAM mapping in $0800-$0FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_DA, "DeaktivÈr RAM-mappning pÂ $0800-$0FFF"},
	/* de */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_DE, "RAM Zuordnung in $0800-$0FFF deaktivieren"},
	/* es */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_ES, "Deshabilitar mapeado RAM en $0800-$0FFF"},
	/* fr */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_FR, "DÈsactiver le mappage RAM dans $0800-$0FFF"},
	/* hu */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_HU, "$0800-$0FFF RAM lekÈpzÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_IT, "Disattiva mappatura della RAM a $0800-$0FFF"},
	/* ko */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_NL, "RAM op adres $0800-$0FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_PL, "Wy≥±cz mapowanie RAM w $0800-$0FFF"},
	/* ru */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_RU, "Disable RAM mapping in $0800-$0FFF"},
	/* sv */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_SV, "Inaktivera RAM-mappning pÂ $0800-$0FFF"},
	/* tr */ {IDCLS_DISABLE_RAM_MAPPING_IN_0800_TR, "$0800-$0FFF aral˝˝nda RAM e˛le˛tirmeyi pasifle˛tir"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000,    N_("Enable RAM mapping in $1000-$1FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_DA, "AktivÈr RAM-mappning pÂ $1000-$1FFF"},
	/* de */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_DE, "RAM Zuordnung in $1000-$1FFF aktivieren"},
	/* es */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_ES, "Permitir mapeado RAM en $1000-$1FFF"},
	/* fr */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_FR, "Activer le mappage RAM dans $1000-$1FFF"},
	/* hu */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_HU, "$1000-$1FFF RAM lekÈpzÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_IT, "Attiva mappatura della RAM a $1000-$1FFF"},
	/* ko */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_NL, "Activeer RAM op adres $1000-$1FFF"},
	/* pl */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_PL, "W≥±cz mapowanie RAM w $1000-$1FFF"},
	/* ru */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_RU, "Enable RAM mapping in $1000-$1FFF"},
	/* sv */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_SV, "Aktivera RAM-mappning pÂ $1000-$1FFF"},
	/* tr */ {IDCLS_ENABLE_RAM_MAPPING_IN_1000_TR, "$1000-$1FFF aral˝˝nda RAM e˛le˛tirmeyi aktif et"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000,    N_("Disable RAM mapping in $1000-$1FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_DA, "DeaktivÈr RAM-mappning pÂ $1000-$1FFF"},
	/* de */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_DE, "RAM Zuordnung in $1000-$1FFF deaktivieren"},
	/* es */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_ES, "Deshabilitar mapeado RAM en $1000-$1FFF"},
	/* fr */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_FR, "DÈsactiver le mappage RAM dans $1000-$1FFF"},
	/* hu */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_HU, "$1000-$1FFF RAM lekÈpzÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_IT, "Disattiva mappatura della RAM a $1000-$1FFF"},
	/* ko */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_NL, "RAM op adres $1000-$1FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_PL, "Wy≥±cz mapowanie RAM w $1000-$1FFF"},
	/* ru */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_RU, "Disable RAM mapping in $1000-$1FFF"},
	/* sv */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_SV, "Inaktivera RAM-mappning pÂ $1000-$1FFF"},
	/* tr */ {IDCLS_DISABLE_RAM_MAPPING_IN_1000_TR, "$1000-$1FFF aral˝˝nda RAM e˛le˛tirmeyi pasifle˛tir"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000,    N_("Enable RAM mapping in $2000-$3FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_DA, "AktivÈr RAM-mappning pÂ $2000-$3FFF"},
	/* de */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_DE, "RAM Zuordnung in $2000-3FFF aktivieren"},
	/* es */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_ES, "Permitir mapeado RAM en $2000-$3FFF"},
	/* fr */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_FR, "Activer le mappage RAM dans $2000-$3FFF"},
	/* hu */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_HU, "$2000-$3FFF RAM lekÈpzÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_IT, "Attiva mappatura della RAM a $2000-$3FFF"},
	/* ko */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_NL, "Activeer RAM op adres $2000-$3FFF"},
	/* pl */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_PL, "W≥±cz mapowanie RAM w $2000-$3FFF"},
	/* ru */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_RU, "Enable RAM mapping in $2000-$3FFF"},
	/* sv */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_SV, "Aktivera RAM-mappning pÂ $2000-$3FFF"},
	/* tr */ {IDCLS_ENABLE_RAM_MAPPING_IN_2000_TR, "$2000-$3FFF aral˝˝nda RAM e˛le˛tirmeyi aktif et"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000,    N_("Disable RAM mapping in $2000-$3FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_DA, "DeaktivÈr RAM-mappning pÂ $2000-$3FFF"},
	/* de */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_DE, "RAM Zuordnung in $2000-$3FFF deaktivieren"},
	/* es */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_ES, "Deshabilitar mapeado RAM en $2000-$3FFF"},
	/* fr */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_FR, "DÈsactiver le mappage RAM dans $2000-$3FFF"},
	/* hu */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_HU, "$2000-$3FFF RAM lekÈpzÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_IT, "Disattiva mappatura della RAM a $2000-$3FFF"},
	/* ko */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_NL, "RAM op adres $2000-$3FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_PL, "Wy≥±cz mapowanie RAM w $2000-$3FFF"},
	/* ru */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_RU, "Disable RAM mapping in $2000-$3FFF"},
	/* sv */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_SV, "Inaktivera RAM-mappning pÂ $2000-$3FFF"},
	/* tr */ {IDCLS_DISABLE_RAM_MAPPING_IN_2000_TR, "$2000-$3FFF aral˝˝nda RAM e˛le˛tirmeyi pasifle˛tir"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000,    N_("Enable RAM mapping in $4000-$5FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_DA, "AktivÈr RAM-mappning pÂ $4000-$5FFF"},
	/* de */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_DE, "RAM Zuordnung in $4000-$5FFF aktivieren"},
	/* es */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_ES, "Permitir mapeado RAM en $4000-$5FFF"},
	/* fr */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_FR, "Activer le mappage RAM dans $4000-$5FFF"},
	/* hu */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_HU, "$4000-$5FFF RAM lekÈpzÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_IT, "Attiva mappatura della RAM a $4000-$5FFF"},
	/* ko */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_NL, "Activeer RAM op adres $4000-$5FFF"},
	/* pl */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_PL, "W≥±cz mapowanie RAM w $4000-$5FFF"},
	/* ru */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_RU, "Enable RAM mapping in $4000-$5FFF"},
	/* sv */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_SV, "Aktivera RAM-mappning pÂ $4000-$5FFF"},
	/* tr */ {IDCLS_ENABLE_RAM_MAPPING_IN_4000_TR, "$4000-$5FFF aral˝˝nda RAM e˛le˛tirmeyi aktif et"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000,    N_("Disable RAM mapping in $4000-$5FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_DA, "DeaktivÈr RAM-mappning pÂ $4000-$5FFF"},
	/* de */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_DE, "RAM Zuordnung in $4000-$5FFF deaktivieren"},
	/* es */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_ES, "Deshabilitar mapeado RAM en $4000-$5FFF"},
	/* fr */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_FR, "DÈsactiver le mappage RAM dans $4000-$5FFF"},
	/* hu */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_HU, "$4000-$5FFF RAM lekÈpzÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_IT, "Disattiva mappatura della RAM a $4000-$5FFF"},
	/* ko */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_NL, "RAM op adres $4000-$5FFF uitchakelen"},
	/* pl */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_PL, "Wy≥±cz mapowanie RAM w $4000-$5FFF"},
	/* ru */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_RU, "Disable RAM mapping in $4000-$5FFF"},
	/* sv */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_SV, "Inaktivera RAM-mappning pÂ $4000-$5FFF"},
	/* tr */ {IDCLS_DISABLE_RAM_MAPPING_IN_4000_TR, "$4000-$5FFF aral˝˝nda RAM e˛le˛tirmeyi pasifle˛tir"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000,    N_("Enable RAM mapping in $6000-$7FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_DA, "AktivÈr RAM-mappning pÂ $6000-$7FFF"},
	/* de */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_DE, "RAM Zuordnung in $6000-$7FFF aktivieren"},
	/* es */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_ES, "Permitir mapeado RAM en $6000-$7FFF"},
	/* fr */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_FR, "Activer le mappage RAM dans $6000-$7FFF"},
	/* hu */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_HU, "$6000-$7FFF RAM lekÈpzÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_IT, "Attiva mappatura della RAM a $6000-$7FFF"},
	/* ko */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_NL, "Activeer RAM op adres $6000-$7FFF"},
	/* pl */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_PL, "W≥±cz mapowanie RAM w $6000-$7FFF"},
	/* ru */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_RU, "Enable RAM mapping in $6000-$7FFF"},
	/* sv */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_SV, "Aktivera RAM-mappning pÂ $6000-$7FFF"},
	/* tr */ {IDCLS_ENABLE_RAM_MAPPING_IN_6000_TR, "$6000-$7FFF aral˝˝nda RAM e˛le˛tirmeyi aktif et"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000,    N_("Disable RAM mapping in $6000-$7FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_DA, "DeaktivÈr RAM-mappning pÂ $6000-$7FFF"},
	/* de */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_DE, "RAM Zuordnung in $6000-$7FFF deaktivieren"},
	/* es */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_ES, "Deshabilitar mapeado RAM en $6000-$7FFF"},
	/* fr */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_FR, "DÈsactiver le mappage RAM dans $6000-$7FFF"},
	/* hu */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_HU, "$6000-$7FFF RAM lekÈpzÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_IT, "Disattiva mappatura della RAM a $6000-$7FFF"},
	/* ko */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_NL, "RAM op adres $6000-$7FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_PL, "Wy≥±cz mapowanie RAM w $6000-$7FFF"},
	/* ru */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_RU, "Disable RAM mapping in $6000-$7FFF"},
	/* sv */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_SV, "Inaktivera RAM-mappning pÂ $6000-$7FFF"},
	/* tr */ {IDCLS_DISABLE_RAM_MAPPING_IN_6000_TR, "$6000-$7FFF aral˝˝nda RAM e˛le˛tirmeyi pasifle˛tir"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000,    N_("Enable RAM mapping in $C000-$CFFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_DA, "AktivÈr RAM-mappning pÂ $C000-$CFFF"},
	/* de */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_DE, "RAM Zuordnung in $C000-$CFFF aktivieren"},
	/* es */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_ES, "Permitir mapeado RAM en $C000-$CFFF"},
	/* fr */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_FR, "Activer le mappage RAM dans $C000-$CFFF"},
	/* hu */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_HU, "$C000-$CFFF RAM lekÈpzÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_IT, "Attiva mappatura della RAM a $C000-$CFFF"},
	/* ko */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_NL, "Activeer RAM op adres $C000-$CFFF"},
	/* pl */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_PL, "W≥±cz mapowanie RAM w $C000-$CFFF"},
	/* ru */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_RU, "Enable RAM mapping in $C000-$CFFF"},
	/* sv */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_SV, "Aktivera RAM-mappning pÂ $C000-$CFFF"},
	/* tr */ {IDCLS_ENABLE_RAM_MAPPING_IN_C000_TR, "$C000-$CFFF aral˝˝nda RAM e˛le˛tirmeyi aktif et"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000,    N_("Disable RAM mapping in $C000-$CFFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_DA, "DeaktivÈr RAM-mappning pÂ $C000-$CFFF"},
	/* de */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_DE, "RAM Zuordnung in $C000-$CFFF deaktivieren"},
	/* es */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_ES, "Deshabilitar mapeado RAM en $C000-$CFFF"},
	/* fr */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_FR, "DÈsactiver le mappage RAM dans $C000-$CFFF"},
	/* hu */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_HU, "$C000-$CFFF RAM lekÈpzÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_IT, "Disattiva mappatura della RAM a $C000-$CFFF"},
	/* ko */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_NL, "RAM op adres $C000-$CFFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_PL, "Wy≥±cz mapowanie RAM w $C000-$CFFF"},
	/* ru */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_RU, "Disable RAM mapping in $C000-$CFFF"},
	/* sv */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_SV, "Inaktivera RAM-mappning pÂ $C000-$CFFF"},
	/* tr */ {IDCLS_DISABLE_RAM_MAPPING_IN_C000_TR, "$C000-$CFFF aral˝˝nda RAM e˛le˛tirmeyi pasifle˛tir"},
#endif
	
#ifdef COMMON_KBD
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_KEYMAP_INDEX,    N_("Specify index of keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_KEYMAP_INDEX_DA, "Angiv indeks for tastaturindstillingsfil"},
	/* de */ {IDCLS_SPECIFY_KEYMAP_INDEX_DE, "Index der Keymap Datei definieren"},
	/* es */ {IDCLS_SPECIFY_KEYMAP_INDEX_ES, "Especificar Ìndice fichero teclado"},
	/* fr */ {IDCLS_SPECIFY_KEYMAP_INDEX_FR, "SpÈcifier l'index du fichier de mappage clavier"},
	/* hu */ {IDCLS_SPECIFY_KEYMAP_INDEX_HU, "Adja meg a billenty˚zet lekÈpzÈs f·jl tÌpus·t"},
	/* it */ {IDCLS_SPECIFY_KEYMAP_INDEX_IT, "Specifica l'indice del file della mappa della tastiera"},
	/* ko */ {IDCLS_SPECIFY_KEYMAP_INDEX_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_KEYMAP_INDEX_NL, "Geef de index van het keymapbestand"},
	/* pl */ {IDCLS_SPECIFY_KEYMAP_INDEX_PL, "Okre∂l indeks pliku uk≥adu klawiatury"},
	/* ru */ {IDCLS_SPECIFY_KEYMAP_INDEX_RU, "Specify index of keymap file"},
	/* sv */ {IDCLS_SPECIFY_KEYMAP_INDEX_SV, "Ange index o tangentbordsfil"},
	/* tr */ {IDCLS_SPECIFY_KEYMAP_INDEX_TR, "Tu˛ haritas˝ dosyas˝n˝n indeksini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME,    N_("Specify name of graphics keyboard symbolic keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_DA, "Angiv fil for symbolsk tastaturemulering for \"graphics\"-tastatur"},
	/* de */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_DE, "Keymap Datei f¸r graphics keyboard symbolic definieren"},
	/* es */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_ES, "Especificar nombre fichero graficos teclado simbÛlico"},
	/* fr */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier symbolique"},
	/* hu */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_HU, "Adja meg a grafikus Ès szimbolikus billenty˚zet lekÈpzÈsi f·jl nevÈt."},
	/* it */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_IT, "Specifica il nome del file della mappa simbolica della tastiera grafica"},
	/* ko */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_NL, "Geef de naam van het symbolisch keymapbestand voor het grafische toetsenbord"},
	/* pl */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_PL, "Okre∂l nazwÍ pliku symbolicznego uk≥adu klawiatury graficznej"},
	/* ru */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_RU, "Specify name of graphics keyboard symbolic keymap file"},
	/* sv */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_SV, "Ange fil fˆr symbolisk tangentbordsemulering fˆr \"graphics\"-tangentbord"},
	/* tr */ {IDCLS_SPECIFY_GFX_SYM_KEYMAP_NAME_TR, "Grafik klavyesi sembolik tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME,    N_("Specify name of graphics keyboard positional keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_DA, "Angiv fil for positionsbestemt tastaturemulering for \"graphics\"-tastatur"},
	/* de */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_DE, "Keymap Datei f¸r graphics keyboard positional definieren"},
	/* es */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_ES, "Especificar nombre fichero graficos teclado posicional"},
	/* fr */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier positionnel"},
	/* hu */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_HU, "Adja meg a grafikus Ès pozÌciÛ szerinti billenty˚zet lekÈpzÈsi f·jl nevÈt."},
	/* it */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_IT, "Specifica il nome del file della mappa posizionale della tastiera grafica"},
	/* ko */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_NL, "Geef de naam van het positioneel keymapbestand voor het grafische toetsenbord"},
	/* pl */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_PL, "Okre∂l nazwÍ pliku pozycyjnego uk≥adu klawiatury graficznej"},
	/* ru */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_RU, "Specify name of graphics keyboard positional keymap file"},
	/* sv */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_SV, "Ange fil fˆr positionsriktig tangentbordsemulering fˆr \"graphics\"-tangentbord"},
	/* tr */ {IDCLS_SPECIFY_GFX_POS_KEYMAP_NAME_TR, "Grafik klavyesi konumsal tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME,    N_("Specify name of UK business keyboard symbolic keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_DA, "Angiv fil for symbolsk tastaturemulering for Britisk \"business\"-tastatur"},
	/* de */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_DE, "Keymap Datei f¸r UK business keyboard symbolic definieren"},
	/* es */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_ES, "Especificar nombre fichero teclado UK business simbÛlico"},
	/* fr */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier symbolique UK"},
	/* hu */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_HU, "Adja meg az angol, hivatalos, szimbolikus billenty˚zet lekÈpzÈsi f·jl nevÈt."},
	/* it */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_IT, "Specifica il nome del file della mappa simbolica della tastiera UK business"},
	/* ko */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_NL, "Geef de naam van het symbolisch keymapbestand voor het UK zakelijk toetsenbord"},
	/* pl */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_PL, "Okre∂l nazwÍ pliku symbolicznego uk≥adu angielskiej klawiatury biznesowej"},
	/* ru */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_RU, "Specify name of UK business keyboard symbolic keymap file"},
	/* sv */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_SV, "Ange fil fˆr symbolisk tangentbordsemulering fˆr brittiskt \"business\"-tangentbord"},
	/* tr */ {IDCLS_SPECIFY_BUK_SYM_KEYMAP_NAME_TR, "UK business klavyesi sembolik tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME,    N_("Specify name of UK business keyboard positional keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_DA, "Angiv fil for positionsbestemt tastaturemulering for Britisk \"business\"-tastatur"},
	/* de */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_DE, "Keymap Datei f¸r UK business keyboard positional definieren"},
	/* es */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_ES, "Especificar nombre fichero teclado UK business posicional"},
	/* fr */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier positionnel UK"},
	/* hu */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_HU, "Adja meg az angol, hivatalos, pozÌciÛ szerinti billenty˚zet lekÈpzÈsi f·jl nevÈt."},
	/* it */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_IT, "Specifica il nome del file della mappa posizionale della tastiera UK business"},
	/* ko */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_NL, "Geef de naam van het positioneel keymapbestand voor het UK zakelijk toetsenbord"},
	/* pl */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_PL, "Okre∂l nazwÍ pliku pozycyjnego uk≥adu angielskiej klawiatury biznesowej"},
	/* ru */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_RU, "Specify name of UK business keyboard positional keymap file"},
	/* sv */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_SV, "Ange fil fˆr positionsriktig tangentbordsemulering fˆr brittiskt \"business\"-tangentbord"},
	/* tr */ {IDCLS_SPECIFY_BUK_POS_KEYMAP_NAME_TR, "UK business klavyesi konumsal tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME,    N_("Specify name of German business keyboard symbolic keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_DA, "Angiv fil for symbolsk tastaturemulering for Tysk \"business\"-tastatur"},
	/* de */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_DE, "Keymap Datei f¸r German business keyboard symbolic definieren"},
	/* es */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_ES, "Especificar nombre fichero teclado Alem·n business simbÛlico"},
	/* fr */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier symbolique allemand"},
	/* hu */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_HU, "Adja meg a nÈmet, hivatalos, szimbolikus billenty˚zet lekÈpzÈsi f·jl nevÈt."},
	/* it */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_IT, "Specifica il nome del file della mappa simbolica della tastiera business tedesca"},
	/* ko */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_NL, "Geef de naam van het symbolisch keymapbestand voor het Duitse zakelijk toetsenbord"},
	/* pl */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_PL, "Okre∂l nazwÍ pliku symbolicznego uk≥adu niemieckiej klawiatury biznesowej"},
	/* ru */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_RU, "Specify name of German business keyboard symbolic keymap file"},
	/* sv */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_SV, "Ange fil fˆr symbolisk tangentbordsemulering fˆr tyskt \"business\"-tangentbord"},
	/* tr */ {IDCLS_SPECIFY_BDE_SYM_KEYMAP_NAME_TR, "Alman business klavyesi sembolik tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
	
	/* cbm2/cbm2-cmdline-options.c, pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME,    N_("Specify name of German business keyboard positional keymap file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_DA, "Angiv fil for positionsbestemt tastaturemulering for Tysk \"business\"-tastatur"},
	/* de */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_DE, "Keymap Datei f¸r German business keyboard positional definieren"},
	/* es */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_ES, "Especificar nombre fichero teclado Alem·n business posicional"},
	/* fr */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_FR, "SpÈcifier le nom du fichier de mappage clavier positionnel allemand"},
	/* hu */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_HU, "Adja meg a nÈmet, hivatalos, pozÌciÛ szerinti billenty˚zet lekÈpzÈsi f·jl nevÈt."},
	/* it */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_IT, "Specifica il nome del file della mappa posizionale della tastiera business tedesca"},
	/* ko */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_NL, "Geef de naam van het positioneel keymapbestand voor het Duitse zakelijk toetsenbord"},
	/* pl */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_PL, "Okre∂l nazwÍ pliku pozycyjnego uk≥adu niemieckiej klawiatury biznesowej"},
	/* ru */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_RU, "Specify name of German business keyboard positional keymap file"},
	/* sv */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_SV, "Ange fil fˆr positionsriktig tangentbordsemulering fˆr tyskt \"business\"-tangentbord"},
	/* tr */ {IDCLS_SPECIFY_BDE_POS_KEYMAP_NAME_TR, "Alman business klavyesi konumsal tu˛ haritas˝ dosyas˝n˝n ismini belirt"},
#endif
#endif
	
	/* drive/drive-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_TRUE_DRIVE,    N_("Enable hardware-level emulation of disk drives")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_TRUE_DRIVE_DA, "AktivÈr emulering af diskettedrev pÂ hardware-niveau"},
	/* de */ {IDCLS_ENABLE_TRUE_DRIVE_DE, "Hardware Emulation f¸r Disklaufwerke aktivieren"},
	/* es */ {IDCLS_ENABLE_TRUE_DRIVE_ES, "Permitir emulacion a nivel hardware unidades de disco"},
	/* fr */ {IDCLS_ENABLE_TRUE_DRIVE_FR, "Activer l'Èmulation de disques au niveau physique"},
	/* hu */ {IDCLS_ENABLE_TRUE_DRIVE_HU, "LemezegysÈgek hardver szint˚ emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_TRUE_DRIVE_IT, "Attiva emulazione hardware dei disk drive"},
	/* ko */ {IDCLS_ENABLE_TRUE_DRIVE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_TRUE_DRIVE_NL, "Activeer hardwarematige emulatie van diskdrives"},
	/* pl */ {IDCLS_ENABLE_TRUE_DRIVE_PL, "W≥±cz sprzÍtow± emulacjÍ stacji dyskÛw"},
	/* ru */ {IDCLS_ENABLE_TRUE_DRIVE_RU, "Enable hardware-level emulation of disk drives"},
	/* sv */ {IDCLS_ENABLE_TRUE_DRIVE_SV, "Aktivera emulering av diskettstationer pÂ maskinvarunivÂ"},
	/* tr */ {IDCLS_ENABLE_TRUE_DRIVE_TR, "Disk s¸r¸c¸lerinin donan˝m seviyesinde em¸lasyonunu aktif et"},
#endif
	
	/* drive/drive-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_TRUE_DRIVE,    N_("Disable hardware-level emulation of disk drives")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_TRUE_DRIVE_DA, "DeaktivÈr emulering af diskettedrev pÂ hardware-niveau"},
	/* de */ {IDCLS_DISABLE_TRUE_DRIVE_DE, "Hardware Emulation f¸r Disklaufwerke deaktivieren"},
	/* es */ {IDCLS_DISABLE_TRUE_DRIVE_ES, "No permitir emulacion a nivel hardware unidades de disco"},
	/* fr */ {IDCLS_DISABLE_TRUE_DRIVE_FR, "DÈsactiver l'Èmulation de disques au niveau physique"},
	/* hu */ {IDCLS_DISABLE_TRUE_DRIVE_HU, "LemezegysÈgek hardver szint˚ emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_TRUE_DRIVE_IT, "Disattiva emulazione hardware dei disk drive"},
	/* ko */ {IDCLS_DISABLE_TRUE_DRIVE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_TRUE_DRIVE_NL, "Hardwarematige emulatie van diskdrives uitschakelen"},
	/* pl */ {IDCLS_DISABLE_TRUE_DRIVE_PL, "Wy≥±cz sprzÍtow± emulacjÍ stacji dyskÛw"},
	/* ru */ {IDCLS_DISABLE_TRUE_DRIVE_RU, "Disable hardware-level emulation of disk drives"},
	/* sv */ {IDCLS_DISABLE_TRUE_DRIVE_SV, "Inaktivera emulering av diskettstationer pÂ maskinvarunivÂ"},
	/* tr */ {IDCLS_DISABLE_TRUE_DRIVE_TR, "Disk s¸r¸c¸lerinin donan˝m seviyesinde em¸lasyonunu pasifle˛tir"},
#endif
	
	/* drive/drive-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DRIVE_SOUND,    N_("Enable sound emulation of disk drives")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DRIVE_SOUND_DA, "AktivÈr emulering af lyd for diskettedrev"},
	/* de */ {IDCLS_ENABLE_DRIVE_SOUND_DE, "Sound Emulation f¸r Disklaufwerke aktivieren"},
	/* es */ {IDCLS_ENABLE_DRIVE_SOUND_ES, "Permitir emulaciÛn de sonido en unidad de discos"},
	/* fr */ {IDCLS_ENABLE_DRIVE_SOUND_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DRIVE_SOUND_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_DRIVE_SOUND_IT, "Attiva emulazione audio dei disk drive"},
	/* ko */ {IDCLS_ENABLE_DRIVE_SOUND_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DRIVE_SOUND_NL, "Activeer geluidsemulatie van diskdrives"},
	/* pl */ {IDCLS_ENABLE_DRIVE_SOUND_PL, "W≥±cz emulacjÍ odg≥osÛw stacji dyskÛw"},
	/* ru */ {IDCLS_ENABLE_DRIVE_SOUND_RU, "Enable sound emulation of disk drives"},
	/* sv */ {IDCLS_ENABLE_DRIVE_SOUND_SV, "Aktivera ljudemulering fˆr diskettstationer"},
	/* tr */ {IDCLS_ENABLE_DRIVE_SOUND_TR, "Disk s¸r¸c¸lerinin ses em¸lasyonunu aktif et"},
#endif
	
	/* drive/drive-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DRIVE_SOUND,    N_("Disable sound emulation of disk drives")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DRIVE_SOUND_DA, "DeaktivÈr emulering af lyd for diskettedrev"},
	/* de */ {IDCLS_DISABLE_DRIVE_SOUND_DE, "Sound Emulation f¸r Disklaufwerke deaktivieren"},
	/* es */ {IDCLS_DISABLE_DRIVE_SOUND_ES, "Inhabilitar emulaciÛn de sonido wn unidad de discos"},
	/* fr */ {IDCLS_DISABLE_DRIVE_SOUND_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DRIVE_SOUND_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_DRIVE_SOUND_IT, "Disattiva emulazione audio dei disk drive"},
	/* ko */ {IDCLS_DISABLE_DRIVE_SOUND_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DRIVE_SOUND_NL, "Geluidsemulatie van diskdrives uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DRIVE_SOUND_PL, "Wy≥±cz emulacjÍ odg≥osÛw stacji dyskÛw"},
	/* ru */ {IDCLS_DISABLE_DRIVE_SOUND_RU, "Disable sound emulation of disk drives"},
	/* sv */ {IDCLS_DISABLE_DRIVE_SOUND_SV, "Inaktivera ljudemulering fˆr diskettstationer"},
	/* tr */ {IDCLS_DISABLE_DRIVE_SOUND_TR, "Disk s¸r¸c¸lerinin ses em¸lasyonunu pasifle˛tir"},
#endif
	
	/* drive/drive-cmdline-options.c, printerdrv/interface-serial.c,
	 attach.c, drive/iec/iec-cmdline-options.c, c64/c64gluelogic.c */
	/* en */ {IDCLS_P_TYPE,    N_("<Type>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_TYPE_DA, "<Type>"},
	/* de */ {IDCLS_P_TYPE_DE, "<Typ>"},
	/* es */ {IDCLS_P_TYPE_ES, "<Tipo>"},
	/* fr */ {IDCLS_P_TYPE_FR, "<type>"},
	/* hu */ {IDCLS_P_TYPE_HU, "<TÌpus>"},
	/* it */ {IDCLS_P_TYPE_IT, "<Tipo>"},
	/* ko */ {IDCLS_P_TYPE_KO, "<¡æ∑˘>"},
	/* nl */ {IDCLS_P_TYPE_NL, "<Soort>"},
	/* pl */ {IDCLS_P_TYPE_PL, "<Typ>"},
	/* ru */ {IDCLS_P_TYPE_RU, "<Type>"},
	/* sv */ {IDCLS_P_TYPE_SV, "<Typ>"},
	/* tr */ {IDCLS_P_TYPE_TR, "<Tip>"},
#endif
	
	/* drive/drive-cmdline-options.c */
	/* en */ {IDCLS_SET_DRIVE_TYPE,    N_("Set drive type (0: no drive)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DRIVE_TYPE_DA, "Angiv enhedstype (0: ingen enhed)"},
	/* de */ {IDCLS_SET_DRIVE_TYPE_DE, "Setze Laufwerkstyp (0: kein Laufwerk)"},
	/* es */ {IDCLS_SET_DRIVE_TYPE_ES, "Seleccionar tipo unidad disco (0: sin unidad disco)"},
	/* fr */ {IDCLS_SET_DRIVE_TYPE_FR, "SpÈcifier le type de lecteur de disque (0: pas de lecteur)"},
	/* hu */ {IDCLS_SET_DRIVE_TYPE_HU, "Adja meg a lemezegysÈg tÌpus·t (0: nincs)"},
	/* it */ {IDCLS_SET_DRIVE_TYPE_IT, "Imposta tipo drive (0: nessun drive)"},
	/* ko */ {IDCLS_SET_DRIVE_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DRIVE_TYPE_NL, "Zet drive soort (0: geen drive)"},
	/* pl */ {IDCLS_SET_DRIVE_TYPE_PL, "Ustaw typ stacji (0: brak stacji)"},
	/* ru */ {IDCLS_SET_DRIVE_TYPE_RU, "Set drive type (0: no drive)"},
	/* sv */ {IDCLS_SET_DRIVE_TYPE_SV, "Ange enhetstyp (0: ingen enhet)"},
	/* tr */ {IDCLS_SET_DRIVE_TYPE_TR, "S¸r¸c¸ tipini ayarlay˝n (0: s¸r¸c¸ yok)"},
#endif
	
	/* drive/drive-cmdline-options.c,
	 drive/iec/iec-cmdline-options.c,
	 gfxoutputdrv/doodledrv.c */
	/* en */ {IDCLS_P_METHOD,    N_("<method>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_METHOD_DA, "<metode>"},
	/* de */ {IDCLS_P_METHOD_DE, "<Methode>"},
	/* es */ {IDCLS_P_METHOD_ES, "<mÈtodo>"},
	/* fr */ {IDCLS_P_METHOD_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_METHOD_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_METHOD_IT, "<metodo>"},
	/* ko */ {IDCLS_P_METHOD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_METHOD_NL, "<methode>"},
	/* pl */ {IDCLS_P_METHOD_PL, "<metoda>"},
	/* ru */ {IDCLS_P_METHOD_RU, "<method>"},
	/* sv */ {IDCLS_P_METHOD_SV, "<metod>"},
	/* tr */ {IDCLS_P_METHOD_TR, "<metod>"},
#endif
	
	/* gfxoutputdrv/doodledrv.c */
	/* en */ {IDCLS_P_COLOR,    N_("<color>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_COLOR_DA, "<farve>"},
	/* de */ {IDCLS_P_COLOR_DE, "<Farbe>"},
	/* es */ {IDCLS_P_COLOR_ES, "<color>"},
	/* fr */ {IDCLS_P_COLOR_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_COLOR_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_COLOR_IT, "<colore>"},
	/* ko */ {IDCLS_P_COLOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_COLOR_NL, "<kleur>"},
	/* pl */ {IDCLS_P_COLOR_PL, "<kolor>"},
	/* ru */ {IDCLS_P_COLOR_RU, "<Ê“’‚>"},
	/* sv */ {IDCLS_P_COLOR_SV, "<f‰rg>"},
	/* tr */ {IDCLS_P_COLOR_TR, "<renk>"},
#endif
	
	/* gfxoutputdrv/doodledrv.c */
	/* en */ {IDCLS_OVERSIZED_HANDLING,    N_("Select the way the oversized input should be handled, (0: scale down, 1: crop left top, 2: crop center top,  3: crop right top, 4: crop left center, 5: crop center, 6: crop right center, 7: crop left bottom, 8: crop center bottom, 9:  crop right bottom)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_OVERSIZED_HANDLING_DA, "Angiv hÂndtering af for stort input (0: skalÈr ned, 1: klip venstre top, 2: klip midt top,  3: klip h¯jre top, 4: klip venstre midt, 5: klip centreret, 6: klip h¯jre midt, 7: klip venstre bund, 8: klip midt bund, 9: klip h¯jre bund)"},
	/* de */ {IDCLS_OVERSIZED_HANDLING_DE, "W‰hle, wie ¸bergroﬂer Input behandelt werden soll, (0: skaliere, 1: schneide links oben, 2: schneide mitte oben,  3: schneide rechts oben, 4: schneide links mitte, 5: schneide mitte, 6: schneide rechts mitte, 7: schneide links unten, 8: schneide mitte unten, 9:  schneide rechts unten)"},
	/* es */ {IDCLS_OVERSIZED_HANDLING_ES, "Seleccionar cÛmo se manejar·n las entradas sobredimensionadas, (0: escalar, 1:recorte sup izq, 2:recorte sup centro, 3:recorte sup dcha, 4:recorte centro izq, 5:recorte centro, 6:recorte centro dcha, 7:recorte abajo izq, 8:recorte centro abajo, 9:recorte abajo dcha)"},
	/* fr */ {IDCLS_OVERSIZED_HANDLING_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_OVERSIZED_HANDLING_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_OVERSIZED_HANDLING_IT, "Seleziona come gestire il sovradimensionamento dell'input, (0: scale down, 1: ritaglia sinistra alto, 2: ritaglia centro alto,  3: ritaglia destra alto, 4: ritaglia sinistra centro, 5: ritaglia centro, 6: ritaglia destra centro, 7: ritaglia sinistra basso, 8: ritaglia centro basso, 9:  ritaglia destra basso)"},
	/* ko */ {IDCLS_OVERSIZED_HANDLING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_OVERSIZED_HANDLING_NL, "Selecteer de manier waarop de te grootte invoer moet worden afgehandeld, (0: maak kleiner, 1: crop linker bovenkant, 2: crop midden bovenkant, 3: crop rechter bovenkant, 4: crop linker midden, 5: crop midden, 6: crop rechter midden, 7: crop linker onderkant, 8: crop midden onderkant, 9: crop rechter onderkant)"},
	/* pl */ {IDCLS_OVERSIZED_HANDLING_PL, "Wybierz sposÛb, w jaki ma byÊ obs≥ugiwany za duøy obraz, (0: zmniejszenie, 1: ∂ciÍcie z gÛry z lewej, 2: ∂ciÍcie z gÛry, 3: ∂ciÍcie z prawej z gÛry, 4: ∂ciÍcie z lewej, 5: ∂ciÍcie od ∂rodka, 6: ∂ciÍcie z prawej, 7: ∂ciÍcie z lewej z do≥u, 8: ∂ciÍcie z do≥u, 9: ∂ciÍcie z prawej z do≥u)"},
	/* ru */ {IDCLS_OVERSIZED_HANDLING_RU, "Select the way the oversized input should be handled, (0: scale down, 1: crop left top, 2: crop center top,  3: crop right top, 4: crop left center, 5: crop center, 6: crop right center, 7: crop left bottom, 8: crop center bottom, 9:  crop right bottom)"},
	/* sv */ {IDCLS_OVERSIZED_HANDLING_SV, "V‰lj hur fˆr stor indata skall hanteras, (0: skala ned, 1: visa ˆvre v‰nstra, 2: visa ˆvre mitten, 3: visa ˆvre hˆgra, 4: visa v‰nstra mitten, 5: visa mitten, 6: visa hˆgra mitten, 7: visa nedre v‰nstra, 8: visa nedre mitten, 9: visa nedre hˆgre)"},
	/* tr */ {IDCLS_OVERSIZED_HANDLING_TR, "B¸y¸k girdilerin ele al˝nma yˆntemini seÁin, (0: k¸Á¸lt, 1: sol ¸stten k˝rp, 2: ortal˝ ¸stten k˝rp,  3: sa ¸stten k˝rp, 4: soldan ortal˝ k˝rp, 5: ortadan k˝rp, 6: sadan ortal˝ k˝rp, 7: sol alttan k˝rp, 8: ortal˝ alttan k˝rp, 9:  sa alttan k˝rp)"},
#endif
	
	/* gfxoutputdrv/doodledrv.c */
	/* en */ {IDCLS_MULTICOLOR_HANDLING,    N_("Select the way the multicolor to hires should be handled, (0: b&w, 1: 2 colors, 2: 4 colors, 3: gray scale,  4: best cell colors)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_MULTICOLOR_HANDLING_DA, "Angiv mÂden multicolor til h¯jopl¯sning skal hÂndteres pÂ, (0: sort/hvid, 1: 2 farver, 2: 4 farver, 3: grÂtoner,  4: bedste cellefarver)"},
	/* de */ {IDCLS_MULTICOLOR_HANDLING_DE, "W‰hle, wie Mulitcolore zu Hochauflˆsung behandelte werden soll, (0: S&W, 1: 2 Farben, 2: 4 Farben, 4 Graustufen, 4: Beste Zellenfarben)"},
	/* es */ {IDCLS_MULTICOLOR_HANDLING_ES, "Seleccionar cÛmo se manejar·n el cambio multicolor-alta resoluciÛn (0:ByN, 1:2 colores, 2:4 colores, 3:escala grises, 4:mejores colores)"},
	/* fr */ {IDCLS_MULTICOLOR_HANDLING_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_MULTICOLOR_HANDLING_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_MULTICOLOR_HANDLING_IT, "Seleziona come gestire il multicolor in hires, (0: b&w, 1: 2 colori, 2: 4 colori, 3: scala di grigi,  4: migliori colori cella)"},
	/* ko */ {IDCLS_MULTICOLOR_HANDLING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_MULTICOLOR_HANDLING_NL, "Selecteer de manier waarop 'multicolor' naar 'hires' conversie moet worden afgehandeld, (0: zwart/wit, 1: 2 kleuren, 2: 4 kleuren, 3: grijs, 4: best mogelijke kleuren in de cel)"},
	/* pl */ {IDCLS_MULTICOLOR_HANDLING_PL, "Wybiera sposÛb obs≥ugi wielu kolorÛw w wysokiej rozdzielczo∂ci (0: czarno-bia≥y, 1: 2 kolory, 2: 4 kolory, 3: skala szaro∂ci, 4: najlepsze kolory komÛrek)"},
	/* ru */ {IDCLS_MULTICOLOR_HANDLING_RU, "Select the way the multicolor to hires should be handled, (0: b&w, 1: 2 colors, 2: 4 colors, 3: gray scale,  4: best cell colors)"},
	/* sv */ {IDCLS_MULTICOLOR_HANDLING_SV, "V‰lj hur flerf‰rgs-till-hˆgupplˆst skall hanteras, (0: svartvit, 1: 2 f‰rger, 2: fyra f‰rger, 3: grÂskala, 4: b‰sta cellf‰rger)"},
	/* tr */ {IDCLS_MULTICOLOR_HANDLING_TR, "«ok renkliden y¸ksek Áˆz¸n¸rl¸e geÁi˛in ele al˝nma yˆntemini seÁin, (0: siyah&beyaz, 1: 2 renk, 2: 4 renk, 3: gri tonlu,  4: en iyi h¸cre renkleri)"},
#endif
	
	/* gfxoutputdrv/doodledrv.c */
	/* en */ {IDCLS_TED_LUM_HANDLING,    N_("Select the way the TED luminosity should be handled, (0: ignore, 1: dither)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TED_LUM_HANDLING_DA, "Angiv mÂden TED-lysstyrker skal hÂndteres pÂ (0: ignorÈr, 1: blanding)"},
	/* de */ {IDCLS_TED_LUM_HANDLING_DE, "W‰hle, wie TED Leuchtst‰rke behandelt werden soll, (0: ignorieren, 1: dither)"},
	/* es */ {IDCLS_TED_LUM_HANDLING_ES, "Seleccionar cÛmo se manejar·n la luminosidad TED (0:ignorar, 1:dither)"},
	/* fr */ {IDCLS_TED_LUM_HANDLING_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_TED_LUM_HANDLING_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_TED_LUM_HANDLING_IT, "Seleziona come gestire la luminosit‡ TED, (0: ignora, 1: dither)"},
	/* ko */ {IDCLS_TED_LUM_HANDLING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TED_LUM_HANDLING_NL, "Selecteer de manier waarop de TED kleuren moeten worden afgehandeld, (0: negeren, 1: dither)"},
	/* pl */ {IDCLS_TED_LUM_HANDLING_PL, "WybÛr sposobu obs≥ugi jaskrawo∂ci TED (0: ignoruj, 1: ditheruj)"},
	/* ru */ {IDCLS_TED_LUM_HANDLING_RU, "Select the way the TED luminosity should be handled, (0: ignore, 1: dither)"},
	/* sv */ {IDCLS_TED_LUM_HANDLING_SV, "V‰lj hur TED-luminositet skall hanteras, (0: ignorera, 1: f‰rgutj‰mna)"},
	/* tr */ {IDCLS_TED_LUM_HANDLING_TR, "TED l¸minozitesinin ele al˝nma yˆntemini seÁin, (0: yok say, 1: dither)"},
#endif
	
	/* gfxoutputdrv/doodledrv.c */
	/* en */ {IDCLS_CRTC_TEXT_COLOR,    N_("Select the CRTC text color (0: white, 1: amber, 2: green)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_CRTC_TEXT_COLOR_DA, "VÊlg CRTC tekstfarve (0: hvid, 1: ravgul, 2: gr¯n)"},
	/* de */ {IDCLS_CRTC_TEXT_COLOR_DE, "W‰hle CRTC Textfarbe (0: weiﬂ, 1: Amberbraun, 2: Gr¸n)"},
	/* es */ {IDCLS_CRTC_TEXT_COLOR_ES, "Seleccionar color texto CRTC (0:blanco, 1:·mbar, 2:verde)"},
	/* fr */ {IDCLS_CRTC_TEXT_COLOR_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_CRTC_TEXT_COLOR_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_CRTC_TEXT_COLOR_IT, "Seleziona il colore del testo CRTC (0: bianco, 1: ambra, 2: verde)"},
	/* ko */ {IDCLS_CRTC_TEXT_COLOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_CRTC_TEXT_COLOR_NL, "Selecteer de CRTC tekst kleur (0: wit, 1: amber, 2: groen)"},
	/* pl */ {IDCLS_CRTC_TEXT_COLOR_PL, "Wybierz kolor tekstu CRTC (0: bia≥y, 1: bursztynowy, 2: zielony)"},
	/* ru */ {IDCLS_CRTC_TEXT_COLOR_RU, "Select the CRTC text color (0: white, 1: amber, 2: green)"},
	/* sv */ {IDCLS_CRTC_TEXT_COLOR_SV, "V‰lj CRTC-textf‰rg (0: vit, 1: gul, 2: grˆn)"},
	/* tr */ {IDCLS_CRTC_TEXT_COLOR_TR, "CRTC yaz˝ rengini seÁin (0: beyaz, 1: kehribar, 2: ye˛il)"},
#endif
	
	/* drive/drive-cmdline-options.c */
	/* en */ {IDCLS_SET_DRIVE_EXTENSION_POLICY,    N_("Set drive 40 track extension policy (0: never, 1: ask, 2: on access)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_DA, "Angiv drevets regel for 40-spors udviddelse (0: aldrig, 1: sp¯rg, 2: ved tilgang)"},
	/* de */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_DE, "40 Spur Erweiterungsmethode (0: nie, 1: R¸ckfrage, 2: bei Bedarf)"},
	/* es */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_ES, "Seleccionar polÌtica unidad disco extensiÛn 40 pistas (0:nunca, 1:preguntar, 2:al acceder)"},
	/* fr */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_FR, "SpÈcifier la rËgle d'extention 40 pistes (0: jamais, 1: demander, 2: ‡ l'accËs)"},
	/* hu */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_HU, "Adja meg a 40 s·vra kiterjesztÈs terjesztÈs mÛdj·t (0: soha, 1: kÈrdÈs, 2: hozz·fÈrÈskor)"},
	/* it */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_IT, "Imposta la politica di estensione a 40 tracce del drive (0: mai, 1: a richiesta, 2: all'accesso)"},
	/* ko */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_NL, "Stel beleid voor 40-sporenuitbreiding drive in (0: nooit, 1: vraag, 2: bij toegang)"},
	/* pl */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_PL, "Okre∂l zasadÍ rozszerzania do 40 ∂cieøek (0: nigdy, 1: pytaj, 2: przy dostÍpie)"},
	/* ru */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_RU, "Set drive 40 track extension policy (0: never, 1: ask, 2: on access)"},
	/* sv */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_SV, "Ange regel fˆr 40-spÂrsutˆkning (0: aldrig, 1: frÂga, 2: vid Âtkomst)"},
	/* tr */ {IDCLS_SET_DRIVE_EXTENSION_POLICY_TR, "S¸r¸c¸ 40 track b¸y¸me kural˝n˝ ayarla (0: asla, 1: sor, 2: eri˛ildiinde)"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME,    N_("Specify name of 1541 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_DA, "Angiv navn pÂ 1541-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_DE, "Name der 1541 DOS ROM Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_ES, "Especificar nombre imagen ROM de 1541 DOS "},
	/* fr */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1541 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_HU, "Adja meg az 1541 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1541"},
	/* ko */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_NL, "Geef de naam van het 1541 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1541"},
	/* ru */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_RU, "Specify name of 1541 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_SV, "Ange namn pÂ 1541-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1541_DOS_ROM_NAME_TR, "1541 DOS ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME,    N_("Specify name of 1541-II DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_DA, "Angivn navn pÂ 1541-II-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_DE, "Name der 1541-II DOS ROM Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_ES, "Especificar nombre imagen ROM de 1541-II DOS"},
	/* fr */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1541-II DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_HU, "Adja meg az 1541-II DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1541-II"},
	/* ko */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_NL, "Geef de naam van het 1541-II DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1541-II"},
	/* ru */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_RU, "Specify name of 1541-II DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_SV, "Ange namn pÂ 1541-II-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1541_II_DOS_ROM_NAME_TR, "1541-II DOS ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME,    N_("Specify name of 1570 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_DA, "Angivn navn pÂ 1570-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_DE, "Name der 1570 DOS ROM Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_ES, "Especificar nombre imagen ROM de 1570 DOS"},
	/* fr */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1570 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_HU, "Adja meg az 1570 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1570"},
	/* ko */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_NL, "Geef de naam van het 1570 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1570"},
	/* ru */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_RU, "Specify name of 1570 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_SV, "Ange namn pÂ 1570-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1570_DOS_ROM_NAME_TR, "1570 DOS ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME,    N_("Specify name of 1571 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_DA, "Angivn navn pÂ 1571-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_DE, "Name der 1571 DOS ROM Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_ES, "Especificar nombre imagen ROM de 1571 DOS "},
	/* fr */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1571 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_HU, "Adja meg az 1571 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1571"},
	/* ko */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_NL, "Geef de naam van het 1571 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1571"},
	/* ru */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_RU, "Specify name of 1571 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_SV, "Ange namn pÂ 1571-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1571_DOS_ROM_NAME_TR, "1571 DOS ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME,    N_("Specify name of 1581 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_DA, "Angivn navn pÂ 1581-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_DE, "Name der 1581 DOS ROM Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_ES, "Especificar nombre imagen ROM de 1581 DOS "},
	/* fr */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1581 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_HU, "Adja meg az 1581 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1581"},
	/* ko */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_NL, "Geef de naam van het 1581 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1581"},
	/* ru */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_RU, "Specify name of 1581 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_SV, "Ange namn pÂ 1581-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1581_DOS_ROM_NAME_TR, "1581 DOS ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME,    N_("Specify name of 2000 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_DA, "Angiv navn pÂ 2000-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_DE, "Name der 2000 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_ES, "Especificar nombre imagen 2000 DOS ROM"},
	/* fr */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del 2000 DOS"},
	/* ko */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_NL, "Geef de naam van het 2000 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 2000"},
	/* ru */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_RU, "Specify name of 2000 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_SV, "Ange namn pÂ 2000-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_2000_DOS_ROM_NAME_TR, "2000 DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME,    N_("Specify name of 4000 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_DA, "Angiv navn pÂ 4000-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_DE, "Name der 4000 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_ES, "Especificar nombre imagen 4000 DOS ROM"},
	/* fr */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del 4000 DOS"},
	/* ko */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_NL, "Geef de naam van het 4000 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 4000"},
	/* ru */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_RU, "Specify name of 4000 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_SV, "Ange namn pÂ 4000-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_4000_DOS_ROM_NAME_TR, "4000 DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_SET_IDLE_METHOD,    N_("Set drive idling method (0: no traps, 1: skip cycles, 2: trap idle)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_IDLE_METHOD_DA, "VÊlg tomgangsmetode for diskettedrev (0: ingen traps, 1: spring over cykler, 2: trap ledig)"},
	/* de */ {IDCLS_SET_IDLE_METHOD_DE, "Laufwerks idling Methode (0: kein Traps, 1: Zyklen verwerfen, 2: trap idle)"},
	/* es */ {IDCLS_SET_IDLE_METHOD_ES, "Seleccionar metodo tiempo inactico (0: sin intercepciÛn, 1:saltar ciclos, 2:interceptar tiempos inactivos)"},
	/* fr */ {IDCLS_SET_IDLE_METHOD_FR, "SpÈcifier la mÈthode d'idle (0: pas de traps, 1: sauter des cycles, 2: trap idle)"},
	/* hu */ {IDCLS_SET_IDLE_METHOD_HU, "LemezegysÈg ¸resj·r·si mÛdja (0: folytonos emul·ciÛ, 1: ciklusok kihagy·sa, 2: ¸res DOS ciklusok kihagy·sa)"},
	/* it */ {IDCLS_SET_IDLE_METHOD_IT, "Imposta il metodo per rilevare l'inattivit‡ del drive (0: non rilevare, 1: salta cicli, 2: rileva inattivit‡)"},
	/* ko */ {IDCLS_SET_IDLE_METHOD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_IDLE_METHOD_NL, "Stel de drive idlemethode in (0: geen traps, 1: sla cycli over, 2: trap idle)"},
	/* pl */ {IDCLS_SET_IDLE_METHOD_PL, "Okre∂l metodÍ bezczynno∂ci napÍdu (0: no traps, 1: opuszczaj cykle, 2: trap idle)"},
	/* ru */ {IDCLS_SET_IDLE_METHOD_RU, "Set drive idling method (0: no traps, 1: skip cycles, 2: trap idle)"},
	/* sv */ {IDCLS_SET_IDLE_METHOD_SV, "St‰ll in v‰ntemetod fˆr diskettstation (0: fÂnta inge, 1: hoppa cykler, 2: fÂnga v‰ntan)"},
	/* tr */ {IDCLS_SET_IDLE_METHOD_TR, "S¸r¸c¸ bo˛a vakit geÁirme metodunu ayarlay˝n (0: trap yok, 1: cyclelar˝ atla, 2: trap bo˛a vakit geÁirme)"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DRIVE_RAM_2000,    N_("Enable 8KB RAM expansion at $2000-$3FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DRIVE_RAM_2000_DA, "AktivÈr 8kB RAM-udviddelse pÂ $2000-$3FFF"},
	/* de */ {IDCLS_ENABLE_DRIVE_RAM_2000_DE, "8KB RAM Erweiterung bei $2000-3fff aktivieren"},
	/* es */ {IDCLS_ENABLE_DRIVE_RAM_2000_ES, "Permitir expansiÛn RAM de 8KB en $2000-$3FFF"},
	/* fr */ {IDCLS_ENABLE_DRIVE_RAM_2000_FR, "Activer l'exansion de 8KB RAM ‡ $2000-$3FFF"},
	/* hu */ {IDCLS_ENABLE_DRIVE_RAM_2000_HU, "8KB RAM kiterjeszÈs engedÈlyezÈse a $2000-$3FFF cÌmen"},
	/* it */ {IDCLS_ENABLE_DRIVE_RAM_2000_IT, "Attiva l'espansione di RAM di 8KB a $2000-$3FFF"},
	/* ko */ {IDCLS_ENABLE_DRIVE_RAM_2000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DRIVE_RAM_2000_NL, "Activeer 8KB RAM uitbreiding op adres $2000-$3FFF"},
	/* pl */ {IDCLS_ENABLE_DRIVE_RAM_2000_PL, "W≥±cz rozszerzenie 8KB RAM w $2000-$3FFF"},
	/* ru */ {IDCLS_ENABLE_DRIVE_RAM_2000_RU, "Enable 8KB RAM expansion at $2000-$3FFF"},
	/* sv */ {IDCLS_ENABLE_DRIVE_RAM_2000_SV, "Aktivera 8KB RAM-expansion pÂ $2000-$3FFF"},
	/* tr */ {IDCLS_ENABLE_DRIVE_RAM_2000_TR, "$2000-$3FFF aras˝nda 8KB RAM geni˛letmeyi aktif et"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DRIVE_RAM_2000,    N_("Disable 8KB RAM expansion at $2000-$3FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DRIVE_RAM_2000_DA, "DeaktivÈr 8kB RAM-udviddelse pÂ $2000-$3FFF"},
	/* de */ {IDCLS_DISABLE_DRIVE_RAM_2000_DE, "8KB RAM Erweiterung bei $2000-3fff deaktivieren"},
	/* es */ {IDCLS_DISABLE_DRIVE_RAM_2000_ES, "Deshabilitar expansiÛn RAM de 8KB en $2000-$3FFF"},
	/* fr */ {IDCLS_DISABLE_DRIVE_RAM_2000_FR, "DÈsactiver l'exansion de 8KB RAM ‡ $2000-$3FFF"},
	/* hu */ {IDCLS_DISABLE_DRIVE_RAM_2000_HU, "8KB RAM kiterjeszÈs tilt·sa a $2000-$3FFF cÌmen"},
	/* it */ {IDCLS_DISABLE_DRIVE_RAM_2000_IT, "Disattiva l'espansione di RAM di 8KB a $2000-$3FFF"},
	/* ko */ {IDCLS_DISABLE_DRIVE_RAM_2000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DRIVE_RAM_2000_NL, "8KB RAM uitbreiding op adres $2000-$3FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DRIVE_RAM_2000_PL, "Wy≥±cz rozszerzenie 8KB RAM w $2000-$3FFF"},
	/* ru */ {IDCLS_DISABLE_DRIVE_RAM_2000_RU, "Disable 8KB RAM expansion at $2000-$3FFF"},
	/* sv */ {IDCLS_DISABLE_DRIVE_RAM_2000_SV, "Inaktivera 8KB RAM-expansion pÂ $2000-$3FFF"},
	/* tr */ {IDCLS_DISABLE_DRIVE_RAM_2000_TR, "$2000-$3FFF aras˝nda 8KB RAM geni˛letmeyi pasifle˛tir"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DRIVE_RAM_4000,    N_("Enable 8KB RAM expansion at $4000-$5FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DRIVE_RAM_4000_DA, "AktivÈr 8kB RAM-udviddelse pÂ $4000-$5FFF"},
	/* de */ {IDCLS_ENABLE_DRIVE_RAM_4000_DE, "8KB RAM Erweiterung bei $4000-5fff aktivieren"},
	/* es */ {IDCLS_ENABLE_DRIVE_RAM_4000_ES, "Permitir expansiÛn RAM de 8KB en $4000-$5FFF"},
	/* fr */ {IDCLS_ENABLE_DRIVE_RAM_4000_FR, "Activer l'exansion de 8KB RAM ‡ $4000-$5FFF"},
	/* hu */ {IDCLS_ENABLE_DRIVE_RAM_4000_HU, "8KB RAM kiterjeszÈs engedÈlyezÈse a $4000-$5FFF cÌmen"},
	/* it */ {IDCLS_ENABLE_DRIVE_RAM_4000_IT, "Attiva l'espansione di RAM di 8KB a $4000-$5FFF"},
	/* ko */ {IDCLS_ENABLE_DRIVE_RAM_4000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DRIVE_RAM_4000_NL, "Activeer 8KB RAM uitbreiding op adres $4000-$5FFF"},
	/* pl */ {IDCLS_ENABLE_DRIVE_RAM_4000_PL, "W≥±cz rozszerzenie 8KB RAM w $4000-$5FFF"},
	/* ru */ {IDCLS_ENABLE_DRIVE_RAM_4000_RU, "Enable 8KB RAM expansion at $4000-$5FFF"},
	/* sv */ {IDCLS_ENABLE_DRIVE_RAM_4000_SV, "Aktivera 8KB RAM-expansion pÂ $4000-$5FFF"},
	/* tr */ {IDCLS_ENABLE_DRIVE_RAM_4000_TR, "$4000-$5FFF aras˝nda 8KB RAM geni˛letmeyi aktif et"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DRIVE_RAM_4000,    N_("Disable 8KB RAM expansion at $4000-$5FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DRIVE_RAM_4000_DA, "DeaktivÈr 8kB RAM-udviddelse pÂ $4000-$5FFF"},
	/* de */ {IDCLS_DISABLE_DRIVE_RAM_4000_DE, "8KB RAM Erweiterung bei $4000-5fff deaktivieren"},
	/* es */ {IDCLS_DISABLE_DRIVE_RAM_4000_ES, "Deshabilitar expansiÛn RAM de 8KB en $4000-$5FFF"},
	/* fr */ {IDCLS_DISABLE_DRIVE_RAM_4000_FR, "DÈsactiver l'exansion de 8KB RAM ‡ $4000-$5FFF"},
	/* hu */ {IDCLS_DISABLE_DRIVE_RAM_4000_HU, "8KB RAM kiterjeszÈs tilt·sa a $4000-$5FFF cÌmen"},
	/* it */ {IDCLS_DISABLE_DRIVE_RAM_4000_IT, "Disattiva l'espansione di RAM di 8KB a $4000-$5FFF"},
	/* ko */ {IDCLS_DISABLE_DRIVE_RAM_4000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DRIVE_RAM_4000_NL, "8KB RAM uitbreiding op adres $4000-$5FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DRIVE_RAM_4000_PL, "Wy≥±cz rozszerzenie 8KB RAM w $4000-$5FFF"},
	/* ru */ {IDCLS_DISABLE_DRIVE_RAM_4000_RU, "Disable 8KB RAM expansion at $4000-$5FFF"},
	/* sv */ {IDCLS_DISABLE_DRIVE_RAM_4000_SV, "Inaktivera 8KB RAM-expansion pÂ $4000-$5FFF"},
	/* tr */ {IDCLS_DISABLE_DRIVE_RAM_4000_TR, "$4000-$5FFF aras˝nda 8KB RAM geni˛letmeyi pasifle˛tir"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DRIVE_RAM_6000,    N_("Enable 8KB RAM expansion at $6000-$7FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DRIVE_RAM_6000_DA, "AktivÈr 8kB RAM-udviddelse pÂ $6000-$7FFF"},
	/* de */ {IDCLS_ENABLE_DRIVE_RAM_6000_DE, "8KB RAM Erweiterung bei $6000-7fff aktivieren"},
	/* es */ {IDCLS_ENABLE_DRIVE_RAM_6000_ES, "Permitir expansiÛn RAM de 8KB en $6000-$7FFF"},
	/* fr */ {IDCLS_ENABLE_DRIVE_RAM_6000_FR, "Activer l'exansion de 8KB RAM ‡ $6000-$7FFF"},
	/* hu */ {IDCLS_ENABLE_DRIVE_RAM_6000_HU, "8KB RAM kiterjeszÈs engedÈlyezÈse a $6000-$7FFF cÌmen"},
	/* it */ {IDCLS_ENABLE_DRIVE_RAM_6000_IT, "Attiva l'espansione di RAM di 8KB a $6000-$7FFF"},
	/* ko */ {IDCLS_ENABLE_DRIVE_RAM_6000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DRIVE_RAM_6000_NL, "Activeer 8KB RAM uitbreiding op adres $6000-$7FFF"},
	/* pl */ {IDCLS_ENABLE_DRIVE_RAM_6000_PL, "W≥±cz rozszerzenie 8KB RAM w $6000-$7FFF"},
	/* ru */ {IDCLS_ENABLE_DRIVE_RAM_6000_RU, "Enable 8KB RAM expansion at $6000-$7FFF"},
	/* sv */ {IDCLS_ENABLE_DRIVE_RAM_6000_SV, "Aktivera 8KB RAM-expansion pÂ $6000-$7FFF"},
	/* tr */ {IDCLS_ENABLE_DRIVE_RAM_6000_TR, "$6000-$7FFF aras˝nda 8KB RAM geni˛letmeyi aktif et"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DRIVE_RAM_6000,    N_("Disable 8KB RAM expansion at $6000-$7FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DRIVE_RAM_6000_DA, "DeaktivÈr 8kB RAM-udviddelse pÂ $6000-$7FFF"},
	/* de */ {IDCLS_DISABLE_DRIVE_RAM_6000_DE, "8KB RAM Erweiterung bei $6000-7fff deaktivieren"},
	/* es */ {IDCLS_DISABLE_DRIVE_RAM_6000_ES, "Deshabilitar expansiÛn RAM de 8KB en $6000-$7FFF"},
	/* fr */ {IDCLS_DISABLE_DRIVE_RAM_6000_FR, "DÈsactiver l'exansion de 8KB RAM ‡ $6000-$7FFF"},
	/* hu */ {IDCLS_DISABLE_DRIVE_RAM_6000_HU, "8KB RAM kiterjeszÈs tilt·sa a $6000-$7FFF cÌmen"},
	/* it */ {IDCLS_DISABLE_DRIVE_RAM_6000_IT, "Disattiva l'espansione di RAM di 8KB a $6000-$7FFF"},
	/* ko */ {IDCLS_DISABLE_DRIVE_RAM_6000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DRIVE_RAM_6000_NL, "8KB RAM uitbreiding op adres $6000-$7FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DRIVE_RAM_6000_PL, "Wy≥±cz rozszerzenie 8KB RAM w $6000-$7FFF"},
	/* ru */ {IDCLS_DISABLE_DRIVE_RAM_6000_RU, "Disable 8KB RAM expansion at $6000-$7FFF"},
	/* sv */ {IDCLS_DISABLE_DRIVE_RAM_6000_SV, "Inaktivera 8KB RAM-expansion pÂ $6000-$7FFF"},
	/* tr */ {IDCLS_DISABLE_DRIVE_RAM_6000_TR, "$6000-$7FFF aras˝nda 8KB RAM geni˛letmeyi pasifle˛tir"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DRIVE_RAM_8000,    N_("Enable 8KB RAM expansion at $8000-$9FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DRIVE_RAM_8000_DA, "AktivÈr 8kB RAM-udviddelse pÂ $8000-$9FFF"},
	/* de */ {IDCLS_ENABLE_DRIVE_RAM_8000_DE, "8KB RAM Erweiterung bei $8000-9fff aktivieren"},
	/* es */ {IDCLS_ENABLE_DRIVE_RAM_8000_ES, "Permitir expansiÛn RAM de 8KB en $8000-$9FFF"},
	/* fr */ {IDCLS_ENABLE_DRIVE_RAM_8000_FR, "Activer l'exansion de 8KB RAM ‡ $8000-$9FFF"},
	/* hu */ {IDCLS_ENABLE_DRIVE_RAM_8000_HU, "8KB RAM kiterjeszÈs engedÈlyezÈse a $8000-$9FFF cÌmen"},
	/* it */ {IDCLS_ENABLE_DRIVE_RAM_8000_IT, "Attiva l'espansione di RAM di 8KB a $8000-$9FFF"},
	/* ko */ {IDCLS_ENABLE_DRIVE_RAM_8000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DRIVE_RAM_8000_NL, "Activeer 8KB RAM uitbreiding op adres $8000-$9FFF"},
	/* pl */ {IDCLS_ENABLE_DRIVE_RAM_8000_PL, "W≥±cz rozszerzenie 8KB RAM w $8000-$9FFF"},
	/* ru */ {IDCLS_ENABLE_DRIVE_RAM_8000_RU, "Enable 8KB RAM expansion at $8000-$9FFF"},
	/* sv */ {IDCLS_ENABLE_DRIVE_RAM_8000_SV, "Aktivera 8KB RAM-expansion pÂ $8000-$9FFF"},
	/* tr */ {IDCLS_ENABLE_DRIVE_RAM_8000_TR, "$8000-$9FFF aras˝nda 8KB RAM geni˛letmeyi aktif et"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DRIVE_RAM_8000,    N_("Disable 8KB RAM expansion at $8000-$9FFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DRIVE_RAM_8000_DA, "DeaktivÈr 8kB RAM-udviddelse pÂ $8000-$9FFF"},
	/* de */ {IDCLS_DISABLE_DRIVE_RAM_8000_DE, "8KB RAM Erweiterung bei $8000-9fff deaktivieren"},
	/* es */ {IDCLS_DISABLE_DRIVE_RAM_8000_ES, "Deshabilitar expansiÛn RAM de 8KB en $8000-$9FFF"},
	/* fr */ {IDCLS_DISABLE_DRIVE_RAM_8000_FR, "DÈsactiver l'exansion de 8KB RAM ‡ $8000-$9FFF"},
	/* hu */ {IDCLS_DISABLE_DRIVE_RAM_8000_HU, "8KB RAM kiterjeszÈs tilt·sa a $8000-$9FFF cÌmen"},
	/* it */ {IDCLS_DISABLE_DRIVE_RAM_8000_IT, "Disattiva l'espansione di RAM di 8KB a $8000-$9FFF"},
	/* ko */ {IDCLS_DISABLE_DRIVE_RAM_8000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DRIVE_RAM_8000_NL, "8KB RAM uitbreiding op adres $8000-$9FFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DRIVE_RAM_8000_PL, "Wy≥±cz rozszerzenie 8KB RAM w $8000-$9FFF"},
	/* ru */ {IDCLS_DISABLE_DRIVE_RAM_8000_RU, "Disable 8KB RAM expansion at $8000-$9FFF"},
	/* sv */ {IDCLS_DISABLE_DRIVE_RAM_8000_SV, "Inaktivera 8KB RAM-expansion pÂ $8000-$9FFF"},
	/* tr */ {IDCLS_DISABLE_DRIVE_RAM_8000_TR, "$8000-$9FFF aras˝nda 8KB RAM geni˛letmeyi pasifle˛tir"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DRIVE_RAM_A000,    N_("Enable 8KB RAM expansion at $A000-$BFFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DRIVE_RAM_A000_DA, "AktivÈr 8kB RAM-udviddelse pÂ $A000-$BFFF"},
	/* de */ {IDCLS_ENABLE_DRIVE_RAM_A000_DE, "8KB RAM Erweiterung bei $A000-Bfff aktivieren"},
	/* es */ {IDCLS_ENABLE_DRIVE_RAM_A000_ES, "Permitir expansiÛn RAM de 8KB en $A000-$BFFF"},
	/* fr */ {IDCLS_ENABLE_DRIVE_RAM_A000_FR, "Activer l'exansion de 8KB RAM ‡ $A000-$BFFF"},
	/* hu */ {IDCLS_ENABLE_DRIVE_RAM_A000_HU, "8KB RAM kiterjeszÈs engedÈlyezÈse a $A000-$BFFF cÌmen"},
	/* it */ {IDCLS_ENABLE_DRIVE_RAM_A000_IT, "Attiva l'espansione di RAM di 8KB a $A000-$BFFF"},
	/* ko */ {IDCLS_ENABLE_DRIVE_RAM_A000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DRIVE_RAM_A000_NL, "Activeer 8KB RAM uitbreiding op adres $A000-$BFFF"},
	/* pl */ {IDCLS_ENABLE_DRIVE_RAM_A000_PL, "W≥±cz rozszerzenie 8KB RAM w $A000-$BFFF"},
	/* ru */ {IDCLS_ENABLE_DRIVE_RAM_A000_RU, "Enable 8KB RAM expansion at $A000-$BFFF"},
	/* sv */ {IDCLS_ENABLE_DRIVE_RAM_A000_SV, "Aktivera 8KB RAM-expansion pÂ $A000-$BFFF"},
	/* tr */ {IDCLS_ENABLE_DRIVE_RAM_A000_TR, "$A000-$BFFF aras˝nda 8KB RAM geni˛letmeyi aktif et"},
#endif
	
	/* drive/iec/iec-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DRIVE_RAM_A000,    N_("Disable 8KB RAM expansion at $A000-$BFFF")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DRIVE_RAM_A000_DA, "DeaktivÈr 8kB RAM-udviddelse pÂ $A000-$BFFF"},
	/* de */ {IDCLS_DISABLE_DRIVE_RAM_A000_DE, "8KB RAM Erweiterung bei $A000-Bfff deaktivieren"},
	/* es */ {IDCLS_DISABLE_DRIVE_RAM_A000_ES, "Deshabilitar expansiÛn RAM de 8KB en $A000-$BFFF"},
	/* fr */ {IDCLS_DISABLE_DRIVE_RAM_A000_FR, "DÈsactiver l'exansion de 8KB RAM ‡ $A000-$BFFF"},
	/* hu */ {IDCLS_DISABLE_DRIVE_RAM_A000_HU, "8KB RAM kiterjeszÈs tilt·sa a $A000-$BFFF cÌmen"},
	/* it */ {IDCLS_DISABLE_DRIVE_RAM_A000_IT, "Disattiva l'espansione di RAM di 8KB a $A000-$BFFF"},
	/* ko */ {IDCLS_DISABLE_DRIVE_RAM_A000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DRIVE_RAM_A000_NL, "8KB RAM uitbreiding op adres $A000-$BFFF uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DRIVE_RAM_A000_PL, "Wy≥±cz rozszerzenie 8KB RAM w $A000-$BFFF"},
	/* ru */ {IDCLS_DISABLE_DRIVE_RAM_A000_RU, "Disable 8KB RAM expansion at $A000-$BFFF"},
	/* sv */ {IDCLS_DISABLE_DRIVE_RAM_A000_SV, "Inaktivera 8KB RAM-expansion pÂ $A000-$BFFF"},
	/* tr */ {IDCLS_DISABLE_DRIVE_RAM_A000_TR, "$A000-$BFFF aras˝nda 8KB RAM geni˛letmeyi pasifle˛tir"},
#endif
	
	/* drive/iec/c64exp/c64exp-cmdline-options.c */
	/* en */ {IDCLS_PAR_CABLE_C64EXP_TYPE,    N_("Set parallel cable type (0: none, 1: standard, 2: Dolphin DOS 3, 3: Formel 64)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PAR_CABLE_C64EXP_TYPE_DA, "VÊlg typen af parallelkabel (0: ingen, 1: standard, 2: Dolphin DOS 3 3: Formel 64)"},
	/* de */ {IDCLS_PAR_CABLE_C64EXP_TYPE_DE, "Parallelkabel Typ (0: kein, 1: Standard, 2: Dolphin DOS 3, 3: Formel 64)"},
	/* es */ {IDCLS_PAR_CABLE_C64EXP_TYPE_ES, "Seleccionar tipo de cable paralelo (0:no, 1:estandar, 2:Dolphin DOS 3, 3:Formel 64)"},
	/* fr */ {IDCLS_PAR_CABLE_C64EXP_TYPE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_PAR_CABLE_C64EXP_TYPE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_PAR_CABLE_C64EXP_TYPE_IT, "Imposta il tipo di cavo parallelo (0: none, 1: standard, 2: Dolphin DOS 3, 3: Formel 64)"},
	/* ko */ {IDCLS_PAR_CABLE_C64EXP_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PAR_CABLE_C64EXP_TYPE_NL, "Zet parallele kabelsoort (0: geen, 1: standaard, 2: Dolphin DOS 3, 3: Formel 64)"},
	/* pl */ {IDCLS_PAR_CABLE_C64EXP_TYPE_PL, "Okre∂l typ ≥±cza rÛwnoleg≥ego (0: brak, 1: zwyk≥e, 2: Dolphin DOS 3, 3: Formel 64)"},
	/* ru */ {IDCLS_PAR_CABLE_C64EXP_TYPE_RU, "Set parallel cable type (0: none, 1: standard, 2: Dolphin DOS 3, 3: Formel 64)"},
	/* sv */ {IDCLS_PAR_CABLE_C64EXP_TYPE_SV, "V‰lj typ av parallellkabel (0: ingen, 1: standard, 2: Dolphin DOS 3, 3: Formel 64)"},
	/* tr */ {IDCLS_PAR_CABLE_C64EXP_TYPE_TR, "Paralel kablo tipini belirle (0: yok, 1: standart, 2: Dolphin DOS 3, 3: Formel 64)"},
#endif
	
	/* drive/iec/c64exp/c64exp-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_PROFDOS,    N_("Enable Professional DOS")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_PROFDOS_DA, "AktivÈr Professional DOS"},
	/* de */ {IDCLS_ENABLE_PROFDOS_DE, "Professional DOS aktivieren"},
	/* es */ {IDCLS_ENABLE_PROFDOS_ES, "Permitir DOS profesional"},
	/* fr */ {IDCLS_ENABLE_PROFDOS_FR, "Activer le DOS Professionnel"},
	/* hu */ {IDCLS_ENABLE_PROFDOS_HU, "Professional DOS engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_PROFDOS_IT, "Attiva Professional DOS"},
	/* ko */ {IDCLS_ENABLE_PROFDOS_KO, "Professional DOS ªÁøÎ∞°¥…«œ∞‘ «œ±‚"},
	/* nl */ {IDCLS_ENABLE_PROFDOS_NL, "Activeer Professional DOS"},
	/* pl */ {IDCLS_ENABLE_PROFDOS_PL, "W≥±cz Professional DOS"},
	/* ru */ {IDCLS_ENABLE_PROFDOS_RU, "Enable Professional DOS"},
	/* sv */ {IDCLS_ENABLE_PROFDOS_SV, "Aktivera Professional DOS"},
	/* tr */ {IDCLS_ENABLE_PROFDOS_TR, "Professional DOS'u aktif et"},
#endif
	
	/* drive/iec/c64exp/c64exp-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_PROFDOS,    N_("Disable Professional DOS")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_PROFDOS_DA, "DeaktivÈr Professional DOS"},
	/* de */ {IDCLS_DISABLE_PROFDOS_DE, "Professional DOS deaktivieren"},
	/* es */ {IDCLS_DISABLE_PROFDOS_ES, "Deshabilitar Professional DOS"},
	/* fr */ {IDCLS_DISABLE_PROFDOS_FR, "DÈsactiver le DOS Professionnel"},
	/* hu */ {IDCLS_DISABLE_PROFDOS_HU, "Professional DOS tilt·sa"},
	/* it */ {IDCLS_DISABLE_PROFDOS_IT, "Disattiva Professional DOS"},
	/* ko */ {IDCLS_DISABLE_PROFDOS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_PROFDOS_NL, "Professional DOS uitschakelen"},
	/* pl */ {IDCLS_DISABLE_PROFDOS_PL, "Wy≥±cz Professional DOS"},
	/* ru */ {IDCLS_DISABLE_PROFDOS_RU, "Disable Professional DOS"},
	/* sv */ {IDCLS_DISABLE_PROFDOS_SV, "Inaktivera Professional DOS"},
	/* tr */ {IDCLS_DISABLE_PROFDOS_TR, "Professional DOS'u pasifle˛tir"},
#endif
	
	/* drive/iec/c64exp/c64exp-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME,    N_("Specify name of Professional DOS 1571 ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_DA, "Angiv navn pÂ Professional DOS 1571-ROM-image"},
	/* de */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_DE, "Name von Professional DOS 1571 Datei definieren"},
	/* es */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_ES, "Especificar nombre imagen ROM Professional DOS 1571"},
	/* fr */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_HU, "Adja meg a Professional DOS 1571 ROM kÈpm·st"},
	/* it */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_IT, "Specifica il nome immagine della ROM del Professional DOS 1571"},
	/* ko */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_NL, "Geef de naam van het Professional DOS 1571 ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Professional DOS 1571"},
	/* ru */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_RU, "Specify name of Professional DOS 1571 ROM image"},
	/* sv */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_SV, "Ange namn pÂ Professional DOS 1571-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_PROFDOS_1571_ROM_NAME_TR, "Professional DOS 1571 ROM imaj ismini belirt"},
#endif
	
	/* drive/iec/c64exp/c64exp-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_SUPERCARD,    N_("Enable SuperCard+")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SUPERCARD_DA, "AktivÈr SuperCard+"},
	/* de */ {IDCLS_ENABLE_SUPERCARD_DE, "SuperCard+ aktivieren"},
	/* es */ {IDCLS_ENABLE_SUPERCARD_ES, "Permitir SuperCard+"},
	/* fr */ {IDCLS_ENABLE_SUPERCARD_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_SUPERCARD_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_SUPERCARD_IT, "Attiva SuperCard+"},
	/* ko */ {IDCLS_ENABLE_SUPERCARD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SUPERCARD_NL, "Activeer SuperCard+"},
	/* pl */ {IDCLS_ENABLE_SUPERCARD_PL, "W≥±cz SuperCard+"},
	/* ru */ {IDCLS_ENABLE_SUPERCARD_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_SUPERCARD_SV, "Aktivera SuperCard+"},
	/* tr */ {IDCLS_ENABLE_SUPERCARD_TR, "SuperCard+'˝ aktif et"},
#endif
	
	/* drive/iec/c64exp/c64exp-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_SUPERCARD,    N_("Disable SuperCard+")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SUPERCARD_DA, "DeaktivÈr SuperCard+"},
	/* de */ {IDCLS_DISABLE_SUPERCARD_DE, "SuperCard+ deaktivieren"},
	/* es */ {IDCLS_DISABLE_SUPERCARD_ES, "Deshabilitar SuperCard+"},
	/* fr */ {IDCLS_DISABLE_SUPERCARD_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_SUPERCARD_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_SUPERCARD_IT, "Disattiva SuperCard+"},
	/* ko */ {IDCLS_DISABLE_SUPERCARD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SUPERCARD_NL, "SuperCard+ uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SUPERCARD_PL, "Wy≥±cz SuperCard+"},
	/* ru */ {IDCLS_DISABLE_SUPERCARD_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_SUPERCARD_SV, "Inaktivera SuperCard+"},
	/* tr */ {IDCLS_DISABLE_SUPERCARD_TR, "SuperCard+'˝ pasifle˛tir"},
#endif
	
	/* drive/iec/c64exp/c64exp-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME,    N_("Specify name of SuperCard+ ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_DA, "Angiv navn pÂ SuperCard+ ROM-image"},
	/* de */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_DE, "Name von SuperCard+ ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_ES, "Especificar nombre de Imagen ROM SuperCard+"},
	/* fr */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_IT, "Specifica il nome immagine della ROM del SuperCard+"},
	/* ko */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_NL, "Geef de naam van het SuperCard+ ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM SuperCard+"},
	/* ru */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_SV, "Ange namn pÂ SuperCard+-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_SUPERCARD_ROM_NAME_TR, "SuperCard+ ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* drive/iec/plus4exp/plus4exp-cmdline-options.c */
	/* en */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE,    N_("Set parallel cable type (0: none, 1: standard)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_DA, "VÊlg typen af parallelkabel parallellkabel (0: ingen, 1: standard)"},
	/* de */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_DE, "Parallelkabel Typ (0: kein, 1: Standard)"},
	/* es */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_ES, "Seleccionar tipo de cable paralelo (0:no, 1:standard)"},
	/* fr */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_FR, "DÈfinir le type de c‚ble parallËle (0: aucun, 1: standard)"},
	/* hu */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_HU, "Adja meg a p·rhuzamos k·bel tÌpus·t (0: nincs, 1: standard)"},
	/* it */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_IT, "Imposta il tipo di cavo parallelo (0: nessuno, 1: standard)"},
	/* ko */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_NL, "Zet parallelle kabelsoort (0: geen, 1: standaard)"},
	/* pl */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_PL, "Ustaw typ kabla portu rÛwnoleg≥ego (0: brak, 1: typowy)"},
	/* ru */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_RU, "Set parallel cable type (0: none, 1: standard)"},
	/* sv */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_SV, "V‰lj typ av parallellkabel (0: ingen, 1: standard)"},
	/* tr */ {IDCLS_PAR_CABLE_PLUS4EXP_TYPE_TR, "Paralel kablo tipini ayarlay˝n (0: yok, 1: standart)"},
#endif
	
	/* drive/iec128dcr/iec128dcr-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME,    N_("Specify name of 1571CR DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_DA, "Angiv navn pÂ 1571CR-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_DE, "Name der 1571CR DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_ES, "Especificar nombre imagen DOS ROM 1571CR"},
	/* fr */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1571CR DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_HU, "Adja meg az 1571CR DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1571CR"},
	/* ko */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_NL, "Geef de naam van het 1571CR DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1571CR"},
	/* ru */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_RU, "Specify name of 1571CR DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_SV, "Ange namn pÂ 1571CR-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1571CR_DOS_ROM_NAME_TR, "1571CR DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/ieee/ieee-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME,    N_("Specify name of 2031 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_DA, "Angiv navn pÂ 2031-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_DE, "Name der 2031 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_ES, "Especificar nombre imagen DOS ROM 2031"},
	/* fr */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 2031 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_HU, "Adja meg a 2031 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 2031"},
	/* ko */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_NL, "Geef de naam van het 2031 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 2031"},
	/* ru */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_RU, "Specify name of 2031 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_SV, "Ange namn pÂ 2031-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_2031_DOS_ROM_NAME_TR, "2031 DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/ieee/ieee-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME,    N_("Specify name of 2040 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_DA, "Angiv navn pÂ 2040-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_DE, "Name der 2040 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_ES, "Especificar nombre imagen DOS ROM 2040"},
	/* fr */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 2040 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_HU, "Adja meg a 2040 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 2040"},
	/* ko */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_NL, "Geef de naam van het 2040 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 2040"},
	/* ru */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_RU, "Specify name of 2040 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_SV, "Ange namn pÂ 2040-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_2040_DOS_ROM_NAME_TR, "2040 DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/ieee/ieee-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME,    N_("Specify name of 3040 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_DA, "Angiv navn pÂ 3040-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_DE, "Name der 3040 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_ES, "Especificar nombre imagen DOS ROM 3040"},
	/* fr */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 3040 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_HU, "Adja meg a 3040 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 3040"},
	/* ko */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_NL, "Geef de naam van het 3040 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 3040"},
	/* ru */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_RU, "Specify name of 3040 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_SV, "Ange namn pÂ 3040-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_3040_DOS_ROM_NAME_TR, "3040 DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/ieee/ieee-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME,    N_("Specify name of 4040 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_DA, "Angiv navn pÂ 4040-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_DE, "Name der 4040 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_ES, "Especificar nombre imagen DOS ROM 4040"},
	/* fr */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 4040 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_HU, "Adja meg a 4040 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 4040"},
	/* ko */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_NL, "Geef de naam van het 4040 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 4040"},
	/* ru */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_RU, "Specify name of 4040 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_SV, "Ange namn pÂ 4040-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_4040_DOS_ROM_NAME_TR, "4040 DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/ieee/ieee-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME,    N_("Specify name of 1001/8050/8250 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_DA, "Angiv navn pÂ 1001/8050/8250-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_DE, "Name der 1001/8040/8205 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_ES, "Especificar nombre imagen DOS ROM 1001/8050/8250"},
	/* fr */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1001/8050/8250 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_HU, "Adja meg az 1001/8050/8250 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1001/8050/8250"},
	/* ko */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_NL, "Geef de naam van het 1001/8050/8250 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1001/8050/8250"},
	/* ru */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_RU, "Specify name of 1001/8050/8250 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_SV, "Ange namn pÂ 1001/8050/8250-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1001_DOS_ROM_NAME_TR, "1001/8050/8250 DOS ROM imaj ismini belirt"},
#endif
	
	/* drive/tcbm/tcbm-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME,    N_("Specify name of 1551 DOS ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_DA, "Angiv navn pÂ 1551-DOS-ROM-image"},
	/* de */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_DE, "Name der 1551 DOS ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_ES, "Especificar nombre imagen DOS ROM 1551"},
	/* fr */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_FR, "SpÈcifier le nom de l'image 1551 DOS ROM"},
	/* hu */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_HU, "Adja meg az 1551 DOS ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_IT, "Specifica il nome immagine della ROM del DOS del 1551"},
	/* ko */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_NL, "Geef de naam van het 1551 DOS ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM DOS-a 1551"},
	/* ru */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_RU, "Specify name of 1551 DOS ROM image"},
	/* sv */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_SV, "Ange namn pÂ 1551-DOS-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_1551_DOS_ROM_NAME_TR, "1551 DOS ROM imaj ismini belirt"},
#endif
	
	/* fsdevice/fsdevice-cmdline-options.c */
	/* en */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8,    N_("Use <name> as directory for file system device #8")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_DA, "Brug <navn> som katalog for filsystembaseret drev #8"},
	/* de */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_DE, "Benutze <Name> f¸r Verzeichnis beim Verzeichniszugriff f¸r Ger‰t #8"},
	/* es */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_ES, "Usar <nombre> como directorio fichero sistema perifÈrico #8"},
	/* fr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_FR, "Utiliser le rÈpertoire <nom> comme systËme de fichiers pour le lecteur #8"},
	/* hu */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_HU, "<nÈv> kˆnyvt·r haszn·lata az #8-as egysÈg f·jlrendszerÈnek"},
	/* it */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_IT, "Una <nome> come direcory per il file system della periferica #8"},
	/* ko */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_NL, "Gebruik <naam> als directory voor bestandssysteemapparaat #8"},
	/* pl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_PL, "Uzyj <nazwa> jako katalog urz±dzenia systemu plikÛw #8"},
	/* ru */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_RU, "Use <name> as directory for file system device #8"},
	/* sv */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_SV, "Ange <namn> som katalog fˆr filsystemsbaserad enhet 8"},
	/* tr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_8_TR, "<isim>'i ayg˝t #8'in dosya sistemi dizini olarak kullan"},
#endif
	
	/* fsdevice/fsdevice-cmdline-options.c */
	/* en */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9,    N_("Use <name> as directory for file system device #9")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_DA, "Brug <navn> som katalog for filsystembaseret drev #9"},
	/* de */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_DE, "Benutze <Name> f¸r Verzeichnis beim Verzeichniszugriff f¸r Ger‰t #9"},
	/* es */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_ES, "Usar <nombre> como directorio fichero sistema perifÈrico #9"},
	/* fr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_FR, "Utiliser le rÈpertoire <nom> comme systËme de fichiers pour le lecteur #9"},
	/* hu */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_HU, "<nÈv> kˆnyvt·r haszn·lata az #9-es egysÈg f·jlrendszerÈnek"},
	/* it */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_IT, "Una <nome> come direcory per il file system della periferica #9"},
	/* ko */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_NL, "Gebruik <naam> als directory voor bestandssysteemapparaat #9"},
	/* pl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_PL, "Uzyj <nazwa> jako katalog urz±dzenia systemu plikÛw #9"},
	/* ru */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_RU, "Use <name> as directory for file system device #9"},
	/* sv */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_SV, "Ange <namn> som katalog fˆr filsystemsbaserad enhet 9"},
	/* tr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_9_TR, "<isim>'i ayg˝t #9'un dosya sistemi dizini olarak kullan"},
#endif
	
	/* fsdevice/fsdevice-cmdline-options.c */
	/* en */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10,    N_("Use <name> as directory for file system device #10")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_DA, "Brug <navn> som katalog for filsystembaseret drev #10"},
	/* de */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_DE, "Benutze <Name> f¸r Verzeichnis beim Verzeichniszugriff f¸r Ger‰t #10"},
	/* es */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_ES, "Usar <nombre> como directorio fichero sistema perifÈrico #10"},
	/* fr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_FR, "Utiliser le rÈpertoire <nom> comme systËme de fichiers pour le lecteur #10"},
	/* hu */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_HU, "<nÈv> kˆnyvt·r haszn·lata az #10-es egysÈg f·jlrendszerÈnek"},
	/* it */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_IT, "Una <nome> come direcory per il file system della periferica #10"},
	/* ko */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_NL, "Gebruik <naam> als directory voor bestandssysteemapparaat #10"},
	/* pl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_PL, "Uzyj <nazwa> jako katalog urz±dzenia systemu plikÛw #10"},
	/* ru */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_RU, "Use <name> as directory for file system device #10"},
	/* sv */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_SV, "Ange <namn> som katalog fˆr filsystemsbaserad enhet 10"},
	/* tr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_10_TR, "<isim>'i ayg˝t #10'un dosya sistemi dizini olarak kullan"},
#endif
	
	/* fsdevice/fsdevice-cmdline-options.c */
	/* en */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11,    N_("Use <name> as directory for file system device #11")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_DA, "Brug <navn> som katalog for filsystembaseret drev #11"},
	/* de */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_DE, "Benutze <Name> f¸r Verzeichnis beim Verzeichniszugriff f¸r Ger‰t #11"},
	/* es */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_ES, "Usar <nombre> como directorio fichero sistema perifÈrico #10"},
	/* fr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_FR, "Utiliser le rÈpertoire <nom> comme systËme de fichiers pour le lecteur #11"},
	/* hu */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_HU, "<nÈv> kˆnyvt·r haszn·lata az #11-es egysÈg f·jlrendszerÈnek"},
	/* it */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_IT, "Una <nome> come direcory per il file system della periferica #11"},
	/* ko */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_NL, "Gebruik <naam> als directory voor bestandssysteemapparaat #11"},
	/* pl */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_PL, "Uzyj <nazwa> jako katalog urz±dzenia systemu plikÛw #11"},
	/* ru */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_RU, "Use <name> as directory for file system device #11"},
	/* sv */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_SV, "Ange <namn> som katalog fˆr filsystemsbaserad enhet 11"},
	/* tr */ {IDCLS_USE_AS_DIRECTORY_FSDEVICE_11_TR, "<isim>'i ayg˝t #11'in dosya sistemi dizini olarak kullan"},
#endif
	
#ifdef HAVE_FFMPEG
	/* gfxoutputdrv/ffmpegdrv.c */
	/* en */ {IDCLS_SET_AUDIO_STREAM_BITRATE,    N_("Set bitrate for audio stream in media file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_AUDIO_STREAM_BITRATE_DA, "Angiv bitrate for lydstr¯m i mediefil"},
	/* de */ {IDCLS_SET_AUDIO_STREAM_BITRATE_DE, "Bitrate f¸r Audio Stream f¸r Media Datei setzen"},
	/* es */ {IDCLS_SET_AUDIO_STREAM_BITRATE_ES, "Seleccionar velocidad muestreo para flujo audio en fichero media"},
	/* fr */ {IDCLS_SET_AUDIO_STREAM_BITRATE_FR, "RÈgler le bitrate audio du fichier mÈdia"},
	/* hu */ {IDCLS_SET_AUDIO_STREAM_BITRATE_HU, "Adja meg az audiÛ bitr·t·t a mÈdia f·jlhoz"},
	/* it */ {IDCLS_SET_AUDIO_STREAM_BITRATE_IT, "Imposta il bitrate del flusso audio nel file multimediale"},
	/* ko */ {IDCLS_SET_AUDIO_STREAM_BITRATE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_AUDIO_STREAM_BITRATE_NL, "Zet de bitrate voor het audiogedeelte van het mediabestand"},
	/* pl */ {IDCLS_SET_AUDIO_STREAM_BITRATE_PL, "Okre∂l szybko∂Ê transmisji strumienia audio w pliku multimediÛw"},
	/* ru */ {IDCLS_SET_AUDIO_STREAM_BITRATE_RU, "Set bitrate for audio stream in media file"},
	/* sv */ {IDCLS_SET_AUDIO_STREAM_BITRATE_SV, "Ange bithastighet fˆr ljudstrˆm i mediafil"},
	/* tr */ {IDCLS_SET_AUDIO_STREAM_BITRATE_TR, "Ses ak˝˛˝ iÁin ortam dosyas˝ndaki bith˝z˝'n˝ ayarla"},
#endif
	
	/* gfxoutputdrv/ffmpegdrv.c */
	/* en */ {IDCLS_SET_VIDEO_STREAM_BITRATE,    N_("Set bitrate for video stream in media file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_VIDEO_STREAM_BITRATE_DA, "Angiv bitrate for videostr¯m i mediefil"},
	/* de */ {IDCLS_SET_VIDEO_STREAM_BITRATE_DE, "Bitrate f¸r Video Stream f¸r Media Datei setzen"},
	/* es */ {IDCLS_SET_VIDEO_STREAM_BITRATE_ES, "Seleccionar velocidad muestreo para flujo video en fichero media"},
	/* fr */ {IDCLS_SET_VIDEO_STREAM_BITRATE_FR, "RÈgler le bitrate vidÈo du fichier mÈdia"},
	/* hu */ {IDCLS_SET_VIDEO_STREAM_BITRATE_HU, "Adja meg az videÛ bitr·t·t a mÈdia f·jlhoz"},
	/* it */ {IDCLS_SET_VIDEO_STREAM_BITRATE_IT, "Imposta il bitrate per il flusso video nel file multimediale"},
	/* ko */ {IDCLS_SET_VIDEO_STREAM_BITRATE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_VIDEO_STREAM_BITRATE_NL, "Zet de bitrate voor het videogedeelte van het mediabestand"},
	/* pl */ {IDCLS_SET_VIDEO_STREAM_BITRATE_PL, "Okre∂l szybko∂Ê transmisji strumienia wideo w pliku multimediÛw"},
	/* ru */ {IDCLS_SET_VIDEO_STREAM_BITRATE_RU, "Set bitrate for video stream in media file"},
	/* sv */ {IDCLS_SET_VIDEO_STREAM_BITRATE_SV, "Ange bithastighet fˆr videostrˆm i mediafil"},
	/* tr */ {IDCLS_SET_VIDEO_STREAM_BITRATE_TR, "Gˆr¸nt¸ ak˝˛˝ iÁin ortam dosyas˝ndaki bith˝z˝'n˝ ayarla"},
#endif
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_PET_MODEL,    N_("Specify PET model to emulate")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PET_MODEL_DA, "Angiv emuleret PET-model"},
	/* de */ {IDCLS_SPECIFY_PET_MODEL_DE, "PET Modell spezifizieren"},
	/* es */ {IDCLS_SPECIFY_PET_MODEL_ES, "Especificar modelo PET a emular"},
	/* fr */ {IDCLS_SPECIFY_PET_MODEL_FR, "SpÈcifier le modËle PET ‡ Èmuler"},
	/* hu */ {IDCLS_SPECIFY_PET_MODEL_HU, "Adja meg az emul·lt PET modellt"},
	/* it */ {IDCLS_SPECIFY_PET_MODEL_IT, "Specifica il modello di PET da emulare"},
	/* ko */ {IDCLS_SPECIFY_PET_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PET_MODEL_NL, "Geef PET model om te emuleren"},
	/* pl */ {IDCLS_SPECIFY_PET_MODEL_PL, "Okre∂l emulowany model PET"},
	/* ru */ {IDCLS_SPECIFY_PET_MODEL_RU, "Specify PET model to emulate"},
	/* sv */ {IDCLS_SPECIFY_PET_MODEL_SV, "Ange PET-modell att emulera"},
	/* tr */ {IDCLS_SPECIFY_PET_MODEL_TR, "Em¸le edilecek PET modelini belirt"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_EDITOR_ROM_NAME,    N_("Specify name of Editor ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_DA, "Angiv navn pÂ Editor-ROM-image"},
	/* de */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_DE, "Name f¸r Editor ROM Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_ES, "Especificar nombre imagen editor ROM"},
	/* fr */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_FR, "SpÈcifier le nom de líimage ROM Editor"},
	/* hu */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_HU, "Adja meg a szerkesztı ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_IT, "Specifica il nome immagine della Editor ROM"},
	/* ko */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_NL, "Geef naam van het Editor ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Editor"},
	/* ru */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_RU, "Specify name of Editor ROM image"},
	/* sv */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_SV, "Ange namn pÂ Editor-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_EDITOR_ROM_NAME_TR, "Editor ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME,    N_("Specify 4K extension ROM name at $9***")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_DA, "Angiv navn pÂ 4K-udviddelses-ROM pÂ $9***"},
	/* de */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_DE, "4K Erweiterungs ROM Datei Name bei $9*** definieren"},
	/* es */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_ES, "Especificar nombre extensiÛn ROM 4KB en $9***"},
	/* fr */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_FR, "SpÈcifier le nom de l'extension ROM 4K ‡ $9***"},
	/* hu */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_HU, "Adja meg a $9*** cÌm˚ 4K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_IT, "Specifica il nome della ROM di estensione di 4k a $9***"},
	/* ko */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_NL, "Geef naam van het 4K uitbreiding ROM bestand op adres $9***"},
	/* pl */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_PL, "Okre∂l nazwÍ rozszerzenia 4K ROM w $9***"},
	/* ru */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_RU, "Specify 4K extension ROM name at $9***"},
	/* sv */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_SV, "Ange namn pÂ 4K-utˆknings-ROM pÂ $9***"},
	/* tr */ {IDCLS_SPECIFY_4K_ROM_9XXX_NAME_TR, "$9*** adresindeki 4K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME,    N_("Specify 4K extension ROM name at $A***")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_DA, "Angiv navn pÂ 4K-udviddelses-ROM pÂ $A***"},
	/* de */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_DE, "4K Erweiterungs ROM Datei Name bei $A*** definieren"},
	/* es */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_ES, "Especificar nombre extensiÛn ROM 4KB en $A***"},
	/* fr */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_FR, "SpÈcifier le nom de l'extension ROM 4K ‡ $A***"},
	/* hu */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_HU, "Adja meg a $A*** cÌm˚ 4K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_IT, "Specifica il nome della ROM di estensione di 4k a $A***"},
	/* ko */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_NL, "Geef naam van het 4K uitbreiding ROM bestand op adres $A***"},
	/* pl */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_PL, "Okre∂l nazwÍ rozszerzenia 4K ROM w $A***"},
	/* ru */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_RU, "Specify 4K extension ROM name at $A***"},
	/* sv */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_SV, "Ange namn pÂ 4K-utˆknings-ROM pÂ $A***"},
	/* tr */ {IDCLS_SPECIFY_4K_ROM_AXXX_NAME_TR, "$A*** adresindeki 4K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME,    N_("Specify 4K extension ROM name at $B***")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_DA, "Angiv navn pÂ 4K-udviddelses-ROM pÂ $B***"},
	/* de */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_DE, "4K Erweiterungs ROM Datei Name bei $B*** definieren"},
	/* es */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_ES, "Especificar nombre extensiÛn ROM 4KB en $B***"},
	/* fr */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_FR, "SpÈcifier le nom de l'extension ROM 4K ‡ $B***"},
	/* hu */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_HU, "Adja meg a $B*** cÌm˚ 4K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_IT, "Specifica il nome della ROM di estensione di 4k a $B***"},
	/* ko */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_NL, "Geef naam van het 4K uitbreiding ROM bestand op adres $B***"},
	/* pl */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_PL, "Okre∂l nazwÍ rozszerzenia 4K ROM w $B***"},
	/* ru */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_RU, "Specify 4K extension ROM name at $B***"},
	/* sv */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_SV, "Ange namn pÂ 4K-utˆknings-ROM pÂ $B***"},
	/* tr */ {IDCLS_SPECIFY_4K_ROM_BXXX_NAME_TR, "$B*** adresindeki 4K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000,    N_("Enable PET8296 4K RAM mapping at $9***")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_DA, "AktivÈr PET8296 4K-RAM-mapping pÂ $9***"},
	/* de */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_DE, "PET8296 4K RAM Zuordnung bei $9*** aktivieren"},
	/* es */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_ES, "Permitir mapeado 4KB de RAM PET8296 en $9***"},
	/* fr */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_FR, "Activer l'extension PET8296 4K ‡ $9***"},
	/* hu */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_HU, "PET8296 4K RAM engedÈlyezÈse a $9*** cÌmen"},
	/* it */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_IT, "Attiva la mappatura della RAM di 4K del PET8296 a $9***"},
	/* ko */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_NL, "Activeer PET8296 4K RAM op adres $9***"},
	/* pl */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_PL, "W≥±cz mapowanie 4K RAM PET8296 w $9***"},
	/* ru */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_RU, "Enable PET8296 4K RAM mapping at $9***"},
	/* sv */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_SV, "Aktivera PET8296 4K-RAM-mappning pÂ $9***"},
	/* tr */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_9000_TR, "$9*** adresindeki PET8296 4K RAM e˛le˛tirmesini aktif et"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000,    N_("Disable PET8296 4K RAM mapping at $9***")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_DA, "DeaktivÈr PET8296 4K-RAM-mapping pÂ $9***"},
	/* de */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_DE, "PET8296 4K RAM Zuordnung bei $9*** deaktivieren"},
	/* es */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_ES, "Deshabilitar mapeado 4KB de RAM PET8296 en $9***"},
	/* fr */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_FR, "DÈsactiver l'extension PET8296 4K ‡ $9***"},
	/* hu */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_HU, "PET8296 4K RAM tilt·sa a $9*** cÌmen"},
	/* it */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_IT, "Disattiva la mappatura della RAM di 4K del PET8296 a $9***"},
	/* ko */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_NL, "PET8296 4K RAM op adres $9*** uitschakelen"},
	/* pl */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_PL, "Wy≥±cz mapowanie 4K RAM PET8296 w $9***"},
	/* ru */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_RU, "Disable PET8296 4K RAM mapping at $9***"},
	/* sv */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_SV, "Inaktivera PET8296 4K-RAM-mappning pÂ $9***"},
	/* tr */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_9000_TR, "$9*** adresindeki PET8296 4K RAM e˛le˛tirmesini pasifle˛tir"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000,    N_("Enable PET8296 4K RAM mapping at $A***")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_DA, "AktivÈr PET8296 4K-RAM-mapping pÂ $A***"},
	/* de */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_DE, "PET8296 4K RAM Zuordnung bei $A*** aktivieren"},
	/* es */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_ES, "Permitir mapeado 4KB de RAM PET8296 en $A***"},
	/* fr */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_FR, "Activer l'extension PET8296 4K ‡ $A***"},
	/* hu */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_HU, "PET8296 4K RAM engedÈlyezÈse a $A*** cÌmen"},
	/* it */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_IT, "Attiva la mappatura della RAM di 4K del PET8296 a $A***"},
	/* ko */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_NL, "Activeer PET8296 4K RAM op adres $A***"},
	/* pl */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_PL, "W≥±cz mapowanie 4K RAM PET8296 w $A***"},
	/* ru */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_RU, "Enable PET8296 4K RAM mapping at $A***"},
	/* sv */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_SV, "Aktivera PET8296 4K-RAM-mappning pÂ $A***"},
	/* tr */ {IDCLS_PET8296_ENABLE_4K_RAM_AT_A000_TR, "$A*** adresindeki PET8296 4K RAM e˛le˛tirmesini aktif et"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000,    N_("Disable PET8296 4K RAM mapping at $A***")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_DA, "DeaktivÈr PET8296 4K-RAM-mapping pÂ $A***"},
	/* de */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_DE, "PET8296 4K RAM Zuordnung bei $A*** deaktivieren"},
	/* es */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_ES, "Deshabilitar mapeado 4KB de RAM PET8296 en $A***"},
	/* fr */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_FR, "DÈsactiver l'extension PET8296 4K ‡ $A***"},
	/* hu */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_HU, "PET8296 4K RAM tilt·sa a $A*** cÌmen"},
	/* it */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_IT, "Disattiva la mappatura della RAM di 4K del PET8296 a $A***"},
	/* ko */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_NL, "PET8296 4K RAM op adres $A*** uitschakelen"},
	/* pl */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_PL, "Wy≥±cz mapowanie 4K RAM PET8296 w $A***"},
	/* ru */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_RU, "Disable PET8296 4K RAM mapping at $A***"},
	/* sv */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_SV, "Inaktivera PET8296 4K-RAM-mappning pÂ $A***"},
	/* tr */ {IDCLS_PET8296_DISABLE_4K_RAM_AT_A000_TR, "$A*** adresindeki PET8296 4K RAM e˛le˛tirmesini pasifle˛tir"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_SUPERPET_IO,    N_("Enable SuperPET I/O")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SUPERPET_IO_DA, "AktivÈr SuperPET-I/O"},
	/* de */ {IDCLS_ENABLE_SUPERPET_IO_DE, "SuperPET I/O aktivieren"},
	/* es */ {IDCLS_ENABLE_SUPERPET_IO_ES, "Permitir entrada/salida SuperPET"},
	/* fr */ {IDCLS_ENABLE_SUPERPET_IO_FR, "Activer les E/S SuperPET"},
	/* hu */ {IDCLS_ENABLE_SUPERPET_IO_HU, "SuperPET I/O engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_SUPERPET_IO_IT, "Attiva l'I/O del SuperPET"},
	/* ko */ {IDCLS_ENABLE_SUPERPET_IO_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SUPERPET_IO_NL, "Activeer SuperPET I/O"},
	/* pl */ {IDCLS_ENABLE_SUPERPET_IO_PL, "W≥±cz we/wy SuperPET"},
	/* ru */ {IDCLS_ENABLE_SUPERPET_IO_RU, "Enable SuperPET I/O"},
	/* sv */ {IDCLS_ENABLE_SUPERPET_IO_SV, "Aktivera SuperPET-I/O"},
	/* tr */ {IDCLS_ENABLE_SUPERPET_IO_TR, "SuperPET G/«'˝ aktif et"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_SUPERPET_IO,    N_("Disable SuperPET I/O")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SUPERPET_IO_DA, "DeaktivÈr SuperPET-I/O"},
	/* de */ {IDCLS_DISABLE_SUPERPET_IO_DE, "SuperPET I/O deaktivieren"},
	/* es */ {IDCLS_DISABLE_SUPERPET_IO_ES, "Deshabilitar entrada/salida SuperPET"},
	/* fr */ {IDCLS_DISABLE_SUPERPET_IO_FR, "DÈsactiver les E/S SuperPET"},
	/* hu */ {IDCLS_DISABLE_SUPERPET_IO_HU, "SuperPET I/O tilt·sa"},
	/* it */ {IDCLS_DISABLE_SUPERPET_IO_IT, "Disattiva l'I/O del SuperPET"},
	/* ko */ {IDCLS_DISABLE_SUPERPET_IO_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SUPERPET_IO_NL, "SuperPET I/O uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SUPERPET_IO_PL, "Wy≥±cz we/wy SuperPET"},
	/* ru */ {IDCLS_DISABLE_SUPERPET_IO_RU, "Disable SuperPET I/O"},
	/* sv */ {IDCLS_DISABLE_SUPERPET_IO_SV, "Inaktivera SuperPET-I/O"},
	/* tr */ {IDCLS_DISABLE_SUPERPET_IO_TR, "SuperPET G/«'˝ pasifle˛tir"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES,    N_("Enable ROM 1 Kernal patches")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_DA, "AktivÈr ROM 1 kerneÊndringer"},
	/* de */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_DE, "ROM 1 Kernal patches aktivieren"},
	/* es */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_ES, "Permitir parches ROM 1 Kernal"},
	/* fr */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_FR, "Activer les patches ROM 1 Kernal"},
	/* hu */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_HU, "ROM 1 Kernal foltoz·s engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_IT, "Attiva le patch del Kernal della ROM 1"},
	/* ko */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_NL, "Activeer ROM 1 Kernalverbeteringen"},
	/* pl */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_PL, "W≥±cz ≥atki Kernala ROM 1"},
	/* ru */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_RU, "Enable ROM 1 Kernal patches"},
	/* sv */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_SV, "Aktivera ROM 1-Kernalpatchar"},
	/* tr */ {IDCLS_ENABLE_ROM_1_KERNAL_PATCHES_TR, "ROM 1 Kernal yamalar˝n˝ aktif et"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES,    N_("Disable ROM 1 Kernal patches")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_DA, "DeaktivÈr ROM 1 kerneÊndringer"},
	/* de */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_DE, "ROM 1 Kernal patches deaktivieren"},
	/* es */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_ES, "Deshabilitar parches ROM 1 Kernal"},
	/* fr */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_FR, "DÈsactiver les patches ROM 1 Kernal"},
	/* hu */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_HU, "ROM 1 Kernal foltoz·s tilt·sa"},
	/* it */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_IT, "Disattiva le patch del Kernal della ROM 1"},
	/* ko */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_NL, "ROM 1 Kernalverbeteringen uitschakelen"},
	/* pl */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_PL, "Wy≥±cz ≥atki Kernala ROM 1"},
	/* ru */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_RU, "Disable ROM 1 Kernal patches"},
	/* sv */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_SV, "Inaktivera ROM 1-Kernalpatchar"},
	/* tr */ {IDCLS_DISABLE_ROM_1_KERNAL_PATCHES_TR, "ROM 1 Kernal yamalar˝n˝ pasifle˛tir"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET,    N_("Switch upper/lower case charset")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_DA, "Skift mellem store og smÂ bogstaver"},
	/* de */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_DE, "Wechsel Groﬂ-/Kleinschreibung Zeichensatz"},
	/* es */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_ES, "Intercambiar may˙sculas/min˙scula"},
	/* fr */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_FR, "Inverser le charset majuscule et minuscule"},
	/* hu */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_HU, "V·lt·s nagy-/kisbet˚s karakterkÈszletre"},
	/* it */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_IT, "Scambia il set di caratteri maiuscolo/minuscolo"},
	/* ko */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_NL, "Schakel tussen grote/kleine letters"},
	/* pl */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_PL, "Prze≥±cz zestaw wielkich/ma≥ych znakÛw"},
	/* ru */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_RU, "≤⁄€ÓÁÿ‚Ï “’‡Â›ÿŸ/›ÿ÷›ÿŸ ‡’”ÿ·‚‡"},
	/* sv */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_SV, "V‰xla smÂ/stora bokst‰ver i teckengeneratorn"},
	/* tr */ {IDCLS_SWITCH_UPPER_LOWER_CHARSET_TR, "B¸y¸k/k¸Á¸k harf karakter seti dei˛tir"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET,    N_("Do not switch upper/lower case charset")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_DA, "Skift ikke mellem store og smÂ bogstaver"},
	/* de */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_DE, "Kein Wechsel Groﬂ-/Kleinschreibung Zeichensatz"},
	/* es */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_ES, "No intercambiar may˙sculas/min˙sculas"},
	/* fr */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_FR, "Ne pas inverser le charset majuscule et minuscule"},
	/* hu */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_HU, "Ne v·ltson a nagy-/kisbet˚s karakterkÈszletre"},
	/* it */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_IT, "Non scambiare il set di caratteri maiuscolo/minuscolo"},
	/* ko */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_NL, "Schakel niet tussen grote/kleine letters"},
	/* pl */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_PL, "Nie prze≥±czaj zestawu wielkich/ma≥ych znakÛw"},
	/* ru */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_RU, "Ω’ “⁄€ÓÁ–‚Ï “’‡Â›ÿŸ/›ÿ÷›ÿŸ ‡’”ÿ·‚‡"},
	/* sv */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_SV, "V‰xla inte smÂ/stora bokst‰ver i teckengeneratorn"},
	/* tr */ {IDCLS_NO_SWITCH_UPPER_LOWER_CHARSET_TR, "B¸y¸k/k¸Á¸k harf karakter seti dei˛tirme"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_EOI_BLANKS_SCREEN,    N_("EOI blanks screen")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_EOI_BLANKS_SCREEN_DA, "EOI sletter skÊrmen"},
	/* de */ {IDCLS_EOI_BLANKS_SCREEN_DE, "EOI lˆscht Bildschirm"},
	/* es */ {IDCLS_EOI_BLANKS_SCREEN_ES, "EOI pantalla en blanco"},
	/* fr */ {IDCLS_EOI_BLANKS_SCREEN_FR, "EOI vide l'Ècran"},
	/* hu */ {IDCLS_EOI_BLANKS_SCREEN_HU, "EOI tˆrli a kÈpernyıt"},
	/* it */ {IDCLS_EOI_BLANKS_SCREEN_IT, "EOI oscura lo schermo"},
	/* ko */ {IDCLS_EOI_BLANKS_SCREEN_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_EOI_BLANKS_SCREEN_NL, "EOI maakt het scherm leeg"},
	/* pl */ {IDCLS_EOI_BLANKS_SCREEN_PL, "Koniec przerwania czy∂ci ekran"},
	/* ru */ {IDCLS_EOI_BLANKS_SCREEN_RU, "EOI blanks screen"},
	/* sv */ {IDCLS_EOI_BLANKS_SCREEN_SV, "EOI tˆmmer sk‰rmen"},
	/* tr */ {IDCLS_EOI_BLANKS_SCREEN_TR, "EOI ekran˝ bo˛alt˝r"},
#endif
	
	/* pet/pet-cmdline-options.c */
	/* en */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN,    N_("EOI does not blank screen")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_DA, "EOI sletter ikke skÊrmen"},
	/* de */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_DE, "EIO lˆscht Bildschirm nicht"},
	/* es */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_ES, "EOI pantalla no en blanco"},
	/* fr */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_FR, "EOI ne vide pas l'Ècran"},
	/* hu */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_HU, "EOI nem tˆrli a kÈpernyıt"},
	/* it */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_IT, "EOI non oscura lo schermo"},
	/* ko */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_NL, "EOI maakt het scherm niet leeg"},
	/* pl */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_PL, "Koniec przerwania nie czy∂ci ekranu"},
	/* ru */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_RU, "EOI does not blank screen"},
	/* sv */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_SV, "EOI tˆmmer inte sk‰rmen"},
	/* tr */ {IDCLS_EOI_DOES_NOT_BLANK_SCREEN_TR, "EOI ekran˝ bo˛altmaz"},
#endif
	
	/* pet/petpia1.c */
	/* en */ {IDCLS_ENABLE_USERPORT_DIAG_PIN,    N_("Enable userport diagnostic pin")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_DA, "AktivÈr diagnostik pÂ brugerporten"},
	/* de */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_DE, "Userport Diagnose Pin aktivieren"},
	/* es */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_ES, "Permitir pin puerto diagnostico"},
	/* fr */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_FR, "Activer la pin de diagnostique userport"},
	/* hu */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_HU, "Userport diagnosztikai l·b engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_IT, "Attiva pin diagnostico su userport"},
	/* ko */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_NL, "Activeer userport diagnostic pin"},
	/* pl */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_PL, "W≥±cz pin diagnostyczny userportu"},
	/* ru */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_RU, "Enable userport diagnostic pin"},
	/* sv */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_SV, "Aktivera diagnostik pÂ anv‰ndarporten"},
	/* tr */ {IDCLS_ENABLE_USERPORT_DIAG_PIN_TR, "Userport diyagnostik pinini aktif et"},
#endif
	
	/* pet/petpia1.c */
	/* en */ {IDCLS_DISABLE_USERPORT_DIAG_PIN,    N_("Disable userport diagnostic pin")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_DA, "DeaktivÈr diagnostik pÂ brugerporten"},
	/* de */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_DE, "Userport Diagnose Pin deaktivieren"},
	/* es */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_ES, "Deshabilitar pin puerto diagnostico"},
	/* fr */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_FR, "DÈsactiver la pin de diagnostique userport"},
	/* hu */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_HU, "Userport diagnosztikai l·b tilt·sa"},
	/* it */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_IT, "Disattiva pin diagnostico su userport"},
	/* ko */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_NL, "Userport diagnostic pin uitschakelen"},
	/* pl */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_PL, "Wy≥±cz pin diagnostyczny userportu"},
	/* ru */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_RU, "Disable userport diagnostic pin"},
	/* sv */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_SV, "Inaktivera diagnostik pÂ anv‰ndarporten"},
	/* tr */ {IDCLS_DISABLE_USERPORT_DIAG_PIN_TR, "Userport diyagnostik pinini pasifle˛tir"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME,    N_("Specify name of Function low ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_DA, "Angiv navn pÂ image for lav funktions-ROM"},
	/* de */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_DE, "Namen f¸r Funktions ROM Datei (unterer Bereich) definieren"},
	/* es */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_ES, "Especificar nombre imagen ROM funciÛn baja"},
	/* fr */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_FR, "SpÈcifier le nom de l'image basse ROM Fonction"},
	/* hu */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_HU, "Adja meg az alsÛ Function ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_IT, "Specifica il nome immagine della Function ROM bassa"},
	/* ko */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_NL, "Geef de naam van het Function low ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Function low"},
	/* ru */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_RU, "Specify name of Function low ROM image"},
	/* sv */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_SV, "Ange namn pÂ ROM-avbildning fˆr lÂgt funktions-ROM"},
	/* tr */ {IDCLS_SPECIFY_FUNCTION_LOW_ROM_NAME_TR, "Function low ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME,    N_("Specify name of Function high ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_DA, "Angiv navn pÂ image for h¯j funktions-ROM"},
	/* de */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_DE, "Namen f¸r Funktions ROM Datei (oberer Bereich) definieren"},
	/* es */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_ES, "Especificar nombre imagen ROM funciÛn alta"},
	/* fr */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_FR, "SpÈcifier le nom de l'image haute ROM Fonction"},
	/* hu */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_HU, "Adja meg a felsı Function ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_IT, "Specifica il nome immagine della Function ROM alta"},
	/* ko */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_NL, "Geef de naam van het Function high ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Function high"},
	/* ru */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_RU, "Specify name of Function high ROM image"},
	/* sv */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_SV, "Ange namn pÂ ROM-avbildning fˆr hˆgt funktions-ROM"},
	/* tr */ {IDCLS_SPECIFY_FUNCTION_HIGH_ROM_NAME_TR, "Function high ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME,    N_("Specify name of Cartridge 1 low ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_DA, "Angiv navn pÂ image for lav cartridge 1 ROM"},
	/* de */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_DE, "Name f¸r Erweiterungsmodul 1 ROM Datei (unterer Bereich) definieren"},
	/* es */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_ES, "Especificar nombre imagen ROM cartucho 1 bajo"},
	/* fr */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_FR, "SpÈcifier le nom de l'image basse ROM Cartouche 1"},
	/* hu */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_HU, "Adja meg az alsÛ Cartridge 1 ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_IT, "Specifica il nome immagine della ROM Cartridge 1 bassa"},
	/* ko */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_NL, "Geef de naam van het Cartridge 1 low ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Cartridge 1 low"},
	/* ru */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_RU, "Specify name of Cartridge 1 low ROM image"},
	/* sv */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_SV, "Ange namn pÂ ROM-avbildning fˆr lÂgt insticksmodul 1-ROM"},
	/* tr */ {IDCLS_SPECIFY_CART_1_LOW_ROM_NAME_TR, "Cartridge 1 low ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME,    N_("Specify name of Cartridge 1 high ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_DA, "Angiv navn pÂ image for h¯j cartridge 1 ROM"},
	/* de */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_DE, "Name f¸r Erweiterungsmodul 1 ROM Datei (oberer Bereich) definieren"},
	/* es */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_ES, "Especificar nombre imagen ROM cartucho 1 alto"},
	/* fr */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_FR, "SpÈcifier le nom de l'image haute ROM Cartouche 1"},
	/* hu */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_HU, "Adja meg a felsı Cartridge 1 ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_IT, "Specifica il nome immagine della ROM Cartridge 1 alta"},
	/* ko */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_NL, "Geef de naam van het Cartridge 1 high ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Cartridge 1 high"},
	/* ru */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_RU, "Specify name of Cartridge 1 high ROM image"},
	/* sv */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_SV, "Ange namn pÂ ROM-avbildning fˆr hˆgt insticksmodul 1-ROM"},
	/* tr */ {IDCLS_SPECIFY_CART_1_HIGH_ROM_NAME_TR, "Cartridge 1 high ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME,    N_("Specify name of Cartridge 2 low ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_DA, "Angiv navn pÂ image for lav cartridge 2 ROM"},
	/* de */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_DE, "Name f¸r Erweiterungsmodul 2 ROM Datei (unterer Bereich) definieren"},
	/* es */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_ES, "Especificar nombre imagen ROM cartucho 2 bajo"},
	/* fr */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_FR, "SpÈcifier le nom de l'image basse ROM Cartouche 2"},
	/* hu */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_HU, "Adja meg az alsÛ Cartridge 2 ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_IT, "Specifica il nome immagine della ROM Cartridge 2 bassa"},
	/* ko */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_NL, "Geef de naam van het Cartridge 2 low ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Cartridge 2 low"},
	/* ru */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_RU, "Specify name of Cartridge 2 low ROM image"},
	/* sv */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_SV, "Ange namn pÂ ROM-avbildning fˆr lÂgt insticksmodul 2-ROM"},
	/* tr */ {IDCLS_SPECIFY_CART_2_LOW_ROM_NAME_TR, "Cartridge 2 low ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME,    N_("Specify name of Cartridge 2 high ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_DA, "Angiv navn pÂ image for h¯j cartridge 1 ROM"},
	/* de */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_DE, "Name f¸r Erweiterungsmodul 2 ROM Datei (oberer Bereich) definieren"},
	/* es */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_ES, "Especificar nombre imagen ROM cartucho 2 alto"},
	/* fr */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_FR, "SpÈcifier le nom de l'image haute ROM Cartouche 2"},
	/* hu */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_HU, "Adja meg a felsı Cartridge 2 ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_IT, "Specifica il nome immagine della ROM Cartridge 2 alta"},
	/* ko */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_NL, "Geef de naam van het Cartridge 2 high ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM Cartridge 2 high"},
	/* ru */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_RU, "Specify name of Cartridge 2 high ROM image"},
	/* sv */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_SV, "Ange namn pÂ ROM-avbildning fˆr hˆgt insticksmodul 2-ROM"},
	/* tr */ {IDCLS_SPECIFY_CART_2_HIGH_ROM_NAME_TR, "Cartridge 2 high ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* plus4/plus4-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_RAM_INSTALLED,    N_("Specify size of RAM installed in kb (16/32/64)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RAM_INSTALLED_DA, "Angiv st¯rrelse pÂ installeret RAM i kB (16/32/64)"},
	/* de */ {IDCLS_SPECIFY_RAM_INSTALLED_DE, "Grˆﬂe des emulierten RAM Speichers in kb (16/32/64) spezifizieren"},
	/* es */ {IDCLS_SPECIFY_RAM_INSTALLED_ES, "Especificar tamaÒo RAM instalada en KB (16/32/64)"},
	/* fr */ {IDCLS_SPECIFY_RAM_INSTALLED_FR, "SpÈcifier la taille du RAM installÈ (16/32/64)"},
	/* hu */ {IDCLS_SPECIFY_RAM_INSTALLED_HU, "Adja meg a telepÌtett RAM mÈretÈt kb-ban (16/32/64)"},
	/* it */ {IDCLS_SPECIFY_RAM_INSTALLED_IT, "Specifica la dimensione della RAM installata in kb (16/32/64)"},
	/* ko */ {IDCLS_SPECIFY_RAM_INSTALLED_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RAM_INSTALLED_NL, "Geef de hoeveelheid RAM in kb (16/32/64)"},
	/* pl */ {IDCLS_SPECIFY_RAM_INSTALLED_PL, "Okre∂l ilo∂Ê zainstalowanego RAM-u w kb (16/32/64)"},
	/* ru */ {IDCLS_SPECIFY_RAM_INSTALLED_RU, "Specify size of RAM installed in kb (16/32/64)"},
	/* sv */ {IDCLS_SPECIFY_RAM_INSTALLED_SV, "Ange storlek pÂ installerat RAM i kb (16/32/64)"},
	/* tr */ {IDCLS_SPECIFY_RAM_INSTALLED_TR, "Kurulmu˛ olan RAM boyutunu kb cinsinden belirt (16/32/64)"},
#endif
	
	/* plus4/ted-cmdline-options.c, vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_SATURATION,    N_("Set saturation of internal calculated palette [1000]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_SATURATION_DA, "Indstil mÊtning af internt beregnet palette [1000]"},
	/* de */ {IDCLS_SET_SATURATION_DE, "S‰ttigung f¸r intern berechneten Palette setzen [1000]"},
	/* es */ {IDCLS_SET_SATURATION_ES, "Seleccionar saturaciÛn calculada en paleta interna [1000]"},
	/* fr */ {IDCLS_SET_SATURATION_FR, "RÈgler la saturation de la palette interne calculÈe [1000]"},
	/* hu */ {IDCLS_SET_SATURATION_HU, "A sz·molt paletta telÌtettsÈge [1000]"},
	/* it */ {IDCLS_SET_SATURATION_IT, "Imposta la saturazione della palette calcolata internamente [1000]"},
	/* ko */ {IDCLS_SET_SATURATION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_SATURATION_NL, "Zet de verzadiging van het intern berekend kleurenpalet [1000]"},
	/* pl */ {IDCLS_SET_SATURATION_PL, "Okre∂l nasycenie wewnÍtrznie obliczonej palety kolorystycznej [1000]"},
	/* ru */ {IDCLS_SET_SATURATION_RU, "Set saturation of internal calculated palette [1000]"},
	/* sv */ {IDCLS_SET_SATURATION_SV, "St‰ll in m‰ttnad pÂ internt ber‰knad palett [1000]"},
	/* tr */ {IDCLS_SET_SATURATION_TR, "Dahili hesaplanm˝˛ paletin doygunluunu ayarlay˝n [1000]"},
#endif
	
	/* plus4/ted-cmdline-options.c, vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_CONTRAST,    N_("Set contrast of internal calculated palette [1000]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_CONTRAST_DA, "Indstil kontrast for internt beregnet palette [1000]"},
	/* de */ {IDCLS_SET_CONTRAST_DE, "Kontrast f¸r intern berechnete Palette setzen [1000]"},
	/* es */ {IDCLS_SET_CONTRAST_ES, "Seleccionar contraste calculada en paleta interna [1000]"},
	/* fr */ {IDCLS_SET_CONTRAST_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_CONTRAST_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_CONTRAST_IT, "Imposta il constrasto della palette calcolata internamente [1000]"},
	/* ko */ {IDCLS_SET_CONTRAST_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_CONTRAST_NL, "Zet het contrast van het intern berekend kleurenpalet [1000]"},
	/* pl */ {IDCLS_SET_CONTRAST_PL, "Okre∂l kontrast wewnÍtrznie obliczonej palety kolorystycznej [1000]"},
	/* ru */ {IDCLS_SET_CONTRAST_RU, "Set contrast of internal calculated palette [1000]"},
	/* sv */ {IDCLS_SET_CONTRAST_SV, "St‰ll in kontrast pÂ internt ber‰knad palett [1000]"},
	/* tr */ {IDCLS_SET_CONTRAST_TR, "Dahili hesaplanm˝˛ paletin kar˛˝tl˝˝n˝ ayarlay˝n [1000]"},
#endif
	
	/* plus4/ted-cmdline-options.c, vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_BRIGHTNESS,    N_("Set brightness of internal calculated palette [1000]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_BRIGHTNESS_DA, "Indstil lysstyrke for internt beregnet palette [1000]"},
	/* de */ {IDCLS_SET_BRIGHTNESS_DE, "Helligkeit f¸r intern berechnete Palette setzen [1000]"},
	/* es */ {IDCLS_SET_BRIGHTNESS_ES, "Seleccionar brillo calculada en paleta interna [1000]"},
	/* fr */ {IDCLS_SET_BRIGHTNESS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_BRIGHTNESS_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_BRIGHTNESS_IT, "Imposta la luminanza della palette calcolata internamente [1000]"},
	/* ko */ {IDCLS_SET_BRIGHTNESS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_BRIGHTNESS_NL, "Zet de helderheid van het intern berekend kleurenpalet [1000]"},
	/* pl */ {IDCLS_SET_BRIGHTNESS_PL, "Okre∂l jasno∂Ê wewnÍtrznie obliczonej palety kolorystycznej [1000]"},
	/* ru */ {IDCLS_SET_BRIGHTNESS_RU, "Set brightness of internal calculated palette [1000]"},
	/* sv */ {IDCLS_SET_BRIGHTNESS_SV, "St‰ll in ljusstyrka pÂ internt ber‰knad palett [1000]"},
	/* tr */ {IDCLS_SET_BRIGHTNESS_TR, "Dahili hesaplanm˝˛ paletin parlakl˝˝n˝ ayarlay˝n [1000]"},
#endif
	
	/* plus4/ted-cmdline-options.c`, vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_GAMMA,    N_("Set gamma of internal calculated palette [2200]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_GAMMA_DA, "Indstil gamma for internt beregnet palette [2200]"},
	/* de */ {IDCLS_SET_GAMMA_DE, "Gamma f¸r intern berechnete Palette setzen [2200]"},
	/* es */ {IDCLS_SET_GAMMA_ES, "Seleccionar gamma calculada en paleta interna [2200]"},
	/* fr */ {IDCLS_SET_GAMMA_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_GAMMA_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_GAMMA_IT, "Imposta la gamma della palette calcolata internamente [2200]"},
	/* ko */ {IDCLS_SET_GAMMA_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_GAMMA_NL, "Zet de gamma van het intern berekend kleurenpalet [2200]"},
	/* pl */ {IDCLS_SET_GAMMA_PL, "Okre∂l jaskrawo∂Ê wewnÍtrznie obliczonej palety kolorystycznej [1000]"},
	/* ru */ {IDCLS_SET_GAMMA_RU, "Set gamma of internal calculated palette [2200]"},
	/* sv */ {IDCLS_SET_GAMMA_SV, "St‰ll in gamma pÂ internt ber‰knad palett [2200]"},
	/* tr */ {IDCLS_SET_GAMMA_TR, "Dahili hesaplanm˝˛ paletin gamas˝n˝ ayarlay˝n [2200]"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_TINT,    N_("Set tint of internal calculated palette [1000]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_TINT_DA, "Indstil farvetone for internt beregnet palette [1000]"},
	/* de */ {IDCLS_SET_TINT_DE, "Farbton f¸r intern berechneten Palette setzen [1000]"},
	/* es */ {IDCLS_SET_TINT_ES, "Seleccionar tinta calculada en paleta interna [1000]"},
	/* fr */ {IDCLS_SET_TINT_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_TINT_HU, "A sz·molt, belsı paletta telÌtettsÈge [1000]"},
	/* it */ {IDCLS_SET_TINT_IT, "Imposta la sfumatura della palette calcolata internamente [1000]"},
	/* ko */ {IDCLS_SET_TINT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_TINT_NL, "Zet de tint van het intern berekend kleuren palette [1000]"},
	/* pl */ {IDCLS_SET_TINT_PL, "Okre∂l odcieÒ wewnÍtrznie obliczonej palety kolorystycznej [1000]"},
	/* ru */ {IDCLS_SET_TINT_RU, "Set tint of internal calculated palette [1000]"},
	/* sv */ {IDCLS_SET_TINT_SV, "St‰ll in ton pÂ internt ber‰knad palett [1000]"},
	/* tr */ {IDCLS_SET_TINT_TR, "Dahili hesaplanm˝˛ paletin tonunu ayarlay˝n [1000]"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_ODDLINES_PHASE,    N_("Set phase for color carrier in odd lines [1250]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_ODDLINES_PHASE_DA, "VÊlg fase for farve-bÊreb¯lge pÂ ulige scanlinjer [1250]"},
	/* de */ {IDCLS_SET_ODDLINES_PHASE_DE, "Phase f¸r Farbtr‰ger in ungeraden Zeilen setzen [1250]"},
	/* es */ {IDCLS_SET_ODDLINES_PHASE_ES, "Seleccionar fase trasporte color en lineas impares [1250]"},
	/* fr */ {IDCLS_SET_ODDLINES_PHASE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_ODDLINES_PHASE_HU, "SzÌn vivı f·zisa a p·ratlan sorokban [1250]"},
	/* it */ {IDCLS_SET_ODDLINES_PHASE_IT, "Imposta la fase per la portante colore nelle linee dispari [1250]"},
	/* ko */ {IDCLS_SET_ODDLINES_PHASE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_ODDLINES_PHASE_NL, "Zet de fase van de kleuren drager in oneven lijnen [1250]"},
	/* pl */ {IDCLS_SET_ODDLINES_PHASE_PL, "Okre∂l fazÍ no∂nika koloru w liniach nieparzystych [1250]"},
	/* ru */ {IDCLS_SET_ODDLINES_PHASE_RU, "Set phase for color carrier in odd lines [1250]"},
	/* sv */ {IDCLS_SET_ODDLINES_PHASE_SV, "V‰lj fas fˆr f‰rgb‰rarvÂg pÂ udda rader [1250]"},
	/* tr */ {IDCLS_SET_ODDLINES_PHASE_TR, "Tek sat˝rlardaki renk ta˛˝y˝c˝lar˝ iÁin faz˝ ayarlay˝n [1250]"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_ODDLINES_OFFSET,    N_("Set phase offset for color carrier in odd lines [750]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_ODDLINES_OFFSET_DA, "VÊlg fase-offset for farve-bÊreb¯lge pÂ ulige scanlinjer [750]"},
	/* de */ {IDCLS_SET_ODDLINES_OFFSET_DE, "Phasenoffset f¸r Farbtr‰ger in ungeraden Zeilen setzen [750]"},
	/* es */ {IDCLS_SET_ODDLINES_OFFSET_ES, "Seleccionar aÒadido fase trasporte color en lineas impares [750]"},
	/* fr */ {IDCLS_SET_ODDLINES_OFFSET_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_ODDLINES_OFFSET_HU, "SzÌn vivı f·zis offszet a p·ratlan sorokban [750]"},
	/* it */ {IDCLS_SET_ODDLINES_OFFSET_IT, "Imposta l'offset della fase per la portate colore nelle linee dispari [750]"},
	/* ko */ {IDCLS_SET_ODDLINES_OFFSET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_ODDLINES_OFFSET_NL, "Zet de fase compensatie van de kleuren drager in oneven lijnen [750]"},
	/* pl */ {IDCLS_SET_ODDLINES_OFFSET_PL, "Okre∂l wyrÛwnanie fazy no∂nika koloru w liniach nieparzystych [750]"},
	/* ru */ {IDCLS_SET_ODDLINES_OFFSET_RU, "Set phase offset for color carrier in odd lines [750]"},
	/* sv */ {IDCLS_SET_ODDLINES_OFFSET_SV, "V‰lj fasutj‰mning fˆr f‰rgb‰rarvÂg pÂ udda rader [1250]"},
	/* tr */ {IDCLS_SET_ODDLINES_OFFSET_TR, "Tek sat˝rlardaki renk ta˛˝y˝c˝lar˝ iÁin faz ofsetini ayarlay˝n [750]"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_BLUR,    N_("Amount of horizontal blur for the CRT emulation. [500]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_BLUR_DA, "MÊngden af horizontal udtvÊring for CRT emulering. [500]"},
	/* de */ {IDCLS_SET_BLUR_DE, "Wert f¸r horizontale Unsch‰rfe f¸r CRT Emulation. [500]"},
	/* es */ {IDCLS_SET_BLUR_ES, "Cantidad de borrosidad para emulacion CRT. [500]"},
	/* fr */ {IDCLS_SET_BLUR_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_BLUR_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_BLUR_IT, "Valore della sfuocatura orizzontale per l'emulazione CRT [500]"},
	/* ko */ {IDCLS_SET_BLUR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_BLUR_NL, "Wazigheid hoeveelheid voor de CRT emulatie. [500]"},
	/* pl */ {IDCLS_SET_BLUR_PL, "Rozmycie w poziomie emulacji CRT [500]"},
	/* ru */ {IDCLS_SET_BLUR_RU, "Amount of horizontal blur for the CRT emulation. [500]"},
	/* sv */ {IDCLS_SET_BLUR_SV, "M‰ngd horisontell osk‰rpa fˆr CRT-emulering. [500]"},
	/* tr */ {IDCLS_SET_BLUR_TR, "CRT em¸lasyonu iÁin yatay bulan˝kl˝k miktar˝. [500]"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_SCANLINE_SHADE,    N_("Amount of scan line shading for the CRT emulation [667]")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_SCANLINE_SHADE_DA, "MÊngden af scanlinjeskygge for CRT emulering [667]"},
	/* de */ {IDCLS_SET_SCANLINE_SHADE_DE, "Wert f¸r Scanline Schatten f¸r CRT Emulation [667]"},
	/* es */ {IDCLS_SET_SCANLINE_SHADE_ES, "Cantidad de lineas sombra escaneo para emulaciÛn CRT [667]"},
	/* fr */ {IDCLS_SET_SCANLINE_SHADE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_SCANLINE_SHADE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_SCANLINE_SHADE_IT, "Valore dell'ombreggiatura della scan line per l'emulazione CRT [667]"},
	/* ko */ {IDCLS_SET_SCANLINE_SHADE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_SCANLINE_SHADE_NL, "Hoeveelheid van de scan lijn schaduw voor de CRT emulatie [667]"},
	/* pl */ {IDCLS_SET_SCANLINE_SHADE_PL, "Cieniowanie linii wybierania emulacji CRT [667]"},
	/* ru */ {IDCLS_SET_SCANLINE_SHADE_RU, "Amount of scan line shading for the CRT emulation [667]"},
	/* sv */ {IDCLS_SET_SCANLINE_SHADE_SV, "M‰ngd skannlinjeskuggning i CRT-emuleringen [667]"},
	/* tr */ {IDCLS_SET_SCANLINE_SHADE_TR, "CRT em¸lasyonu iÁin tarama sat˝r˝ n¸ans miktar˝ [667]"},
#endif
	
	/* viciisc/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_VICII_MODEL,    N_("Set VIC-II model (6569/6569r1/8565/6567/8562/6567r56a)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_VICII_MODEL_DA, "VÊlg VIC-II model (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* de */ {IDCLS_SET_VICII_MODEL_DE, "W‰hle VIC-II Modell (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* es */ {IDCLS_SET_VICII_MODEL_ES, "Seleccionar modelo VIC-II (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* fr */ {IDCLS_SET_VICII_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_VICII_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_VICII_MODEL_IT, "Imposta modello VIC-II (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* ko */ {IDCLS_SET_VICII_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_VICII_MODEL_NL, "Zet VIC-II model (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* pl */ {IDCLS_SET_VICII_MODEL_PL, "Ustaw model VIC-II (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* ru */ {IDCLS_SET_VICII_MODEL_RU, "Set VIC-II model (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* sv */ {IDCLS_SET_VICII_MODEL_SV, "V‰lj VIC-II-modell (6569/6569r1/8565/6567/8562/6567r56a)"},
	/* tr */ {IDCLS_SET_VICII_MODEL_TR, "VIC-II modelini ayarla (6569/6569r1/8565/6567/8562/6567r56a)"},
#endif
	
	/* printerdrv/driver-select.c */
	/* en */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME,    N_("Specify name of printer driver for device #4")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_DA, "Angiv navn pÂ printer-driver for enhed #4"},
	/* de */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_DE, "Name f¸r Druckertreiber Ger‰t #4 definieren"},
	/* es */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_ES, "Especificar nombre controlador impresora perifÈrico #4"},
	/* fr */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_FR, "SpÈcifier le nom du pilote imprimante pour le pÈriphÈrique #4"},
	/* hu */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_HU, "Adja meg a #4-es nyomtatÛmeghajtÛ nevÈt"},
	/* it */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_IT, "Specifica il nome del driver di stampa per la periferica #4"},
	/* ko */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_NL, "Geef de naam van het stuurprogramma voor apparaat #4"},
	/* pl */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_PL, "Okre∂l nazwÍ sterownika drukarki urz±dzenia #4"},
	/* ru */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_RU, "Specify name of printer driver for device #4"},
	/* sv */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_SV, "Ange namn pÂ skrivardrivrutin fˆr enhet 4"},
	/* tr */ {IDCLS_SPECIFY_PRT_DRIVER_4_NAME_TR, "Ayg˝t #4 iÁin yaz˝c˝ s¸r¸c¸s¸ ismini belirt"},
#endif
	
	/* printerdrv/driver-select.c */
	/* en */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME,    N_("Specify name of printer driver for device #5")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_DA, "Angiv navn pÂ printer-driver for enhed #5"},
	/* de */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_DE, "Name f¸r Druckertreiber Ger‰t #5 definieren"},
	/* es */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_ES, "Especificar nombre controlador impresora perifÈrico #5"},
	/* fr */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_FR, "SpÈcifier le nom du pilote imprimante pour le pÈriphÈrique #5"},
	/* hu */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_HU, "Adja meg a #5-ˆs nyomtatÛmeghajtÛ nevÈt"},
	/* it */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_IT, "Specifica il nome del driver di stampa per la periferica #5"},
	/* ko */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_NL, "Geef de naam van het stuurprogramma voor apparaat #5"},
	/* pl */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_PL, "Okre∂l nazwÍ sterownika drukarki urz±dzenia #5"},
	/* ru */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_RU, "Specify name of printer driver for device #5"},
	/* sv */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_SV, "Ange namn pÂ skrivardrivrutin fˆr enhet 5"},
	/* tr */ {IDCLS_SPECIFY_PRT_DRIVER_5_NAME_TR, "Ayg˝t #5 iÁin yaz˝c˝ s¸r¸c¸s¸ ismini belirt"},
#endif
	
	/* printerdrv/driver-select.c */
	/* en */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME,    N_("Specify name of printer driver for the userport printer")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_DA, "Angiv navn pÂ printerdriver for brugerport-printer"},
	/* de */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_DE, "Name f¸r Userport Druckertreiber definieren"},
	/* es */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_ES, "Especificar nombre controlador impresiÛn para puerto impresora"},
	/* fr */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_FR, "SpÈcifier le nom du pilote imprimante pour l'imprimante userport"},
	/* hu */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_HU, "Adja meg a userport nyomtatÛmeghajtÛ nevÈt"},
	/* it */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_IT, "Specifica il nome del driver di stampa per la stampante su userport"},
	/* ko */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_NL, "Geef de naam van het stuurprogramma voor de userport printer"},
	/* pl */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_PL, "Okre∂l nazwÍ sterownika drukarki dla drukarki w userporcie"},
	/* ru */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_RU, "Specify name of printer driver for the userport printer"},
	/* sv */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_SV, "Ange namn pÂ skrivardrivrutin fˆr anv‰ndarporten"},
	/* tr */ {IDCLS_SPECIFY_PRT_DRIVER_USR_NAME_TR, "Userport yaz˝c˝s˝ iÁin yaz˝c˝ s¸r¸c¸s¸ ismini belirt"},
#endif
	
	/* printerdrv/interface-serial.c */
	/* en */ {IDCLS_SET_DEVICE_TYPE_4,    N_("Set device type for device #4 (0: NONE, 1: FS, 2: REAL)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DEVICE_TYPE_4_DA, "SÊt enhedstype for enhed #4 (0: INGEN, 1: FS, 2: ∆GTE)"},
	/* de */ {IDCLS_SET_DEVICE_TYPE_4_DE, "Ger‰te Typ f¸r Ger‰t #4 (0: NONE, 1: FS, 2: REAL) setzen"},
	/* es */ {IDCLS_SET_DEVICE_TYPE_4_ES, "Seleccionar tipo para el perifÈrico #4 (0:NO 1:FS, 2:REAL)"},
	/* fr */ {IDCLS_SET_DEVICE_TYPE_4_FR, "SpÈcifier le type de pÈriphÈrique pour #4 (0: AUCUN, 1: SF, 2: R…EL)"},
	/* hu */ {IDCLS_SET_DEVICE_TYPE_4_HU, "Adja meg a #4-es eszkˆz tÌpus·t (0:Nincs, 1: F·jlrendszer, 2: ValÛdi)"},
	/* it */ {IDCLS_SET_DEVICE_TYPE_4_IT, "Specifica il tipo di periferica #4 (0 NESSUNA, 1 FS, 2 REALE)"},
	/* ko */ {IDCLS_SET_DEVICE_TYPE_4_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DEVICE_TYPE_4_NL, "Zet apparaat soort voor apparaat #4 (0: GEEN, 1: FS, 2: ECHT)"},
	/* pl */ {IDCLS_SET_DEVICE_TYPE_4_PL, "Okre∂l typ urz±dzenia #4 (0: BRAK, 1: SYSTEM PLIK”W, 2: RZECZYWISTE)"},
	/* ru */ {IDCLS_SET_DEVICE_TYPE_4_RU, "Set device type for device #4 (0: NONE, 1: FS, 2: REAL)"},
	/* sv */ {IDCLS_SET_DEVICE_TYPE_4_SV, "Ange enhetstyp fˆr enhet 4 (0: INGEN, 1: FS, 2: ƒKTA)"},
	/* tr */ {IDCLS_SET_DEVICE_TYPE_4_TR, "Ayg˝t #4 iÁin ayg˝t tipini ayarlay˝n (0: YOK, 1: FS, 2: GER«EK)"},
#endif
	
	/* printerdrv/interface-serial.c */
	/* en */ {IDCLS_SET_DEVICE_TYPE_5,    N_("Set device type for device #5 (0: NONE, 1: FS, 2: REAL)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DEVICE_TYPE_5_DA, "SÊt enhedstype for enhed #5 (0: INGEN, 1: FS, 2: ∆GTE)"},
	/* de */ {IDCLS_SET_DEVICE_TYPE_5_DE, "Ger‰te Typ f¸r Ger‰t #5 (0: NONE, 1: FS, 2: REAL) setzen"},
	/* es */ {IDCLS_SET_DEVICE_TYPE_5_ES, "Seleccionar tipo para el perifÈrico #5 (0:NO 1:FS, 2:REAL)"},
	/* fr */ {IDCLS_SET_DEVICE_TYPE_5_FR, "SpÈcifier le type de pÈriphÈrique pour #5 (0: AUCUN, 1: SF, 2: R…EL)"},
	/* hu */ {IDCLS_SET_DEVICE_TYPE_5_HU, "Adja meg a #5-ˆs eszkˆz tÌpus·t (0:Nincs, 1: F·jlrendszer, 2: ValÛdi)"},
	/* it */ {IDCLS_SET_DEVICE_TYPE_5_IT, "Specifica il tipo di periferica #5 (0 NESSUNA, 1 FS, 2 REALE)"},
	/* ko */ {IDCLS_SET_DEVICE_TYPE_5_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DEVICE_TYPE_5_NL, "Zet apparaat soort voor apparaat #5 (0: GEEN, 1: FS, 2: ECHT)"},
	/* pl */ {IDCLS_SET_DEVICE_TYPE_5_PL, "Okre∂l typ urz±dzenia #5 (0: BRAK, 1: SYSTEM PLIK”W, 2: RZECZYWISTE)"},
	/* ru */ {IDCLS_SET_DEVICE_TYPE_5_RU, "Set device type for device #5 (0: NONE, 1: FS, 2: REAL)"},
	/* sv */ {IDCLS_SET_DEVICE_TYPE_5_SV, "Ange enhetstyp fˆr enhet 5 (0: INGEN, 1: FS, 2: ƒKTA)"},
	/* tr */ {IDCLS_SET_DEVICE_TYPE_5_TR, "Ayg˝t #5 iÁin ayg˝t tipini ayarlay˝n (0: YOK, 1: FS, 2: GER«EK)"},
#endif
	
	/* printerdrv/interface-userport.c */
	/* en */ {IDCLS_ENABLE_USERPORT_PRINTER,    N_("Enable the userport printer emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_USERPORT_PRINTER_DA, "AktivÈr emulering af printer pÂ brugerporten"},
	/* de */ {IDCLS_ENABLE_USERPORT_PRINTER_DE, "Userport Drucker Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_USERPORT_PRINTER_ES, "Permitir emulaciÛn puerto impresora"},
	/* fr */ {IDCLS_ENABLE_USERPORT_PRINTER_FR, "Acviver l'Èmulation de l'imprimante userport"},
	/* hu */ {IDCLS_ENABLE_USERPORT_PRINTER_HU, "Userport nyomtatÛ emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_USERPORT_PRINTER_IT, "Attiva l'emulazione della stampante su userport"},
	/* ko */ {IDCLS_ENABLE_USERPORT_PRINTER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_USERPORT_PRINTER_NL, "Activeer userport printeremulatie"},
	/* pl */ {IDCLS_ENABLE_USERPORT_PRINTER_PL, "W≥±cz emulacjÍ drukarki w userporcie"},
	/* ru */ {IDCLS_ENABLE_USERPORT_PRINTER_RU, "Enable the userport printer emulation"},
	/* sv */ {IDCLS_ENABLE_USERPORT_PRINTER_SV, "Aktivera emulering av skrivare pÂ anv‰ndarporten"},
	/* tr */ {IDCLS_ENABLE_USERPORT_PRINTER_TR, "Userport yaz˝c˝ em¸lasyonunu aktif et"},
#endif
	
	/* printerdrv/interface-userport.c */
	/* en */ {IDCLS_DISABLE_USERPORT_PRINTER,    N_("Disable the userport printer emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_USERPORT_PRINTER_DA, "DeaktivÈr emulering af printer pÂ brugerporten"},
	/* de */ {IDCLS_DISABLE_USERPORT_PRINTER_DE, "Userport Drucker Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_USERPORT_PRINTER_ES, "Deshabilitar emulaciÛn puerto impresora"},
	/* fr */ {IDCLS_DISABLE_USERPORT_PRINTER_FR, "DÈsactiver l'Èmulation de l'imprimante userport"},
	/* hu */ {IDCLS_DISABLE_USERPORT_PRINTER_HU, "Userport nyomtatÛ emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_USERPORT_PRINTER_IT, "Disattiva l'emulazione della stampante su userport"},
	/* ko */ {IDCLS_DISABLE_USERPORT_PRINTER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_USERPORT_PRINTER_NL, "De userport printeremulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_USERPORT_PRINTER_PL, "Wy≥±cz emulacjÍ drukarki w userporcie"},
	/* ru */ {IDCLS_DISABLE_USERPORT_PRINTER_RU, "Disable the userport printer emulation"},
	/* sv */ {IDCLS_DISABLE_USERPORT_PRINTER_SV, "Inaktivera emulering av skrivare pÂ anv‰ndarporten"},
	/* tr */ {IDCLS_DISABLE_USERPORT_PRINTER_TR, "Userport yaz˝c˝ em¸lasyonunu pasifle˛tir"},
#endif
	
	/* printerdrv/output-select.c */
	/* en */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME,    N_("Specify name of output device for device #4")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_DA, "Angiv navn pÂ uddataenhed for enhed #4"},
	/* de */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_DE, "Name f¸r Druckerausgabe Datei Ger‰t #4 definieren"},
	/* es */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_ES, "Especificar nombre perifÈrico de salida para perifÈrico #4"},
	/* fr */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_FR, "SpÈcifiez le nom du pÈriphÈrique de sortie pour le pÈriphÈrique #4"},
	/* hu */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_HU, "Adja meg a kimeneti eszkˆz nevÈt a #4-es egysÈghez"},
	/* it */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_IT, "Specifica il nome del dispositivo di output per la periferica #4"},
	/* ko */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_NL, "Geef de naam van het uitvoer apparaat voor apparaat #4"},
	/* pl */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_PL, "Okre∂l nazwÍ urz±dzenia wyj∂cia #4"},
	/* ru */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_RU, "Specify name of output device for device #4"},
	/* sv */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_SV, "Ange namn pÂ utskriftsenhet fˆr enhet 4"},
	/* tr */ {IDCLS_SPECIFY_OUTPUT_DEVICE_4_NAME_TR, "Ayg˝t #4 iÁin Á˝k˝˛ ayg˝t˝ ismini belirt"},
#endif
	
	/* printerdrv/output-select.c */
	/* en */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME,    N_("Specify name of output device for device #5")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_DA, "Angiv navn pÂ uddataenhed for enhed #5"},
	/* de */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_DE, "Name f¸r Druckerausgabe Datei Ger‰t #5 definieren"},
	/* es */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_ES, "Especificar nombre perifÈrico de salida para perifÈrico #5"},
	/* fr */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_FR, "SpÈcifiez le nom du pÈriphÈrique de sortie pour le pÈriphÈrique #5"},
	/* hu */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_HU, "Adja meg a kimeneti eszkˆz nevÈt a #5-ˆs egysÈghez"},
	/* it */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_IT, "Specifica il nome del dispositivo di output per la periferica #5"},
	/* ko */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_NL, "Geef de naam van het uitvoer apparaat voor apparaat #5"},
	/* pl */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_PL, "Okre∂l nazwÍ urz±dzenia wyj∂cia #5"},
	/* ru */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_RU, "Specify name of output device for device #5"},
	/* sv */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_SV, "Ange namn pÂ utskriftsenhet fˆr enhet 5"},
	/* tr */ {IDCLS_SPECIFY_OUTPUT_DEVICE_5_NAME_TR, "Ayg˝t #5 iÁin Á˝k˝˛ ayg˝t˝ ismini belirt"},
#endif
	
	/* printerdrv/output-select.c */
	/* en */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME,    N_("Specify name of output device for the userport printer")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_DA, "Angiv navn pÂ uddataenhed for brugerports-printer"},
	/* de */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_DE, "Name f¸r Druckerausgabe Datei Userport definieren"},
	/* es */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_ES, "Especificar nombre perifÈrico de salida para puerto usuario impresora"},
	/* fr */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_FR, "SpÈcifiez le nom du pÈriphÈrique de sortie pour l'imprimante userport"},
	/* hu */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_HU, "Adja meg a kimeneti eszkˆz nevÈt a userport nyomtatÛhoz"},
	/* it */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_IT, "Specifica il nome del dispositivo di output per la stampante su userport"},
	/* ko */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_NL, "Geef de naam van het uitvoer apparaat voor de userport printer"},
	/* pl */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_PL, "Okre∂l nazwÍ urz±dzenia wyj∂ciowego dla drukarki w userporcie"},
	/* ru */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_RU, "Specify name of output device for the userport printer"},
	/* sv */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_SV, "Ange namn pÂ utskriftsenhet fˆr anv‰ndarporten"},
	/* tr */ {IDCLS_SPECIFY_OUTPUT_DEVICE_USR_NAME_TR, "Userport yaz˝c˝s˝ iÁin Á˝k˝˛ ayg˝t˝ ismini belirt"},
#endif
	
	/* printerdrv/output-text.c */
	/* en */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME,    N_("Specify name of printer text device or dump file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_DA, "Angiv navn pÂ printer-tekst-enhed eller dump-fil"},
	/* de */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_DE, "Name f¸r Druckerausgabe Textger‰t oder Dump Datei definieren"},
	/* es */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_ES, "Especificar nombre del perifÈrico para imprimir texto o fichero de volcado"},
	/* fr */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_FR, "SpÈcifier le nom de l'imprimante texte ou \"dump file\""},
	/* hu */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_HU, "Adja meg a szˆvegnyomtatÛ eszkˆz nevÈt, vagy a kimeneti f·jlt"},
	/* it */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_IT, "Specifica il nome del dispositivo testuale di stampa o salva su file"},
	/* ko */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_NL, "Geef de naam van het text apparaat of het dumpbestand"},
	/* pl */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_PL, "Okre∂l nazwÍ urz±dzenia tekstowego drukarki lub pliku zrzutu"},
	/* ru */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_RU, "Specify name of printer text device or dump file"},
	/* sv */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_SV, "Ange namn pÂ textenhet fˆr utskrift eller dumpfil"},
	/* tr */ {IDCLS_SPECIFY_TEXT_DEVICE_DUMP_NAME_TR, "Metin ayg˝t˝ yaz˝c˝s˝ ya da dˆk¸m dosyas˝n˝n ismini belirt"},
#endif
	
	/* printerdrv/output-text.c */
	/* en */ {IDCLS_SPECIFY_TEXT_DEVICE_4,    N_("Specify printer text output device for printer #4")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_TEXT_DEVICE_4_DA, "Angiv printer tekst-uddata enhed for printer #4"},
	/* de */ {IDCLS_SPECIFY_TEXT_DEVICE_4_DE, "Drucker #4 Ger‰t f¸r Textausgabe definieren"},
	/* es */ {IDCLS_SPECIFY_TEXT_DEVICE_4_ES, "Especificar perifÈrico salida impresiÛn texto impresora #4"},
	/* fr */ {IDCLS_SPECIFY_TEXT_DEVICE_4_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_TEXT_DEVICE_4_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_TEXT_DEVICE_4_IT, "Specifica il dispositivo di uscita testuale per la stampante #4"},
	/* ko */ {IDCLS_SPECIFY_TEXT_DEVICE_4_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_TEXT_DEVICE_4_NL, "Geef het tekst uitvoer apparaat voor printer #4"},
	/* pl */ {IDCLS_SPECIFY_TEXT_DEVICE_4_PL, "Okre∂l urz±dzenie wyj∂cia tekstowego drukarki #4"},
	/* ru */ {IDCLS_SPECIFY_TEXT_DEVICE_4_RU, "Specify printer text output device for printer #4"},
	/* sv */ {IDCLS_SPECIFY_TEXT_DEVICE_4_SV, "Ange skrivartextutenhet fˆr skrivare 4"},
	/* tr */ {IDCLS_SPECIFY_TEXT_DEVICE_4_TR, "Yaz˝c˝ #4 iÁin metin Á˝kt˝ ayg˝t˝ yaz˝c˝s˝ belirt"},
#endif
	
	/* printerdrv/output-text.c */
	/* en */ {IDCLS_SPECIFY_TEXT_DEVICE_5,    N_("Specify printer text output device for printer #5")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_TEXT_DEVICE_5_DA, "Angiv printer tekst-uddata enhed for printer #5"},
	/* de */ {IDCLS_SPECIFY_TEXT_DEVICE_5_DE, "Drucker #5 Ger‰t f¸r Textausgabe definieren"},
	/* es */ {IDCLS_SPECIFY_TEXT_DEVICE_5_ES, "Especificar perifÈrico salida impresiÛn texto impresora #5"},
	/* fr */ {IDCLS_SPECIFY_TEXT_DEVICE_5_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_TEXT_DEVICE_5_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_TEXT_DEVICE_5_IT, "Specifica il dispositivo di uscita testuale per la stampante #5"},
	/* ko */ {IDCLS_SPECIFY_TEXT_DEVICE_5_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_TEXT_DEVICE_5_NL, "Geef het tekst uitvoer apparaat voor printer #5"},
	/* pl */ {IDCLS_SPECIFY_TEXT_DEVICE_5_PL, "Okre∂l urz±dzenie wyj∂cia tekstowego drukarki #5"},
	/* ru */ {IDCLS_SPECIFY_TEXT_DEVICE_5_RU, "Specify printer text output device for printer #5"},
	/* sv */ {IDCLS_SPECIFY_TEXT_DEVICE_5_SV, "Ange skrivartextutenhet fˆr skrivare 5"},
	/* tr */ {IDCLS_SPECIFY_TEXT_DEVICE_5_TR, "Yaz˝c˝ #5 iÁin metin Á˝kt˝ ayg˝t˝ yaz˝c˝s˝ belirt"},
#endif
	
	/* printerdrv/output-text.c */
	/* en */ {IDCLS_SPECIFY_TEXT_USERPORT,    N_("Specify printer text output device for userport printer")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_TEXT_USERPORT_DA, "Angiv printer tekst-uddata enhed for brugerports-printer"},
	/* de */ {IDCLS_SPECIFY_TEXT_USERPORT_DE, "IEC Userport Drucker Ger‰t f¸r Textausgabe definieren"},
	/* es */ {IDCLS_SPECIFY_TEXT_USERPORT_ES, "Especificar perifÈrico de salida para imprimir texto impresora puerto usuario"},
	/* fr */ {IDCLS_SPECIFY_TEXT_USERPORT_FR, "SpÈcifier le pÈriphÈrique de sortie text pour l'imprimante userport"},
	/* hu */ {IDCLS_SPECIFY_TEXT_USERPORT_HU, "Adja meg a szˆvegnyomtatÛ eszkˆzt a userport nyomtatÛhoz"},
	/* it */ {IDCLS_SPECIFY_TEXT_USERPORT_IT, "Specifica il nome del dispositivo di output testuale di stampa per la stampante su userport"},
	/* ko */ {IDCLS_SPECIFY_TEXT_USERPORT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_TEXT_USERPORT_NL, "Geef het tekst uitvoer apparaat voor de userport printer"},
	/* pl */ {IDCLS_SPECIFY_TEXT_USERPORT_PL, "Okre∂l urz±dzenie wyj∂cia tekstu dla drukarki w userporcie"},
	/* ru */ {IDCLS_SPECIFY_TEXT_USERPORT_RU, "Specify printer text output device for userport printer"},
	/* sv */ {IDCLS_SPECIFY_TEXT_USERPORT_SV, "Ange skrivartextutenhet fˆr anv‰ndarportsskrivare"},
	/* tr */ {IDCLS_SPECIFY_TEXT_USERPORT_TR, "Userport yaz˝c˝s˝ iÁin metin Á˝kt˝ ayg˝t˝ yaz˝c˝s˝ belirt"},
#endif
	
	/* raster/raster-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_VIDEO_CACHE,    N_("Enable the video cache")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_VIDEO_CACHE_DA, "AktivÈr videocache"},
	/* de */ {IDCLS_ENABLE_VIDEO_CACHE_DE, "Video Cache aktivieren"},
	/* es */ {IDCLS_ENABLE_VIDEO_CACHE_ES, "Permitier cachÈ de video"},
	/* fr */ {IDCLS_ENABLE_VIDEO_CACHE_FR, "Activer le cache vidÈo"},
	/* hu */ {IDCLS_ENABLE_VIDEO_CACHE_HU, "VideÛ gyorsÌtÛt·r engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_VIDEO_CACHE_IT, "Attiva la cache video"},
	/* ko */ {IDCLS_ENABLE_VIDEO_CACHE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_VIDEO_CACHE_NL, "Activeer de videocache"},
	/* pl */ {IDCLS_ENABLE_VIDEO_CACHE_PL, "W≥±cz cache wideo"},
	/* ru */ {IDCLS_ENABLE_VIDEO_CACHE_RU, "Enable the video cache"},
	/* sv */ {IDCLS_ENABLE_VIDEO_CACHE_SV, "Aktivera videocache"},
	/* tr */ {IDCLS_ENABLE_VIDEO_CACHE_TR, "Gˆr¸nt¸ ˆnbelleini aktif et"},
#endif
	
	/* raster/raster-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_VIDEO_CACHE,    N_("Disable the video cache")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_VIDEO_CACHE_DA, "DeaktivÈr videocache"},
	/* de */ {IDCLS_DISABLE_VIDEO_CACHE_DE, "Video Cache deaktivieren"},
	/* es */ {IDCLS_DISABLE_VIDEO_CACHE_ES, "Deshabilitar cachÈ de video"},
	/* fr */ {IDCLS_DISABLE_VIDEO_CACHE_FR, "DÈsactiver le cache vidÈo"},
	/* hu */ {IDCLS_DISABLE_VIDEO_CACHE_HU, "VideÛ gyorsÌtÛt·r tilt·sa"},
	/* it */ {IDCLS_DISABLE_VIDEO_CACHE_IT, "Disattiva la cache video"},
	/* ko */ {IDCLS_DISABLE_VIDEO_CACHE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_VIDEO_CACHE_NL, "De videocache uitschakelen"},
	/* pl */ {IDCLS_DISABLE_VIDEO_CACHE_PL, "Wy≥±cz cache wideo"},
	/* ru */ {IDCLS_DISABLE_VIDEO_CACHE_RU, "Disable the video cache"},
	/* sv */ {IDCLS_DISABLE_VIDEO_CACHE_SV, "Inaktivera videocache"},
	/* tr */ {IDCLS_DISABLE_VIDEO_CACHE_TR, "Gˆr¸nt¸ ˆnbelleini pasifle˛tir"},
#endif
	
#ifdef HAVE_RS232
	/* rs232drv/rs232drv.c */
	/* en */ {IDCLS_SPECIFY_RS232_1_NAME,    N_("Specify name of first RS232 device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RS232_1_NAME_DA, "Angiv navn pÂ f¯rste RS232-enhed"},
	/* de */ {IDCLS_SPECIFY_RS232_1_NAME_DE, "Name f¸r erstes RS232 Ger‰t definieren"},
	/* es */ {IDCLS_SPECIFY_RS232_1_NAME_ES, "Especificar el nombre del primer perifÈrico RS232"},
	/* fr */ {IDCLS_SPECIFY_RS232_1_NAME_FR, "SpÈcifier le nom du 1er pÈriphÈrique RS232"},
	/* hu */ {IDCLS_SPECIFY_RS232_1_NAME_HU, "Adja meg az elsı RS232-es eszkˆz nevÈt"},
	/* it */ {IDCLS_SPECIFY_RS232_1_NAME_IT, "Specifica il nome della prima RS232"},
	/* ko */ {IDCLS_SPECIFY_RS232_1_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RS232_1_NAME_NL, "Geef de naam van het eerste RS232 apparaat"},
	/* pl */ {IDCLS_SPECIFY_RS232_1_NAME_PL, "Okre∂l nazwÍ pierwszego urz±dzenia RS232"},
	/* ru */ {IDCLS_SPECIFY_RS232_1_NAME_RU, "Specify name of first RS232 device"},
	/* sv */ {IDCLS_SPECIFY_RS232_1_NAME_SV, "Ange namn pÂ fˆrsta RS232-enheten"},
	/* tr */ {IDCLS_SPECIFY_RS232_1_NAME_TR, "›lk RS232 ayg˝t˝n˝n ismini belirt"},
#endif
	
	/* rs232drv/rs232drv.c */
	/* en */ {IDCLS_SPECIFY_RS232_2_NAME,    N_("Specify name of second RS232 device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RS232_2_NAME_DA, "Angiv navn pÂ anden RS232-enhed"},
	/* de */ {IDCLS_SPECIFY_RS232_2_NAME_DE, "Name f¸r zweites RS232 Ger‰t definieren"},
	/* es */ {IDCLS_SPECIFY_RS232_2_NAME_ES, "Especificar el nombre del segundo perifÈrico RS232"},
	/* fr */ {IDCLS_SPECIFY_RS232_2_NAME_FR, "SpÈcifier le nom du 2e pÈriphÈrique RS232"},
	/* hu */ {IDCLS_SPECIFY_RS232_2_NAME_HU, "Adja meg a m·sodik RS232-es eszkˆz nevÈt"},
	/* it */ {IDCLS_SPECIFY_RS232_2_NAME_IT, "Specifica il nome della seconda RS232"},
	/* ko */ {IDCLS_SPECIFY_RS232_2_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RS232_2_NAME_NL, "Geef de naam van het tweede RS232 apparaat"},
	/* pl */ {IDCLS_SPECIFY_RS232_2_NAME_PL, "Okre∂l nazwÍ drugiego urz±dzenia RS232"},
	/* ru */ {IDCLS_SPECIFY_RS232_2_NAME_RU, "Specify name of second RS232 device"},
	/* sv */ {IDCLS_SPECIFY_RS232_2_NAME_SV, "Ange namn pÂ andra RS232-enheten"},
	/* tr */ {IDCLS_SPECIFY_RS232_2_NAME_TR, "›kinci RS232 ayg˝t˝n˝n ismini belirt"},
#endif
	
	/* rs232drv/rs232drv.c */
	/* en */ {IDCLS_SPECIFY_RS232_3_NAME,    N_("Specify name of third RS232 device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RS232_3_NAME_DA, "Angiv navn pÂ tredje RS232-enhed"},
	/* de */ {IDCLS_SPECIFY_RS232_3_NAME_DE, "Name f¸r drittes RS232 Ger‰t definieren"},
	/* es */ {IDCLS_SPECIFY_RS232_3_NAME_ES, "Especificar el nombre del tercer perifÈrico RS232"},
	/* fr */ {IDCLS_SPECIFY_RS232_3_NAME_FR, "SpÈcifier le nom du 3e pÈriphÈrique RS232"},
	/* hu */ {IDCLS_SPECIFY_RS232_3_NAME_HU, "Adja meg a harmadik RS232-es eszkˆz nevÈt"},
	/* it */ {IDCLS_SPECIFY_RS232_3_NAME_IT, "Specifica il nome della terza RS232"},
	/* ko */ {IDCLS_SPECIFY_RS232_3_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RS232_3_NAME_NL, "Geef de naam van het derde RS232 apparaat"},
	/* pl */ {IDCLS_SPECIFY_RS232_3_NAME_PL, "Okre∂l nazwÍ trzeciego urz±dzenia RS232"},
	/* ru */ {IDCLS_SPECIFY_RS232_3_NAME_RU, "Specify name of third RS232 device"},
	/* sv */ {IDCLS_SPECIFY_RS232_3_NAME_SV, "Ange namn pÂ tredje RS232-enheten"},
	/* tr */ {IDCLS_SPECIFY_RS232_3_NAME_TR, "‹Á¸nc¸ RS232 ayg˝t˝n˝n ismini belirt"},
#endif
	
	/* rs232drv/rs232drv.c */
	/* en */ {IDCLS_SPECIFY_RS232_4_NAME,    N_("Specify name of fourth RS232 device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RS232_4_NAME_DA, "Angiv navn pÂ fjerde RS232-enhed"},
	/* de */ {IDCLS_SPECIFY_RS232_4_NAME_DE, "Name f¸r viertes RS232 Ger‰t definieren"},
	/* es */ {IDCLS_SPECIFY_RS232_4_NAME_ES, "Especificar el nombre del cuarto perifÈrico RS232"},
	/* fr */ {IDCLS_SPECIFY_RS232_4_NAME_FR, "SpÈcifier le nom du 4e pÈriphÈrique RS232"},
	/* hu */ {IDCLS_SPECIFY_RS232_4_NAME_HU, "Adja meg a negyedik RS232-es eszkˆz nevÈt"},
	/* it */ {IDCLS_SPECIFY_RS232_4_NAME_IT, "Specifica il nome della quarta RS232"},
	/* ko */ {IDCLS_SPECIFY_RS232_4_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RS232_4_NAME_NL, "Geef de naam van het vierde RS232 apparaat"},
	/* pl */ {IDCLS_SPECIFY_RS232_4_NAME_PL, "Okre∂l nazwÍ czwartego urz±dzenia RS232"},
	/* ru */ {IDCLS_SPECIFY_RS232_4_NAME_RU, "Specify name of fourth RS232 device"},
	/* sv */ {IDCLS_SPECIFY_RS232_4_NAME_SV, "Ange namn pÂ fj‰rde RS232-enheten"},
	/* tr */ {IDCLS_SPECIFY_RS232_4_NAME_TR, "Dˆrd¸nc¸ RS232 ayg˝t˝n˝n ismini belirt"},
#endif
#endif
	
	/* rs232drv/rsuser.c */
	/* en */ {IDCLS_ENABLE_RS232_USERPORT,    N_("Enable RS232 userport emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_RS232_USERPORT_DA, "AktivÈr RS232-emulering pÂ brugerporten"},
	/* de */ {IDCLS_ENABLE_RS232_USERPORT_DE, "RS232 Userport Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_RS232_USERPORT_ES, "Permitir emulacion puerto RS232"},
	/* fr */ {IDCLS_ENABLE_RS232_USERPORT_FR, "Activer l'Èmulation de pÈriphÈrique RS232 userport"},
	/* hu */ {IDCLS_ENABLE_RS232_USERPORT_HU, "RS232 userport emul·ciÛ engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_RS232_USERPORT_IT, "Attiva l'emulazione della RS232 su userport"},
	/* ko */ {IDCLS_ENABLE_RS232_USERPORT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_RS232_USERPORT_NL, "Activeer RS232 userportemulatie"},
	/* pl */ {IDCLS_ENABLE_RS232_USERPORT_PL, "W≥±cz emulacjÍ userportu RS232"},
	/* ru */ {IDCLS_ENABLE_RS232_USERPORT_RU, "Enable RS232 userport emulation"},
	/* sv */ {IDCLS_ENABLE_RS232_USERPORT_SV, "Aktivera RS232-emulering pÂ anv‰ndarporten"},
	/* tr */ {IDCLS_ENABLE_RS232_USERPORT_TR, "RS232 userport em¸lasyonunu aktif et"},
#endif
	
	/* rs232drv/rsuser.c */
	/* en */ {IDCLS_DISABLE_RS232_USERPORT,    N_("Disable RS232 userport emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_RS232_USERPORT_DA, "DeaktivÈr RS232-emulering pÂ brugerporten"},
	/* de */ {IDCLS_DISABLE_RS232_USERPORT_DE, "RS232 Userport Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_RS232_USERPORT_ES, "Deshabilitar emulacion puerto RS232"},
	/* fr */ {IDCLS_DISABLE_RS232_USERPORT_FR, "DÈsactiver l'Èmulation de pÈriphÈrique RS232 userport"},
	/* hu */ {IDCLS_DISABLE_RS232_USERPORT_HU, "RS232 userport emul·ciÛ tilt·sa"},
	/* it */ {IDCLS_DISABLE_RS232_USERPORT_IT, "Disattiva l'emulazione della RS232 su userport"},
	/* ko */ {IDCLS_DISABLE_RS232_USERPORT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_RS232_USERPORT_NL, "RS232 userportemulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_RS232_USERPORT_PL, "Wy≥±cz emulacjÍ userportu RS232"},
	/* ru */ {IDCLS_DISABLE_RS232_USERPORT_RU, "Disable RS232 userport emulation"},
	/* sv */ {IDCLS_DISABLE_RS232_USERPORT_SV, "Inaktivera RS232-emulering pÂ anv‰ndarporten"},
	/* tr */ {IDCLS_DISABLE_RS232_USERPORT_TR, "RS232 userport em¸lasyonunu pasifle˛tir"},
#endif
	
	/* rs232drv/rsuser.c */
	/* en */ {IDCLS_P_BAUD,    N_("<baud>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_BAUD_DA, "<baud>"},
	/* de */ {IDCLS_P_BAUD_DE, "<Baud>"},
	/* es */ {IDCLS_P_BAUD_ES, "<baudios>"},
	/* fr */ {IDCLS_P_BAUD_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_BAUD_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_BAUD_IT, "<baud>"},
	/* ko */ {IDCLS_P_BAUD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_BAUD_NL, "<baud>"},
	/* pl */ {IDCLS_P_BAUD_PL, "<bod>"},
	/* ru */ {IDCLS_P_BAUD_RU, "<baud>"},
	/* sv */ {IDCLS_P_BAUD_SV, "<baud>"},
	/* tr */ {IDCLS_P_BAUD_TR, "<baud>"},
#endif
	
	/* rs232drv/rsuser.c */
	/* en */ {IDCLS_SET_BAUD_RS232_USERPORT,    N_("Set the baud rate of the RS232 userport emulation.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_BAUD_RS232_USERPORT_DA, "Angiv baudhastighet for RS232-emuleringen pÂ brugerporten."},
	/* de */ {IDCLS_SET_BAUD_RS232_USERPORT_DE, "Baudrate f¸r RS232 Userport Emulation setzen"},
	/* es */ {IDCLS_SET_BAUD_RS232_USERPORT_ES, "Seleccionar velocidad (baudios) para emulacion puerto RS232"},
	/* fr */ {IDCLS_SET_BAUD_RS232_USERPORT_FR, "SpÈcifiez la vitesse en baud du pÈriphÈrique RS232 userport"},
	/* hu */ {IDCLS_SET_BAUD_RS232_USERPORT_HU, "Bitr·ta megad·sa az RS232 userport emul·ciÛhoz."},
	/* it */ {IDCLS_SET_BAUD_RS232_USERPORT_IT, "Imposta la velocit‡ della RS232 su userport (in baud)"},
	/* ko */ {IDCLS_SET_BAUD_RS232_USERPORT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_BAUD_RS232_USERPORT_NL, "Zet de baud rate van de RS232 userport emulatie."},
	/* pl */ {IDCLS_SET_BAUD_RS232_USERPORT_PL, "Okre∂l prÍdko∂Ê transmisji emulacji userportu RS232."},
	/* ru */ {IDCLS_SET_BAUD_RS232_USERPORT_RU, "Set the baud rate of the RS232 userport emulation."},
	/* sv */ {IDCLS_SET_BAUD_RS232_USERPORT_SV, "Ange baudhastighet fˆr RS232-emuleringen pÂ anv‰ndarporten."},
	/* tr */ {IDCLS_SET_BAUD_RS232_USERPORT_TR, "RS232 userport em¸lasyonunun baud rate'ini ayarla."},
#endif
	
	/* rs232drv/rsuser.c */
	/* en */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT,    N_("Specify VICE RS232 device for userport")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_DA, "Angiv VICE RS232-enhed for brugerporten"},
	/* de */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_DE, "VICE RS232 Ger‰t f¸r Userport definieren"},
	/* es */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_ES, "Especificar perifÈrico VICE RS232 para puerto usuario"},
	/* fr */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_FR, "SpÈcifier un pÈriphÈrique VICE RS232 pour le userport"},
	/* hu */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_HU, "VICE RS232-es userport eszkˆz megad·sa"},
	/* it */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_IT, "Specifica il dispositivo RS232 di VICE per userport"},
	/* ko */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_NL, "Geef VICE RS232 apparaat voor userport"},
	/* pl */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_PL, "Okre∂l urz±dzenie VICE RS232 w userporcie"},
	/* ru */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_RU, "Specify VICE RS232 device for userport"},
	/* sv */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_SV, "Ange VICE RS232-enhet fˆr anv‰ndarporten"},
	/* tr */ {IDCLS_SPECIFY_RS232_DEVICE_USERPORT_TR, "Userport iÁin VICE RS232 ayg˝t˝n˝ belirt"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_ENABLE_IEC_4,    N_("Enable IEC device emulation for device #4")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEC_4_DA, "AktivÈr IEC-enhedsemulering for enhed #4"},
	/* de */ {IDCLS_ENABLE_IEC_4_DE, "IEC Ger‰te Emulation f¸r Ger‰t #4 aktivieren"},
	/* es */ {IDCLS_ENABLE_IEC_4_ES, "Permitir emulaciÛn IEC para perifÈrico #4 "},
	/* fr */ {IDCLS_ENABLE_IEC_4_FR, "Activer l'Èmulation IEC pour le pÈriphÈrique #4"},
	/* hu */ {IDCLS_ENABLE_IEC_4_HU, "IEC eszkˆz #4 emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEC_4_IT, "Attiva emulazione IEC per la periferica #4"},
	/* ko */ {IDCLS_ENABLE_IEC_4_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEC_4_NL, "Activeer IEC apparaat emulatie voor apparaat #4"},
	/* pl */ {IDCLS_ENABLE_IEC_4_PL, "W≥±cz emulacjÍ IEC urz±dzenia #4"},
	/* ru */ {IDCLS_ENABLE_IEC_4_RU, "Enable IEC device emulation for device #4"},
	/* sv */ {IDCLS_ENABLE_IEC_4_SV, "Aktivera IEC-enhetsemulering fˆr enhet 4"},
	/* tr */ {IDCLS_ENABLE_IEC_4_TR, "Ayg˝t #4 iÁin IEC ayg˝t em¸lasyonunu aktif et"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_DISABLE_IEC_4,    N_("Disable IEC device emulation for device #4")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEC_4_DA, "DeaktivÈr IEC-enhedsemulering for enhed #4"},
	/* de */ {IDCLS_DISABLE_IEC_4_DE, "IEC Ger‰te Emulation f¸r Ger‰t #4 deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEC_4_ES, "Deshabilitar emulaciÛn IEC para perifÈrico #4 "},
	/* fr */ {IDCLS_DISABLE_IEC_4_FR, "DÈsactiver l'Èmulation IEC pour le pÈriphÈrique #4"},
	/* hu */ {IDCLS_DISABLE_IEC_4_HU, "IEC eszkˆz #4 emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEC_4_IT, "Disattiva emulazione IEC per la periferica #4"},
	/* ko */ {IDCLS_DISABLE_IEC_4_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEC_4_NL, "IEC apparaat emulatie voor apparaat #4 uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEC_4_PL, "Wy≥±cz emulacjÍ urz±dzenia IEC dla urz±dzenia #4"},
	/* ru */ {IDCLS_DISABLE_IEC_4_RU, "Disable IEC device emulation for device #4"},
	/* sv */ {IDCLS_DISABLE_IEC_4_SV, "Inaktivera IEC-enhetsemulering fˆr enhet 4"},
	/* tr */ {IDCLS_DISABLE_IEC_4_TR, "Ayg˝t #4 iÁin IEC ayg˝t em¸lasyonunu pasifle˛tir"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_ENABLE_IEC_5,    N_("Enable IEC device emulation for device #5")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEC_5_DA, "AktivÈr IEC-enhedsemulering for enhed #5"},
	/* de */ {IDCLS_ENABLE_IEC_5_DE, "IEC Ger‰te Emulation f¸r Ger‰t #5 aktivieren"},
	/* es */ {IDCLS_ENABLE_IEC_5_ES, "Permitir emulaciÛn IEC para perifÈrico #5"},
	/* fr */ {IDCLS_ENABLE_IEC_5_FR, "Activer l'Èmulation IEC pour le pÈriphÈrique #5"},
	/* hu */ {IDCLS_ENABLE_IEC_5_HU, "IEC eszkˆz #5 emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEC_5_IT, "Attiva emulazione IEC per la periferica #5"},
	/* ko */ {IDCLS_ENABLE_IEC_5_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEC_5_NL, "Activeer IEC apparaat emulatie voor apparaat #5"},
	/* pl */ {IDCLS_ENABLE_IEC_5_PL, "W≥±cz emulacjÍ IEC urz±dzenia #5"},
	/* ru */ {IDCLS_ENABLE_IEC_5_RU, "Enable IEC device emulation for device #5"},
	/* sv */ {IDCLS_ENABLE_IEC_5_SV, "Aktivera IEC-enhetsemulering fˆr enhet 5"},
	/* tr */ {IDCLS_ENABLE_IEC_5_TR, "Ayg˝t #5 iÁin IEC ayg˝t em¸lasyonunu aktif et"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_DISABLE_IEC_5,    N_("Disable IEC device emulation for device #5")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEC_5_DA, "DeaktivÈr IEC-enhedsemulering for enhed #5"},
	/* de */ {IDCLS_DISABLE_IEC_5_DE, "IEC Ger‰te Emulation f¸r Ger‰t #5 deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEC_5_ES, "Deshabilitar emulaciÛn IEC para perifÈrico #5"},
	/* fr */ {IDCLS_DISABLE_IEC_5_FR, "DÈsactiver l'Èmulation IEC pour le pÈriphÈrique #5"},
	/* hu */ {IDCLS_DISABLE_IEC_5_HU, "IEC eszkˆz #5 emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEC_5_IT, "Disattiva emulazione IEC per la periferica #5"},
	/* ko */ {IDCLS_DISABLE_IEC_5_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEC_5_NL, "IEC apparaat emulatie voor apparaat #5 uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEC_5_PL, "Wy≥±cz emulacjÍ urz±dzenia IEC dla urz±dzenia #5"},
	/* ru */ {IDCLS_DISABLE_IEC_5_RU, "Disable IEC device emulation for device #5"},
	/* sv */ {IDCLS_DISABLE_IEC_5_SV, "Inaktivera IEC-enhetsemulering fˆr enhet 5"},
	/* tr */ {IDCLS_DISABLE_IEC_5_TR, "Ayg˝t #5 iÁin IEC ayg˝t em¸lasyonunu pasifle˛tir"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_ENABLE_IEC_8,    N_("Enable IEC device emulation for device #8")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEC_8_DA, "AktivÈr IEC-enhedsemulering for enhed #8"},
	/* de */ {IDCLS_ENABLE_IEC_8_DE, "IEC Ger‰te Emulation f¸r Ger‰t #8 aktivieren"},
	/* es */ {IDCLS_ENABLE_IEC_8_ES, "Permitir emulaciÛn IEC para perifÈrico #8"},
	/* fr */ {IDCLS_ENABLE_IEC_8_FR, "Activer l'Èmulation IEC pour le lecteur #8"},
	/* hu */ {IDCLS_ENABLE_IEC_8_HU, "IEC eszkˆz #8 emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEC_8_IT, "Attiva emulazione IEC per la periferica #8"},
	/* ko */ {IDCLS_ENABLE_IEC_8_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEC_8_NL, "Activeer IEC apparaat emulatie voor apparaat #8"},
	/* pl */ {IDCLS_ENABLE_IEC_8_PL, "W≥±cz emulacjÍ IEC urz±dzenia #8"},
	/* ru */ {IDCLS_ENABLE_IEC_8_RU, "Enable IEC device emulation for device #8"},
	/* sv */ {IDCLS_ENABLE_IEC_8_SV, "Aktivera IEC-enhetsemulering fˆr enhet 8"},
	/* tr */ {IDCLS_ENABLE_IEC_8_TR, "Ayg˝t #8 iÁin IEC ayg˝t em¸lasyonunu aktif et"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_DISABLE_IEC_8,    N_("Disable IEC device emulation for device #8")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEC_8_DA, "DeaktivÈr IEC-enhedsemulering for enhed #8"},
	/* de */ {IDCLS_DISABLE_IEC_8_DE, "IEC Ger‰te Emulation f¸r Ger‰t #8 deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEC_8_ES, "Deshabilitar emulaciÛn IEC para perifÈrico #8"},
	/* fr */ {IDCLS_DISABLE_IEC_8_FR, "DÈsactiver l'Èmulation IEC pour le lecteur #8"},
	/* hu */ {IDCLS_DISABLE_IEC_8_HU, "IEC eszkˆz #8 emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEC_8_IT, "Disattiva emulazione IEC per la periferica #8"},
	/* ko */ {IDCLS_DISABLE_IEC_8_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEC_8_NL, "IEC apparaat emulatie voor apparaat #8 uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEC_8_PL, "Wy≥±cz emulacjÍ urz±dzenia IEC dla urz±dzenia #8"},
	/* ru */ {IDCLS_DISABLE_IEC_8_RU, "Disable IEC device emulation for device #8"},
	/* sv */ {IDCLS_DISABLE_IEC_8_SV, "Inaktivera IEC-enhetsemulering fˆr enhet 8"},
	/* tr */ {IDCLS_DISABLE_IEC_8_TR, "Ayg˝t #8 iÁin IEC ayg˝t em¸lasyonunu pasifle˛tir"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_ENABLE_IEC_9,    N_("Enable IEC device emulation for device #9")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEC_9_DA, "AktivÈr IEC-enhedsemulering for enhed #9"},
	/* de */ {IDCLS_ENABLE_IEC_9_DE, "IEC Ger‰te Emulation f¸r Ger‰t #9 aktivieren"},
	/* es */ {IDCLS_ENABLE_IEC_9_ES, "Permitir emulaciÛn IEC para perifÈrico #9"},
	/* fr */ {IDCLS_ENABLE_IEC_9_FR, "Activer l'Èmulation IEC pour le lecteur #9"},
	/* hu */ {IDCLS_ENABLE_IEC_9_HU, "IEC eszkˆz #9 emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEC_9_IT, "Attiva emulazione IEC per la periferica #9"},
	/* ko */ {IDCLS_ENABLE_IEC_9_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEC_9_NL, "Activeer IEC apparaat emulatie voor apparaat #9"},
	/* pl */ {IDCLS_ENABLE_IEC_9_PL, "W≥±cz emulacjÍ IEC urz±dzenia #9"},
	/* ru */ {IDCLS_ENABLE_IEC_9_RU, "Enable IEC device emulation for device #9"},
	/* sv */ {IDCLS_ENABLE_IEC_9_SV, "Aktivera IEC-enhetsemulering fˆr enhet 9"},
	/* tr */ {IDCLS_ENABLE_IEC_9_TR, "Ayg˝t #9 iÁin IEC ayg˝t em¸lasyonunu aktif et"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_DISABLE_IEC_9,    N_("Disable IEC device emulation for device #9")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEC_9_DA, "DeaktivÈr IEC-enhedsemulering for enhed #9"},
	/* de */ {IDCLS_DISABLE_IEC_9_DE, "IEC Ger‰te Emulation f¸r Ger‰t #9 deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEC_9_ES, "Deshabilitar emulaciÛn IEC para perifÈrico #9"},
	/* fr */ {IDCLS_DISABLE_IEC_9_FR, "DÈsactiver l'Èmulation IEC pour le lecteur #9"},
	/* hu */ {IDCLS_DISABLE_IEC_9_HU, "IEC eszkˆz #9 emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEC_9_IT, "Disattiva emulazione IEC per la periferica #9"},
	/* ko */ {IDCLS_DISABLE_IEC_9_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEC_9_NL, "IEC apparaat emulatie voor apparaat #9 uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEC_9_PL, "Wy≥±cz emulacjÍ urz±dzenia IEC dla urz±dzenia #9"},
	/* ru */ {IDCLS_DISABLE_IEC_9_RU, "Disable IEC device emulation for device #9"},
	/* sv */ {IDCLS_DISABLE_IEC_9_SV, "Inaktivera IEC-enhetsemulering fˆr enhet 9"},
	/* tr */ {IDCLS_DISABLE_IEC_9_TR, "Ayg˝t #9 iÁin IEC ayg˝t em¸lasyonunu pasifle˛tir"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_ENABLE_IEC_10,    N_("Enable IEC device emulation for device #10")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEC_10_DA, "AktivÈr IEC-enhedsemulering for enhed #10"},
	/* de */ {IDCLS_ENABLE_IEC_10_DE, "IEC Ger‰te Emulation f¸r Ger‰t #10 aktivieren"},
	/* es */ {IDCLS_ENABLE_IEC_10_ES, "Permitir emulaciÛn IEC para perifÈrico #10"},
	/* fr */ {IDCLS_ENABLE_IEC_10_FR, "Activer l'Èmulation IEC pour le lecteur #10"},
	/* hu */ {IDCLS_ENABLE_IEC_10_HU, "IEC eszkˆz #10 emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEC_10_IT, "Attiva emulazione IEC per la periferica #10"},
	/* ko */ {IDCLS_ENABLE_IEC_10_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEC_10_NL, "Activeer IEC apparaat emulatie voor apparaat #10"},
	/* pl */ {IDCLS_ENABLE_IEC_10_PL, "W≥±cz emulacjÍ IEC urz±dzenia #10"},
	/* ru */ {IDCLS_ENABLE_IEC_10_RU, "Enable IEC device emulation for device #10"},
	/* sv */ {IDCLS_ENABLE_IEC_10_SV, "Aktivera IEC-enhetsemulering fˆr enhet 10"},
	/* tr */ {IDCLS_ENABLE_IEC_10_TR, "Ayg˝t #10 iÁin IEC ayg˝t em¸lasyonunu aktif et"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_DISABLE_IEC_10,    N_("Disable IEC device emulation for device #10")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEC_10_DA, "DeaktivÈr IEC-enhedsemulering for enhed #10"},
	/* de */ {IDCLS_DISABLE_IEC_10_DE, "IEC Ger‰te Emulation f¸r Ger‰t #10 deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEC_10_ES, "Deshabilitar emulaciÛn IEC para perifÈrico #10"},
	/* fr */ {IDCLS_DISABLE_IEC_10_FR, "DÈsactiver l'Èmulation IEC pour le lecteur #10"},
	/* hu */ {IDCLS_DISABLE_IEC_10_HU, "IEC eszkˆz #10 emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEC_10_IT, "Disattiva emulazione IEC per la periferica #10"},
	/* ko */ {IDCLS_DISABLE_IEC_10_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEC_10_NL, "IEC apparaat emulatie voor apparaat #10 uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEC_10_PL, "Wy≥±cz emulacjÍ urz±dzenia IEC dla urz±dzenia #10"},
	/* ru */ {IDCLS_DISABLE_IEC_10_RU, "Disable IEC device emulation for device #10"},
	/* sv */ {IDCLS_DISABLE_IEC_10_SV, "Inaktivera IEC-enhetsemulering fˆr enhet 10"},
	/* tr */ {IDCLS_DISABLE_IEC_10_TR, "Ayg˝t #10 iÁin IEC ayg˝t em¸lasyonunu pasifle˛tir"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_ENABLE_IEC_11,    N_("Enable IEC device emulation for device #11")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_IEC_11_DA, "AktivÈr IEC-enhedsemulering for enhed #11"},
	/* de */ {IDCLS_ENABLE_IEC_11_DE, "IEC Ger‰te Emulation f¸r Ger‰t #11 aktivieren"},
	/* es */ {IDCLS_ENABLE_IEC_11_ES, "Permitir emulaciÛn IEC para perifÈrico #11"},
	/* fr */ {IDCLS_ENABLE_IEC_11_FR, "Activer l'Èmulation IEC pour le lecteur #11"},
	/* hu */ {IDCLS_ENABLE_IEC_11_HU, "IEC eszkˆz #11 emul·ciÛj·nak engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_IEC_11_IT, "Attiva emulazione IEC per la periferica #11"},
	/* ko */ {IDCLS_ENABLE_IEC_11_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_IEC_11_NL, "Activeer IEC apparaat emulatie voor apparaat #11"},
	/* pl */ {IDCLS_ENABLE_IEC_11_PL, "W≥±cz emulacjÍ IEC urz±dzenia #11"},
	/* ru */ {IDCLS_ENABLE_IEC_11_RU, "Enable IEC device emulation for device #11"},
	/* sv */ {IDCLS_ENABLE_IEC_11_SV, "Aktivera IEC-enhetsemulering fˆr enhet 11"},
	/* tr */ {IDCLS_ENABLE_IEC_11_TR, "Ayg˝t #11 iÁin IEC ayg˝t em¸lasyonunu aktif et"},
#endif
	
	/* serial/serial-iec-device.c */
	/* en */ {IDCLS_DISABLE_IEC_11,    N_("Disable IEC device emulation for device #11")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_IEC_11_DA, "DeaktivÈr IEC-enhedsemulering for enhed #11"},
	/* de */ {IDCLS_DISABLE_IEC_11_DE, "IEC Ger‰te Emulation f¸r Ger‰t #11 deaktivieren"},
	/* es */ {IDCLS_DISABLE_IEC_11_ES, "Deshabilitar emulaciÛn IEC para perifÈrico #11"},
	/* fr */ {IDCLS_DISABLE_IEC_11_FR, "DÈsactiver l'Èmulation IEC pour le lecteur #11"},
	/* hu */ {IDCLS_DISABLE_IEC_11_HU, "IEC eszkˆz #11 emul·ciÛj·nak tilt·sa"},
	/* it */ {IDCLS_DISABLE_IEC_11_IT, "Disattiva emulazione IEC per la periferica #11"},
	/* ko */ {IDCLS_DISABLE_IEC_11_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_IEC_11_NL, "IEC apparaat emulatie voor apparaat #11 uitschakelen"},
	/* pl */ {IDCLS_DISABLE_IEC_11_PL, "Wy≥±cz emulacjÍ urz±dzenia IEC dla urz±dzenia #11"},
	/* ru */ {IDCLS_DISABLE_IEC_11_RU, "Disable IEC device emulation for device #11"},
	/* sv */ {IDCLS_DISABLE_IEC_11_SV, "Inaktivera IEC-enhetsemulering fˆr enhet 11"},
	/* tr */ {IDCLS_DISABLE_IEC_11_TR, "Ayg˝t #11 iÁin IEC ayg˝t em¸lasyonunu pasifle˛tir"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_P_ENGINE_MODEL,    N_("<engine and model>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_ENGINE_MODEL_DA, "<motor og model>"},
	/* de */ {IDCLS_P_ENGINE_MODEL_DE, "<Engine und Modell>"},
	/* es */ {IDCLS_P_ENGINE_MODEL_ES, "<motor y modelo>"},
	/* fr */ {IDCLS_P_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_ENGINE_MODEL_IT, "<motore e modello>"},
	/* ko */ {IDCLS_P_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_ENGINE_MODEL_NL, "<kern en model>"},
	/* pl */ {IDCLS_P_ENGINE_MODEL_PL, "<silnik i model>"},
	/* ru */ {IDCLS_P_ENGINE_MODEL_RU, "<engine and model>"},
	/* sv */ {IDCLS_P_ENGINE_MODEL_SV, "<motor och modell>"},
	/* tr */ {IDCLS_P_ENGINE_MODEL_TR, "<motor ve model>"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_P_AMOUNT,    N_("<amount>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_AMOUNT_DA, "<antal>"},
	/* de */ {IDCLS_P_AMOUNT_DE, "<Anzahl>"},
	/* es */ {IDCLS_P_AMOUNT_ES, "<cantidad>"},
	/* fr */ {IDCLS_P_AMOUNT_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_AMOUNT_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_AMOUNT_IT, "<numero>"},
	/* ko */ {IDCLS_P_AMOUNT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_AMOUNT_NL, "<hoeveelheid>"},
	/* pl */ {IDCLS_P_AMOUNT_PL, "<ilo∂Ê>"},
	/* ru */ {IDCLS_P_AMOUNT_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_P_AMOUNT_SV, "<antal>"},
	/* tr */ {IDCLS_P_AMOUNT_TR, "<adet>"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_AMOUNT_EXTRA_SIDS,    N_("amount of extra SID chips")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_AMOUNT_EXTRA_SIDS_DA, "antal ekstra SID-kredse"},
	/* de */ {IDCLS_AMOUNT_EXTRA_SIDS_DE, "Anzahl der extra SID Chips"},
	/* es */ {IDCLS_AMOUNT_EXTRA_SIDS_ES, "Cantidad de chips SID extra"},
	/* fr */ {IDCLS_AMOUNT_EXTRA_SIDS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_AMOUNT_EXTRA_SIDS_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_AMOUNT_EXTRA_SIDS_IT, "numero di SID chip aggiuntivi"},
	/* ko */ {IDCLS_AMOUNT_EXTRA_SIDS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_AMOUNT_EXTRA_SIDS_NL, "Aantal extra SID chips"},
	/* pl */ {IDCLS_AMOUNT_EXTRA_SIDS_PL, "Liczba dodatkowych czipÛw SID"},
	/* ru */ {IDCLS_AMOUNT_EXTRA_SIDS_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_AMOUNT_EXTRA_SIDS_SV, "antal extra SID-kretsar"},
	/* tr */ {IDCLS_AMOUNT_EXTRA_SIDS_TR, "ekstra SID Áiplerinin adedi"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_FASTSID_ENGINE_MODEL,    N_("0: FastSID 6581, 1: FastSID 8580")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_FASTSID_ENGINE_MODEL_DA, "0: FastSID 6581, 1: FastSID 8580"},
	/* de */ {IDCLS_FASTSID_ENGINE_MODEL_DE, "0: FastSID 6581, 1: FastSID 8580"},
	/* es */ {IDCLS_FASTSID_ENGINE_MODEL_ES, "0: FastSID 6581, 1: FastSID 8580"},
	/* fr */ {IDCLS_FASTSID_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_FASTSID_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_FASTSID_ENGINE_MODEL_IT, "0: FastSID 6581, 1: FastSID 8580"},
	/* ko */ {IDCLS_FASTSID_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_FASTSID_ENGINE_MODEL_NL, "0: FastSID 6581, 1: FastSID 8580"},
	/* pl */ {IDCLS_FASTSID_ENGINE_MODEL_PL, "0: FastSID 6581, 1: FastSID 8580"},
	/* ru */ {IDCLS_FASTSID_ENGINE_MODEL_RU, "0: FastSID 6581, 1: FastSID 8580"},
	/* sv */ {IDCLS_FASTSID_ENGINE_MODEL_SV, "0: FastSID 6581, 1: FastSID 8580"},
	/* tr */ {IDCLS_FASTSID_ENGINE_MODEL_TR, "0: FastSID 6581, 1: FastSID 8580"},
#endif
	
#ifdef HAVE_RESID
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_RESID_ENGINE_MODEL,    N_("256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RESID_ENGINE_MODEL_DA, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digitalforstÊrkning"},
	/* de */ {IDCLS_RESID_ENGINE_MODEL_DE, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost"},
	/* es */ {IDCLS_RESID_ENGINE_MODEL_ES, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost"},
	/* fr */ {IDCLS_RESID_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_RESID_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_RESID_ENGINE_MODEL_IT, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost"},
	/* ko */ {IDCLS_RESID_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_RESID_ENGINE_MODEL_NL, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost"},
	/* pl */ {IDCLS_RESID_ENGINE_MODEL_PL, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost"},
	/* ru */ {IDCLS_RESID_ENGINE_MODEL_RU, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost"},
	/* sv */ {IDCLS_RESID_ENGINE_MODEL_SV, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digifˆrst‰rkning"},
	/* tr */ {IDCLS_RESID_ENGINE_MODEL_TR, "256: ReSID 6581, 257: ReSID 8580, 258: ReSID 8580 + digiboost"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_RESIDDTV_ENGINE_MODEL,    N_("260: DTVSID")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RESIDDTV_ENGINE_MODEL_DA, "260: DTVSID"},
	/* de */ {IDCLS_RESIDDTV_ENGINE_MODEL_DE, "260: DTVSID"},
	/* es */ {IDCLS_RESIDDTV_ENGINE_MODEL_ES, "260: DTVSID"},
	/* fr */ {IDCLS_RESIDDTV_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_RESIDDTV_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_RESIDDTV_ENGINE_MODEL_IT, "260: DTVSID"},
	/* ko */ {IDCLS_RESIDDTV_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_RESIDDTV_ENGINE_MODEL_NL, "260: DTVSID"},
	/* pl */ {IDCLS_RESIDDTV_ENGINE_MODEL_PL, "260: DTVSID"},
	/* ru */ {IDCLS_RESIDDTV_ENGINE_MODEL_RU, "260: DTVSID"},
	/* sv */ {IDCLS_RESIDDTV_ENGINE_MODEL_SV, "260: DTVSID"},
	/* tr */ {IDCLS_RESIDDTV_ENGINE_MODEL_TR, "260: DTVSID"},
#endif
#endif
	
#ifdef HAVE_CATWEASELMKIII
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL,    N_("512: Catweasel")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_DA, "512: Catweasel"},
	/* de */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_DE, "512: Catweasel"},
	/* es */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_ES, "512: Catweasel"},
	/* fr */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_IT, "512: Catweasel"},
	/* ko */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_NL, "512: Catweasel"},
	/* pl */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_PL, "512: Catweasel"},
	/* ru */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_RU, "512: Catweasel"},
	/* sv */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_SV, "512: Catweasel"},
	/* tr */ {IDCLS_CATWEASELMKIII_ENGINE_MODEL_TR, "512: Catweasel"},
#endif
#endif
	
#ifdef HAVE_HARDSID
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_HARDSID_ENGINE_MODEL,    N_("768: HardSID")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_HARDSID_ENGINE_MODEL_DA, "768: HardSID"},
	/* de */ {IDCLS_HARDSID_ENGINE_MODEL_DE, "768: HardSID"},
	/* es */ {IDCLS_HARDSID_ENGINE_MODEL_ES, "768: HardSID"},
	/* fr */ {IDCLS_HARDSID_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_HARDSID_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_HARDSID_ENGINE_MODEL_IT, "768: HardSID"},
	/* ko */ {IDCLS_HARDSID_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_HARDSID_ENGINE_MODEL_NL, "768: HardSID"},
	/* pl */ {IDCLS_HARDSID_ENGINE_MODEL_PL, "768: HardSID"},
	/* ru */ {IDCLS_HARDSID_ENGINE_MODEL_RU, "768: HardSID"},
	/* sv */ {IDCLS_HARDSID_ENGINE_MODEL_SV, "768: HardSID"},
	/* tr */ {IDCLS_HARDSID_ENGINE_MODEL_TR, "768: HardSID"},
#endif
#endif
	
#ifdef HAVE_PARSID
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_PARSID_ENGINE_MODEL,    N_("1024: ParSID in par port 1, 1280: ParSID in par port 2, 1536: ParSID in par port 3")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PARSID_ENGINE_MODEL_DA, "1024: ParSID pÂ port 1, 1280: ParSID pÂ port 2, 1536: ParSID pÂ port 3"},
	/* de */ {IDCLS_PARSID_ENGINE_MODEL_DE, "1024: ParSID in par port 1, 1280: ParSID in par port 2, 1536: ParSID in par port 3"},
	/* es */ {IDCLS_PARSID_ENGINE_MODEL_ES, "1024: ParSID in par port 1, 1280: ParSID in par port 2, 1536: ParSID in par port 3"},
	/* fr */ {IDCLS_PARSID_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_PARSID_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_PARSID_ENGINE_MODEL_IT, "1024: ParSID in par port 1, 1280: ParSID in par port 2, 1536: ParSID in par port 3"},
	/* ko */ {IDCLS_PARSID_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PARSID_ENGINE_MODEL_NL, "1024: ParSID in par port 1, 1280: ParSID in par port 2, 1536: ParSID in par port 3"},
	/* pl */ {IDCLS_PARSID_ENGINE_MODEL_PL, "1024: ParSID in porcie par 1, 1280: ParSID w porcie par 2, 1536: ParSID in porcie par 3"},
	/* ru */ {IDCLS_PARSID_ENGINE_MODEL_RU, "1024: ParSID in par port 1, 1280: ParSID in par port 2, 1536: ParSID in par port 3"},
	/* sv */ {IDCLS_PARSID_ENGINE_MODEL_SV, "1024: ParSID i parport 1, 1280: ParSID i parport 2, 1536: ParSID i parport 3"},
	/* tr */ {IDCLS_PARSID_ENGINE_MODEL_TR, "1024: Par port 1'de ParSID, 1280: Par port 2'de ParSID, 1536: Par port 3'de ParSID"},
#endif
#endif
	
#ifdef HAVE_RESID_FP
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_RESIDFP_ENGINE_MODEL,    N_("1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RESIDFP_ENGINE_MODEL_DA, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D"},
	/* de */ {IDCLS_RESIDFP_ENGINE_MODEL_DE, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D"},
	/* es */ {IDCLS_RESIDFP_ENGINE_MODEL_ES, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D"},
	/* fr */ {IDCLS_RESIDFP_ENGINE_MODEL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_RESIDFP_ENGINE_MODEL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_RESIDFP_ENGINE_MODEL_IT, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D"},
	/* ko */ {IDCLS_RESIDFP_ENGINE_MODEL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_RESIDFP_ENGINE_MODEL_NL, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489 + digiboost"},
	/* pl */ {IDCLS_RESIDFP_ENGINE_MODEL_PL, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D"},
	/* ru */ {IDCLS_RESIDFP_ENGINE_MODEL_RU, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D"},
	/* sv */ {IDCLS_RESIDFP_ENGINE_MODEL_SV, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digifˆrst‰rkning, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489 + digifˆrst‰rkning"},
	/* tr */ {IDCLS_RESIDFP_ENGINE_MODEL_TR, "1800: ReSID-FP 6581R3 4885, 1801: ReSID-FP 6581R3 0486S, 1802: ReSID-FP 6581R3 3984, 1803: ReSID-FP 6581R4 AR 3789, 1804: ReSID-FP 6581R3 4485, 1805: ReSID-FP 6581R4 1986S, 1808: ReSID-FP 8580R5 3691, 1809: ReSID-FP 8580R5 3691 + digiboost, 1810: ReSID-FP 8580R5 1489, 1811: ReSID-FP 8580R5 1489D"},
#endif
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_SIDCART,    N_("Enable the SID cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SIDCART_DA, "AktivÈr SID-cartridget"},
	/* de */ {IDCLS_ENABLE_SIDCART_DE, "SID Modul aktivieren"},
	/* es */ {IDCLS_ENABLE_SIDCART_ES, "Permitir cartucho SID"},
	/* fr */ {IDCLS_ENABLE_SIDCART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_SIDCART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_SIDCART_IT, "Attiva cartuccia SID"},
	/* ko */ {IDCLS_ENABLE_SIDCART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SIDCART_NL, "*Activeer de SID cartridge"},
	/* pl */ {IDCLS_ENABLE_SIDCART_PL, "W≥±cz kartridø SID"},
	/* ru */ {IDCLS_ENABLE_SIDCART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_SIDCART_SV, "Aktivera SID-insticksmodul"},
	/* tr */ {IDCLS_ENABLE_SIDCART_TR, "SID kartu˛unu aktif et"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_SIDCART,    N_("Disable the SID cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SIDCART_DA, "DeaktivÈr SID-cartridge"},
	/* de */ {IDCLS_DISABLE_SIDCART_DE, "SID Modul deaktivieren"},
	/* es */ {IDCLS_DISABLE_SIDCART_ES, "Deshabilitar cartucho SID"},
	/* fr */ {IDCLS_DISABLE_SIDCART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_SIDCART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_SIDCART_IT, "Disattiva la cartuccia SID"},
	/* ko */ {IDCLS_DISABLE_SIDCART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SIDCART_NL, "De SID cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SIDCART_PL, "Wy≥±cz kartridø SID"},
	/* ru */ {IDCLS_DISABLE_SIDCART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_SIDCART_SV, "Inaktivera SID-insticksmodul"},
	/* tr */ {IDCLS_DISABLE_SIDCART_TR, "SID kartu˛unu pasifle˛tir"},
#endif
	
	/* sid/sid-cmdline-options.c, c64/plus60k, c64/c64_256k.c */
	/* en */ {IDCLS_P_BASE_ADDRESS,    N_("<Base address>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_BASE_ADDRESS_DA, "<Baseadresse>"},
	/* de */ {IDCLS_P_BASE_ADDRESS_DE, "<Basis Adresse>"},
	/* es */ {IDCLS_P_BASE_ADDRESS_ES, "<DirecciÛn base>"},
	/* fr */ {IDCLS_P_BASE_ADDRESS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_BASE_ADDRESS_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_BASE_ADDRESS_IT, "<Indirizzo base>"},
	/* ko */ {IDCLS_P_BASE_ADDRESS_KO, "<∫£¿ÃΩ∫ ¡÷º“>"},
	/* nl */ {IDCLS_P_BASE_ADDRESS_NL, "<Basisadres>"},
	/* pl */ {IDCLS_P_BASE_ADDRESS_PL, "<Adres bazowy>"},
	/* ru */ {IDCLS_P_BASE_ADDRESS_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_P_BASE_ADDRESS_SV, "<Basadress>"},
	/* tr */ {IDCLS_P_BASE_ADDRESS_TR, "<Taban adresi>"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_SID_2_ADDRESS,    N_("Specify base address for 2nd SID")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SID_2_ADDRESS_DA, "Angiv baseadresse for sekundÊr SID"},
	/* de */ {IDCLS_SPECIFY_SID_2_ADDRESS_DE, "Basis Adresse f¸r zweiten SID definieren"},
	/* es */ {IDCLS_SPECIFY_SID_2_ADDRESS_ES, "Especificar direcciÛn base para el segundo ISD"},
	/* fr */ {IDCLS_SPECIFY_SID_2_ADDRESS_FR, "SpÈcifier l'adresse de base pour le second SID"},
	/* hu */ {IDCLS_SPECIFY_SID_2_ADDRESS_HU, "Adja meg a b·ziscÌmÈt a m·sodik SID-nek"},
	/* it */ {IDCLS_SPECIFY_SID_2_ADDRESS_IT, "Specifica l'indirizzo di base per il secondo SID"},
	/* ko */ {IDCLS_SPECIFY_SID_2_ADDRESS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SID_2_ADDRESS_NL, "Geef het basisadres van de 2e SID"},
	/* pl */ {IDCLS_SPECIFY_SID_2_ADDRESS_PL, "Okre∂l adres bazowy drugiego SID-a"},
	/* ru */ {IDCLS_SPECIFY_SID_2_ADDRESS_RU, "Specify base address for 2nd SID"},
	/* sv */ {IDCLS_SPECIFY_SID_2_ADDRESS_SV, "Ange basadress fˆr andra SID"},
	/* tr */ {IDCLS_SPECIFY_SID_2_ADDRESS_TR, "2nci SID iÁin taban adresini belirt"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_SID_3_ADDRESS,    N_("Specify base address for 3rd SID")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SID_3_ADDRESS_DA, "Angiv baseadresse for tredie SID"},
	/* de */ {IDCLS_SPECIFY_SID_3_ADDRESS_DE, "Basis Adresse f¸r dritten SID definieren"},
	/* es */ {IDCLS_SPECIFY_SID_3_ADDRESS_ES, "Especificar direcciÛn base para el tercer SID"},
	/* fr */ {IDCLS_SPECIFY_SID_3_ADDRESS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_SID_3_ADDRESS_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_SID_3_ADDRESS_IT, "Specifica l'indirizzo di base per il terzo SID"},
	/* ko */ {IDCLS_SPECIFY_SID_3_ADDRESS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SID_3_ADDRESS_NL, "Geef het basisadres van de 3e SID"},
	/* pl */ {IDCLS_SPECIFY_SID_3_ADDRESS_PL, "Okre∂l adres bazowy trzeciego SID-a"},
	/* ru */ {IDCLS_SPECIFY_SID_3_ADDRESS_RU, "Specify base address for 3rd SID"},
	/* sv */ {IDCLS_SPECIFY_SID_3_ADDRESS_SV, "Ange basadress fˆr tredje SID"},
	/* tr */ {IDCLS_SPECIFY_SID_3_ADDRESS_TR, "3¸nc¸ SID iÁin taban adresini belirt"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_SID_FILTERS,    N_("Emulate SID filters")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SID_FILTERS_DA, "EmulÈr SID-filtre"},
	/* de */ {IDCLS_ENABLE_SID_FILTERS_DE, "SID Filter Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_SID_FILTERS_ES, "Emular filtros SID"},
	/* fr */ {IDCLS_ENABLE_SID_FILTERS_FR, "…muler les filtres SID"},
	/* hu */ {IDCLS_ENABLE_SID_FILTERS_HU, "SID sz˚rık emul·ciÛja"},
	/* it */ {IDCLS_ENABLE_SID_FILTERS_IT, "Emula i filtri del SID"},
	/* ko */ {IDCLS_ENABLE_SID_FILTERS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SID_FILTERS_NL, "Emuleer SID filters"},
	/* pl */ {IDCLS_ENABLE_SID_FILTERS_PL, "Emuluj filtry SID"},
	/* ru */ {IDCLS_ENABLE_SID_FILTERS_RU, "Emulate SID filters"},
	/* sv */ {IDCLS_ENABLE_SID_FILTERS_SV, "Emulera SID-filter"},
	/* tr */ {IDCLS_ENABLE_SID_FILTERS_TR, "SID filtrelerini em¸le et"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_SID_FILTERS,    N_("Do not emulate SID filters")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SID_FILTERS_DA, "EmulÈr ikke SID-filtre"},
	/* de */ {IDCLS_DISABLE_SID_FILTERS_DE, "SID Filter Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_SID_FILTERS_ES, "No emular filtros SID"},
	/* fr */ {IDCLS_DISABLE_SID_FILTERS_FR, "Ne pas Èmuler les filtres SID"},
	/* hu */ {IDCLS_DISABLE_SID_FILTERS_HU, "Nem emul·lja a SID sz˚rıket"},
	/* it */ {IDCLS_DISABLE_SID_FILTERS_IT, "Non emulare i filtri del SID"},
	/* ko */ {IDCLS_DISABLE_SID_FILTERS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SID_FILTERS_NL, "SID filters niet emuleren"},
	/* pl */ {IDCLS_DISABLE_SID_FILTERS_PL, "Nie emuluj filtrÛw SID"},
	/* ru */ {IDCLS_DISABLE_SID_FILTERS_RU, "Do not emulate SID filters"},
	/* sv */ {IDCLS_DISABLE_SID_FILTERS_SV, "Emulera inte SID-filter"},
	/* tr */ {IDCLS_DISABLE_SID_FILTERS_TR, "SID filtrelerini em¸le etme"},
#endif
	
#ifdef HAVE_RESID
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_RESID_SAMPLING_METHOD,    N_("reSID sampling method (0: fast, 1: interpolating, 2: resampling, 3: fast resampling)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RESID_SAMPLING_METHOD_DA, "reSID-samplingmetode (0: hurtig, 1: interpolerende, 2: omsampling, 3: hurtig omsampling)"},
	/* de */ {IDCLS_RESID_SAMPLING_METHOD_DE, "reSID Sample Methode (0: schnell, 1: interpolierend, 2: resampling, 3: schnelles resampling)"},
	/* es */ {IDCLS_RESID_SAMPLING_METHOD_ES, "reSID metodo sampleado (0: r·pido, 1: interpolacion, 2: resampelado, 3: resampleado r·pido)"},
	/* fr */ {IDCLS_RESID_SAMPLING_METHOD_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_RESID_SAMPLING_METHOD_HU, "reSID mintavÈtelezÈsi mÛd (0: gyors, 1: interpol·lÛ, 2: ˙jramintavÈtelezı, 3: gyors ˙jramintavÈtelezı)"},
	/* it */ {IDCLS_RESID_SAMPLING_METHOD_IT, "Metodo di campionamento del reSID (0: veloce, 1: interpolato, 2: ricampionato 3: ricampionamento veloce)"},
	/* ko */ {IDCLS_RESID_SAMPLING_METHOD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_RESID_SAMPLING_METHOD_NL, "reSID sampling methode (0: snel, 1: interpoleren, 2: resampling, 3: snelle resampling)"},
	/* pl */ {IDCLS_RESID_SAMPLING_METHOD_PL, "Metoda samplowania reSID (0: szybkie, 1: z przeplotem, 2: resamplowanie, 3: szybkie resamplowanie)"},
	/* ru */ {IDCLS_RESID_SAMPLING_METHOD_RU, "reSID sampling method (0: fast, 1: interpolating, 2: resampling, 3: fast resampling)"},
	/* sv */ {IDCLS_RESID_SAMPLING_METHOD_SV, "reSID-samplingsmetod (0: snabb, 1: interpolerande, 2: omsampling, 3: snabb omsampling)"},
	/* tr */ {IDCLS_RESID_SAMPLING_METHOD_TR, "reSID ˆrnekleme metodu (0: h˝zl˝, 1: ara deer bulma, 2: yeniden ˆrnekleme, 3: h˝zl˝ yeniden ˆrnekleme)"},
#endif
	
	/* sid/sid-cmdline-options.c, vsync.c */
	/* en */ {IDCLS_P_PERCENT,    N_("<percent>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_PERCENT_DA, "<procent>"},
	/* de */ {IDCLS_P_PERCENT_DE, "<prozent>"},
	/* es */ {IDCLS_P_PERCENT_ES, "<porcentaje>"},
	/* fr */ {IDCLS_P_PERCENT_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_PERCENT_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_PERCENT_IT, "<percento>"},
	/* ko */ {IDCLS_P_PERCENT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_PERCENT_NL, "<procent>"},
	/* pl */ {IDCLS_P_PERCENT_PL, "<procent>"},
	/* ru */ {IDCLS_P_PERCENT_RU, "<percent>"},
	/* sv */ {IDCLS_P_PERCENT_SV, "<procent>"},
	/* tr */ {IDCLS_P_PERCENT_TR, "<y¸zde>"},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_PASSBAND_PERCENTAGE,    N_("reSID resampling passband in percentage of total bandwidth (0 - 90)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PASSBAND_PERCENTAGE_DA, "PasbÂnd for reSID-resampling i procent af total bÂndbredde (0 - 90)"},
	/* de */ {IDCLS_PASSBAND_PERCENTAGE_DE, "reSID Resampling Passband Prozentwert der gesamte Bandbreite (0 - 90)\n(0 - 90, niedrig ist schneller, hˆher ist besser)"},
	/* es */ {IDCLS_PASSBAND_PERCENTAGE_ES, "reSID resampleado pasabanda en porcentaje del total de ancho de banda (0 - 90)"},
	/* fr */ {IDCLS_PASSBAND_PERCENTAGE_FR, "Bande passante pour le resampling reSID en pourcentage de la bande totale (0 - 90)"},
	/* hu */ {IDCLS_PASSBAND_PERCENTAGE_HU, "reSID ˙jramintavÈtelezÈsi s·vnak a teljes s·vszÈlessÈgre vonatkoztatott ar·nya (0 - 90)"},
	/* it */ {IDCLS_PASSBAND_PERCENTAGE_IT, "Banda passante di ricampionamento del reSID in percentuale di quella totale (0 - 90)"},
	/* ko */ {IDCLS_PASSBAND_PERCENTAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PASSBAND_PERCENTAGE_NL, "reSID resampling passband in percentage van de totale bandbreedte (0 - 90)"},
	/* pl */ {IDCLS_PASSBAND_PERCENTAGE_PL, "Pasmo resamplowania reSID w procentach ca≥kowitej przepustowo∂ci (0 - 90)"},
	/* ru */ {IDCLS_PASSBAND_PERCENTAGE_RU, "reSID resampling passband in percentage of total bandwidth (0 - 90)"},
	/* sv */ {IDCLS_PASSBAND_PERCENTAGE_SV, "Passband fˆr reSID-resampling i procent av total bandbredd (0 - 90)"},
	/* tr */ {IDCLS_PASSBAND_PERCENTAGE_TR, "reSID yeniden ˆrnekleme passband'inin toplam bant geni˛liine y¸zdesel oran˝ (0 - 90)"},
#endif
	
	/* sid/sid-cmdline-options.c, vsync.c */
	/* en */ {IDCLS_RESID_FILTER_BIAS,    N_("reSID filter bias setting, which can be used to adjust DAC bias in millivolts.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RESID_FILTER_BIAS_DA, "reSID filter biasindstilling, som kan bruges til at justere DAC bias i millivolt."},
	/* de */ {IDCLS_RESID_FILTER_BIAS_DE, "reSID Filter Vorspannungseinstellung, welche f¸r die Anpassung der DAC\nVorspannung in Millivolt benutzt werden kann"},
	/* es */ {IDCLS_RESID_FILTER_BIAS_ES, "reSID ajuste filtro bias, que puede ser usado para ajustar DAC bias en milivoltios."},
	/* fr */ {IDCLS_RESID_FILTER_BIAS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_RESID_FILTER_BIAS_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_RESID_FILTER_BIAS_IT, "Impostazione del bias del filtro del reSID, che puÚ essere usato per correggere il bias del DAC in millivolt."},
	/* ko */ {IDCLS_RESID_FILTER_BIAS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_RESID_FILTER_BIAS_NL, "reSID filter bias instelling, dit kan gebruikt worden om de DAC bias in millivolts aan te passen."},
	/* pl */ {IDCLS_RESID_FILTER_BIAS_PL, "Ustawienie filtra reSID, uøywane do regulacji nastawienia DAC w miliwoltach"},
	/* ru */ {IDCLS_RESID_FILTER_BIAS_RU, "reSID filter bias setting, which can be used to adjust DAC bias in millivolts."},
	/* sv */ {IDCLS_RESID_FILTER_BIAS_SV, "Bias-inst‰llning fˆr reSID-filter, vilket kan anv‰ndas fˆr att justera D/A-bias i millivolt."},
	/* tr */ {IDCLS_RESID_FILTER_BIAS_TR, "Millivolt cinsinden DAC meyilini ayarlamak iÁin kullan˝labilen reSID filtresi meyil ayar˝."},
#endif
	
	/* sid/sid-cmdline-options.c */
	/* en */ {IDCLS_RESID_GAIN_PERCENTAGE,    N_("reSID gain in percent (90 - 100)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RESID_GAIN_PERCENTAGE_DA, "Gain for reSID i procent (90 - 100)"},
	/* de */ {IDCLS_RESID_GAIN_PERCENTAGE_DE, "reSID Gain in Prozent (90 - 100)"},
	/* es */ {IDCLS_RESID_GAIN_PERCENTAGE_ES, "reSID ganancia en porcentaje (90-100)"},
	/* fr */ {IDCLS_RESID_GAIN_PERCENTAGE_FR, "Gain reSID en pourcent (90 - 100)"},
	/* hu */ {IDCLS_RESID_GAIN_PERCENTAGE_HU, "reSID sz·zalÈkos erısÌtÈs (90 - 100)"},
	/* it */ {IDCLS_RESID_GAIN_PERCENTAGE_IT, "Guadagno del reSID in percentuale (90 - 100)"},
	/* ko */ {IDCLS_RESID_GAIN_PERCENTAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_RESID_GAIN_PERCENTAGE_NL, "reSID versterking procent (90 - 100)"},
	/* pl */ {IDCLS_RESID_GAIN_PERCENTAGE_PL, "Wzmocnienie reSID-a w procentach (90 - 100)"},
	/* ru */ {IDCLS_RESID_GAIN_PERCENTAGE_RU, "reSID gain in percent (90 - 100)"},
	/* sv */ {IDCLS_RESID_GAIN_PERCENTAGE_SV, "Gain fˆr reSID i procent (90 - 100)"},
	/* tr */ {IDCLS_RESID_GAIN_PERCENTAGE_TR, "reSID gain y¸zdesi (90 - 100)"},
#endif
#endif
	
	/* vdc/vdc-cmdline-options.c, crtc/crtc-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_STRETCH_VERTICAL,    N_("Enable additional vertical stretching.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_STRETCH_VERTICAL_DA, "AktivÈr yderligere vertikal udstrÊkning"},
	/* de */ {IDCLS_ENABLE_STRETCH_VERTICAL_DE, "Aktiviere zus‰tzliche Vertikalstreckung."},
	/* es */ {IDCLS_ENABLE_STRETCH_VERTICAL_ES, "Permitir extensiÛn vertical adicional"},
	/* fr */ {IDCLS_ENABLE_STRETCH_VERTICAL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_STRETCH_VERTICAL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_STRETCH_VERTICAL_IT, "Attiva allungamento verticale aggiuntivo."},
	/* ko */ {IDCLS_ENABLE_STRETCH_VERTICAL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_STRETCH_VERTICAL_NL, "Aktiveer additionele vertikale rekking."},
	/* pl */ {IDCLS_ENABLE_STRETCH_VERTICAL_PL, "W≥±cz dodatkowe rozci±ganie w pionie"},
	/* ru */ {IDCLS_ENABLE_STRETCH_VERTICAL_RU, "Enable additional vertical stretching."},
	/* sv */ {IDCLS_ENABLE_STRETCH_VERTICAL_SV, "Aktivera ytterligare vertikal utdragning."},
	/* tr */ {IDCLS_ENABLE_STRETCH_VERTICAL_TR, "Ek dikey uzatmay˝ aktif et."},
#endif
	
	/* vdc/vdc-cmdline-options.c, crtc/crtc-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_STRETCH_VERTICAL,    N_("Disable additional vertical stretching.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_STRETCH_VERTICAL_DA, "DeaktivÈr yderligere vertikal udstrÊkning"},
	/* de */ {IDCLS_DISABLE_STRETCH_VERTICAL_DE, "Deaktiviere zus‰tzliche Vertikalstreckung."},
	/* es */ {IDCLS_DISABLE_STRETCH_VERTICAL_ES, "Inhabilitar extensiÛn vertical adicional"},
	/* fr */ {IDCLS_DISABLE_STRETCH_VERTICAL_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_STRETCH_VERTICAL_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_STRETCH_VERTICAL_IT, "Disattiva allungamento verticale aggiuntivo."},
	/* ko */ {IDCLS_DISABLE_STRETCH_VERTICAL_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_STRETCH_VERTICAL_NL, "Additionele vertikale rekking afsluiten."},
	/* pl */ {IDCLS_DISABLE_STRETCH_VERTICAL_PL, "Wy≥±cz dodatkowe rozci±ganie w pionie"},
	/* ru */ {IDCLS_DISABLE_STRETCH_VERTICAL_RU, "Disable additional vertical stretching."},
	/* sv */ {IDCLS_DISABLE_STRETCH_VERTICAL_SV, "Inaktivera ytterligare vertikal utdragning."},
	/* tr */ {IDCLS_DISABLE_STRETCH_VERTICAL_TR, "Ek dikey uzatmay˝ pasifle˛tir."},
#endif
	
	/* vdc/vdc-cmdline-options.c */
	/* en */ {IDCLS_SET_VDC_MEMORY_16KB,    N_("Set the VDC memory size to 16KB")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_VDC_MEMORY_16KB_DA, "SÊt VDC-hukommelsesst¯rrelse til 16KB"},
	/* de */ {IDCLS_SET_VDC_MEMORY_16KB_DE, "VDC Speichgrˆﬂe auf 16KB setzen"},
	/* es */ {IDCLS_SET_VDC_MEMORY_16KB_ES, "Seleccionar tamaÒo memoria VDC en 16KB"},
	/* fr */ {IDCLS_SET_VDC_MEMORY_16KB_FR, "RÈgler la taille de la mÈmoire VDC ‡ 16KO"},
	/* hu */ {IDCLS_SET_VDC_MEMORY_16KB_HU, "VDC memÛria mÈret be·llÌt·sa 16KB-ra"},
	/* it */ {IDCLS_SET_VDC_MEMORY_16KB_IT, "Imposta la dimensione della memoria del VDC a 16KB"},
	/* ko */ {IDCLS_SET_VDC_MEMORY_16KB_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_VDC_MEMORY_16KB_NL, "Zet de VDC geheugengrootte als 16KB"},
	/* pl */ {IDCLS_SET_VDC_MEMORY_16KB_PL, "Ustaw rozmiar pamiÍci VDC na 16 KB"},
	/* ru */ {IDCLS_SET_VDC_MEMORY_16KB_RU, "Set the VDC memory size to 16KB"},
	/* sv */ {IDCLS_SET_VDC_MEMORY_16KB_SV, "S‰tt VDC-minnesstorlek till 16KB"},
	/* tr */ {IDCLS_SET_VDC_MEMORY_16KB_TR, "VDC bellek boyutunu 16KB'a ayarla"},
#endif
	
	/* vdc/vdc-cmdline-options.c */
	/* en */ {IDCLS_SET_VDC_MEMORY_64KB,    N_("Set the VDC memory size to 64KB")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_VDC_MEMORY_64KB_DA, "SÊt VDC-hukommelsesst¯rrelse til 64KB"},
	/* de */ {IDCLS_SET_VDC_MEMORY_64KB_DE, "VDC Speichgrˆﬂe auf 64KB setzen"},
	/* es */ {IDCLS_SET_VDC_MEMORY_64KB_ES, "Seleccionar tamaÒo memoria VDC en 64KB"},
	/* fr */ {IDCLS_SET_VDC_MEMORY_64KB_FR, "RÈgler la taille de la mÈmoire VDC ‡ 64KO"},
	/* hu */ {IDCLS_SET_VDC_MEMORY_64KB_HU, "VDC memÛria mÈret be·llÌt·sa 64KB-ra"},
	/* it */ {IDCLS_SET_VDC_MEMORY_64KB_IT, "Imposta la dimensione della memoria del VDC a 64KB"},
	/* ko */ {IDCLS_SET_VDC_MEMORY_64KB_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_VDC_MEMORY_64KB_NL, "Zet de VDC geheugengrootte als 64KB"},
	/* pl */ {IDCLS_SET_VDC_MEMORY_64KB_PL, "Ustaw rozmiar pamiÍci VDC na 64 KB"},
	/* ru */ {IDCLS_SET_VDC_MEMORY_64KB_RU, "Set the VDC memory size to 64KB"},
	/* sv */ {IDCLS_SET_VDC_MEMORY_64KB_SV, "S‰tt VDC-minnesstorlek till 64KB"},
	/* tr */ {IDCLS_SET_VDC_MEMORY_64KB_TR, "VDC bellek boyutunu 64KB'a ayarla"},
#endif
	
	/* vdc/vdc-cmdline-options.c */
	/* en */ {IDCLS_SET_VDC_REVISION,    N_("Set VDC revision (0..2)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_VDC_REVISION_DA, "Angiv VDC-revision (0..2)"},
	/* de */ {IDCLS_SET_VDC_REVISION_DE, "VDC Revision setzen (0..2)"},
	/* es */ {IDCLS_SET_VDC_REVISION_ES, "Poner revisiÛn VDC (0..2)"},
	/* fr */ {IDCLS_SET_VDC_REVISION_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_VDC_REVISION_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_VDC_REVISION_IT, "Imposta la revisione del VDC (0..2)"},
	/* ko */ {IDCLS_SET_VDC_REVISION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_VDC_REVISION_NL, "Zet de VDC revisie (0..2)"},
	/* pl */ {IDCLS_SET_VDC_REVISION_PL, "Okre∂l wersjÍ VDC (0..2)"},
	/* ru */ {IDCLS_SET_VDC_REVISION_RU, "Set VDC revision (0..2)"},
	/* sv */ {IDCLS_SET_VDC_REVISION_SV, "Ange VDC-revision (0..2)"},
	/* tr */ {IDCLS_SET_VDC_REVISION_TR, "VDC revizyonunu ayarla (0..2)"},
#endif
	
	/* vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_P_SPEC,    N_("<spec>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_SPEC_DA, "<spec>"},
	/* de */ {IDCLS_P_SPEC_DE, "<Spec>"},
	/* es */ {IDCLS_P_SPEC_ES, "<especificaciones>"},
	/* fr */ {IDCLS_P_SPEC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_SPEC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_SPEC_IT, "<spec>"},
	/* ko */ {IDCLS_P_SPEC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_SPEC_NL, "<spec>"},
	/* pl */ {IDCLS_P_SPEC_PL, "<spec>"},
	/* ru */ {IDCLS_P_SPEC_RU, "<spec>"},
	/* sv */ {IDCLS_P_SPEC_SV, "<spec>"},
	/* tr */ {IDCLS_P_SPEC_TR, "<˛art>"},
#endif
	
	/* vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_MEMORY_CONFIG,    N_("Specify memory configuration")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_MEMORY_CONFIG_DA, "Angiv hukommelseskonfiguration"},
	/* de */ {IDCLS_SPECIFY_MEMORY_CONFIG_DE, "Speicher Konfiguration definieren"},
	/* es */ {IDCLS_SPECIFY_MEMORY_CONFIG_ES, "Especificar configuraciÛn de memoria"},
	/* fr */ {IDCLS_SPECIFY_MEMORY_CONFIG_FR, "SpÈcifier la configuration de la mÈmoire"},
	/* hu */ {IDCLS_SPECIFY_MEMORY_CONFIG_HU, "Adja meg a memÛria konfigur·ciÛt"},
	/* it */ {IDCLS_SPECIFY_MEMORY_CONFIG_IT, "Specifica la configurazione della memoria"},
	/* ko */ {IDCLS_SPECIFY_MEMORY_CONFIG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_MEMORY_CONFIG_NL, "Geef geheugenconfiguratie"},
	/* pl */ {IDCLS_SPECIFY_MEMORY_CONFIG_PL, "Okre∂l konfiguracjÍ pamiÍci"},
	/* ru */ {IDCLS_SPECIFY_MEMORY_CONFIG_RU, "Specify memory configuration"},
	/* sv */ {IDCLS_SPECIFY_MEMORY_CONFIG_SV, "Ange minneskonfiguration"},
	/* tr */ {IDCLS_SPECIFY_MEMORY_CONFIG_TR, "Bellek konfig¸rasyonunu ayarlay˝n"},
#endif
	
	/* vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_VIC1112_IEEE488,    N_("Enable VIC-1112 IEEE488 interface")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_VIC1112_IEEE488_DA, "AktivÈr VIC-1112-IEEE488-interface"},
	/* de */ {IDCLS_ENABLE_VIC1112_IEEE488_DE, "VIC-1112 IEEE488 Schnittstelle aktivieren"},
	/* es */ {IDCLS_ENABLE_VIC1112_IEEE488_ES, "Permitier interface VIC-1112 IEEE488"},
	/* fr */ {IDCLS_ENABLE_VIC1112_IEEE488_FR, "Activer l'interface VIC-1112 IEEE488"},
	/* hu */ {IDCLS_ENABLE_VIC1112_IEEE488_HU, "VIC-1112 IEEE488 interfÈsz engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_VIC1112_IEEE488_IT, "Attiva interfaccia IEEE488 VIC-1112"},
	/* ko */ {IDCLS_ENABLE_VIC1112_IEEE488_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_VIC1112_IEEE488_NL, "Activeer VIC-1112 IEEE488 interface"},
	/* pl */ {IDCLS_ENABLE_VIC1112_IEEE488_PL, "W≥±cz interfejs IEEE488 VIC-1112"},
	/* ru */ {IDCLS_ENABLE_VIC1112_IEEE488_RU, "Enable VIC-1112 IEEE488 interface"},
	/* sv */ {IDCLS_ENABLE_VIC1112_IEEE488_SV, "Aktivera VIC-1112-IEEE488-gr‰nssnitt"},
	/* tr */ {IDCLS_ENABLE_VIC1112_IEEE488_TR, "VIC-1112 IEEE488 arabirimini aktif et"},
#endif
	
	/* vic20/vic20-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_VIC1112_IEEE488,    N_("Disable VIC-1112 IEEE488 interface")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_VIC1112_IEEE488_DA, "DeaktivÈr VIC-1112-IEEE488-interface"},
	/* de */ {IDCLS_DISABLE_VIC1112_IEEE488_DE, "VIC-1112 IEEE488 Schnittstelle deaktivieren"},
	/* es */ {IDCLS_DISABLE_VIC1112_IEEE488_ES, "Deshabilitar interface VIC-1112 IEEE488"},
	/* fr */ {IDCLS_DISABLE_VIC1112_IEEE488_FR, "DÈsactiver l'interface VIC-1112 IEEE488"},
	/* hu */ {IDCLS_DISABLE_VIC1112_IEEE488_HU, "VIC-1112 IEEE488 interfÈsz tilt·sa"},
	/* it */ {IDCLS_DISABLE_VIC1112_IEEE488_IT, "Disattiva interfaccia IEEE488 VIC-1112"},
	/* ko */ {IDCLS_DISABLE_VIC1112_IEEE488_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_VIC1112_IEEE488_NL, "VIC-1112 IEEE488 interface uitschakelen"},
	/* pl */ {IDCLS_DISABLE_VIC1112_IEEE488_PL, "Wy≥±cz interfejs IEEE488 VIC-1112"},
	/* ru */ {IDCLS_DISABLE_VIC1112_IEEE488_RU, "Disable VIC-1112 IEEE488 interface"},
	/* sv */ {IDCLS_DISABLE_VIC1112_IEEE488_SV, "Inaktivera VIC-1112-IEEE488-gr‰nssnitt"},
	/* tr */ {IDCLS_DISABLE_VIC1112_IEEE488_TR, "VIC-1112 IEEE488 arabirimini pasifle˛tir"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME,    N_("Specify 4/8/16K extension ROM name at $2000")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_DA, "Angiv navn for 4/8/16k-udviddelses-ROM pÂ $2000"},
	/* de */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_DE, "4/8/16K Erweiterungs ROM Datei Name f¸r $2000 definieren"},
	/* es */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_ES, "Especificar nombre ROM extendida de 4/8/16KB en $2000"},
	/* fr */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_FR, "SpÈcifier le nom de l'extension ROM 4/8/16K ‡ $2000"},
	/* hu */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_HU, "Adja meg a $2000 cÌm˚ 4/8/16K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_IT, "Specifica il nome della ROM di estensione di 4/8/16K a $2000"},
	/* ko */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_NL, "Geef de naam van het bestand voor de 4/8/16K ROM op $2000"},
	/* pl */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_PL, "Okre∂l nazwÍ ROM rozszerzenia 4/8/16K w $2000"},
	/* ru */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_RU, "Specify 4/8/16K extension ROM name at $2000"},
	/* sv */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_SV, "Ange namn fˆr 4/8/16K-utˆknings-ROM pÂ $2000"},
	/* tr */ {IDCLS_SPECIFY_EXT_ROM_2000_NAME_TR, "$2000 adresindeki 4/8/16K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME,    N_("Specify 4/8/16K extension ROM name at $4000")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_DA, "Angiv navn for 4/8/16k-udviddelses-ROM pÂ $4000"},
	/* de */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_DE, "4/8/16K Erweiterungs ROM Datei Name f¸r $4000 definieren"},
	/* es */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_ES, "Especificar nombre ROM extendida de 4/8/16KB en $4000"},
	/* fr */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_FR, "SpÈcifier le nom de l'extension ROM 4/8/16K ‡ $4000"},
	/* hu */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_HU, "Adja meg a $4000 cÌm˚ 4/8/16K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_IT, "Specifica il nome della ROM di estensione di 4/8/16K a $4000"},
	/* ko */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_NL, "Geef de naam van het bestand voor de 4/8/16K ROM op $4000"},
	/* pl */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_PL, "Okre∂l nazwÍ ROM rozszerzenia 4/8/16K w $4000"},
	/* ru */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_RU, "Specify 4/8/16K extension ROM name at $4000"},
	/* sv */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_SV, "Ange namn fˆr 4/8/16K-utˆknings-ROM pÂ $4000"},
	/* tr */ {IDCLS_SPECIFY_EXT_ROM_4000_NAME_TR, "$4000 adresindeki 4/8/16K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME,    N_("Specify 4/8/16K extension ROM name at $6000")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_DA, "Angiv navn for 4/8/16k-udviddelses-ROM pÂ $6000"},
	/* de */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_DE, "4/8/16K Erweiterungs ROM Datei Name f¸r $6000 definieren"},
	/* es */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_ES, "Especificar nombre ROM extendida de 4/8/16KB en $6000"},
	/* fr */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_FR, "SpÈcifier le nom de l'extension ROM 4/8/16K ‡ $6000"},
	/* hu */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_HU, "Adja meg a $6000 cÌm˚ 4/8/16K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_IT, "Specifica il nome della ROM di estensione di 4/8/16K a $6000"},
	/* ko */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_NL, "Geef de naam van het bestand voor de 4/8/16K ROM op $6000"},
	/* pl */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_PL, "Okre∂l nazwÍ ROM rozszerzenia 4/8/16K w $6000"},
	/* ru */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_RU, "Specify 4/8/16K extension ROM name at $6000"},
	/* sv */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_SV, "Ange namn fˆr 4/8/16K-utˆknings-ROM pÂ $6000"},
	/* tr */ {IDCLS_SPECIFY_EXT_ROM_6000_NAME_TR, "$6000 adresindeki 4/8/16K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME,    N_("Specify 4/8K extension ROM name at $A000")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_DA, "Angiv navn for 4/8k-udviddelses-ROM pÂ $A000"},
	/* de */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_DE, "4/8/16K Erweiterungs ROM Datei Name f¸r $A000 definieren"},
	/* es */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_ES, "Especificar nombre ROM extendida de 4/8KB en $A000"},
	/* fr */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_FR, "SpÈcifier le nom de l'extension ROM 4/8K ‡ $A000"},
	/* hu */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_HU, "Adja meg a $A000 cÌm˚ 4/8K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_IT, "Specifica il nome della ROM di estensione di 4/8K a $A000"},
	/* ko */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_NL, "Geef de naam van het bestand voor de 4/8K ROM op $A000"},
	/* pl */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_PL, "Okre∂l nazwÍ ROM rozszerzenia 4/8/16K w $A000"},
	/* ru */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_RU, "Specify 4/8K extension ROM name at $A000"},
	/* sv */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_SV, "Ange namn fˆr 4/8K-utˆknings-ROM pÂ $A000"},
	/* tr */ {IDCLS_SPECIFY_EXT_ROM_A000_NAME_TR, "$A000 adresindeki 4/8K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME,    N_("Specify 4K extension ROM name at $B000")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_DA, "Angiv navn for 4k-udviddelses-ROM pÂ $B000"},
	/* de */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_DE, "4/8/16K Erweiterungs ROM Datei Name f¸r $B000 definieren"},
	/* es */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_ES, "Especificar nombre ROM extendida de 4KB en $B000"},
	/* fr */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_FR, "SpÈcifier le nom de l'extension ROM 4K ‡ $B000"},
	/* hu */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_HU, "Adja meg a $B000 cÌm˚ 4K ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_IT, "Specifica il nome della ROM di estensione di 4 a $B000"},
	/* ko */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_NL, "Geef de naam van het bestand voor de 4K ROM op $B000"},
	/* pl */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_PL, "Okre∂l nazwÍ ROM rozszerzenia 4/8/16K w $B000"},
	/* ru */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_RU, "Specify 4K extension ROM name at $B000"},
	/* sv */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_SV, "Ange namn fˆr 4K-utˆknings-ROM pÂ $B000"},
	/* tr */ {IDCLS_SPECIFY_EXT_ROM_B000_NAME_TR, "$B000 adresindeki 4K uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_GENERIC_ROM_NAME,    N_("Specify generic extension ROM name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_DA, "Angiv navn pÂ standard-udviddelses-ROM"},
	/* de */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_DE, "Generisches Erweiterungs ROM definieren"},
	/* es */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_ES, "Especificar nombre ROM extendida generica"},
	/* fr */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_HU, "Adja meg az ·ltal·nos ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_IT, "Specifica il nome dell'estensione ROM generica"},
	/* ko */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_NL, "Geef de naam van het bestand voor de algemene ROM"},
	/* pl */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_PL, "Okre∂l nazwÍ typowego ROM-u rozszerzeÒ"},
	/* ru */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_RU, "Specify generic extension ROM name"},
	/* sv */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_SV, "Ange namn pÂ generiskt utˆknings-ROM"},
	/* tr */ {IDCLS_SPECIFY_GENERIC_ROM_NAME_TR, "Jenerik uzant˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME,    N_("Specify Mega-Cart extension ROM name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_DA, "Angiv navn pÂ MegaCart-udviddelses-ROM"},
	/* de */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_DE, "Mega-Cart Erweiterungs ROM definieren"},
	/* es */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_ES, "Especificar nombre ROM extendida Mega Cart"},
	/* fr */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_HU, "Adja meg a Mega-Cart ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_IT, "Specifica il nome dell'estensione ROM Mega-Cart"},
	/* ko */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_NL, "Geef de naam van het bestand voor de Mega-Cart ROM"},
	/* pl */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_PL, "Okre∂l nazwÍ ROM rozszerzenia Mega-Cart"},
	/* ru */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_RU, "Specify Mega-Cart extension ROM name"},
	/* sv */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_SV, "Ange namn pÂ Mega-Cart-utˆknings-ROM"},
	/* tr */ {IDCLS_SPECIFY_MEGA_CART_ROM_NAME_TR, "Mega-Cart uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME,    N_("Specify Final Expansion extension ROM name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_DA, "Angiv navn pÂ Final Expansion udviddelses-ROM"},
	/* de */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_DE, "Name f¸r Final Expansion Erweiterungs ROM definieren"},
	/* es */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_ES, "Especificar nombre ROM extendida Final Expansion"},
	/* fr */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_HU, "Adja meg a Final Expansion ROM kiterjesztÈs nevÈt"},
	/* it */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_IT, "Specifica il nome dell'estensione ROM Final Expansion"},
	/* ko */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_NL, "Geef de naam van het bestand voor de Final Expansion ROM"},
	/* pl */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_PL, "Okre∂l nazwÍ rozszerzenia ROM Final Expansion"},
	/* ru */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_RU, "Specify Final Expansion extension ROM name"},
	/* sv */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_SV, "Ange namn pÂ Final Expansion utˆknings-ROM"},
	/* tr */ {IDCLS_SPECIFY_FINAL_EXPANSION_ROM_NAME_TR, "Final Expansion uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/vic20cart.c */
	/* en */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME,    N_("Specify Vic Flash Plugin extension ROM name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_DA, "Angiv navn pÂ Vic Flash Plugin udviddelses-ROM"},
	/* de */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_DE, "Name f¸r Vic Flash Plugin Erweiterungs ROM definieren"},
	/* es */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_ES, "Especificar nombre ROM extendidad Vic Flash Plugin"},
	/* fr */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_IT, "Specifica il nome dell'estensione ROM Vic Flash Plugin"},
	/* ko */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_NL, "Geef de naam van het bestand voor de Vic Flash Plugin ROM"},
	/* pl */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_PL, "Okre∂l nazwÍ rozszerzenia ROM Vic Flash Plugin"},
	/* ru */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_RU, "Specify Vic Flash Plugin extension ROM name"},
	/* sv */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_SV, "Ange namn pÂ Vic Flash-insticksmodulutˆknings-ROM"},
	/* tr */ {IDCLS_SPECIFY_VIC_FP_ROM_NAME_TR, "Vic Flash Plugin uzant˝s˝ ROM ismini belirt"},
#endif
	
	/* vic20/cart/finalexpansion.c */
	/* en */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK,    N_("Enable Final Expansion write back to ROM file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_DA, "AktivÈr Final Expansion tilbageskrivning til ROM-fil"},
	/* de */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_DE, "Final Expansion ROM Schreibzugriff aktivieren"},
	/* es */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_ES, "Permitir grabaciÛn en fichero ROM Final Expansion"},
	/* fr */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_HU, "Final Expansion ROM f·jlba visszaÌr·s engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_IT, "Attiva write back per Final Expansion su file ROM"},
	/* ko */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_NL, "Activeer terug schrijven naar ROM bestand voor Final Expansion"},
	/* pl */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_PL, "W≥±cz zapis do pliku ROM Final Expansion"},
	/* ru */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_RU, "Enable Final Expansion write back to ROM file"},
	/* sv */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_SV, "Aktivera Âterskrivning till ROM-fil fˆr Final Expansion"},
	/* tr */ {IDCLS_ENABLE_FINALEXPANSION_WRITEBACK_TR, "Final Expansion ROM dosyas˝na geri yazmay˝ aktif et"},
#endif
	
	/* vic20/cart/finalexpansion.c */
	/* en */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK,    N_("Disable Final Expansion write back to ROM file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_DA, "DeaktivÈr Final Expansion tilbageskrivning til ROM-fil"},
	/* de */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_DE, "Final Expansion ROM Schreibzugriff deaktivieren"},
	/* es */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_ES, "Deshabilitar grabaciÛn en fichero ROM Final Expansion"},
	/* fr */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_HU, "Final Expansion ROM f·jlba visszaÌr·s tilt·sa"},
	/* it */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_IT, "Disattiva write back per Final Expansion su file ROM"},
	/* ko */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_NL, "Terug schrijven naar ROM bestand voor Final Expansion uitschakelen"},
	/* pl */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_PL, "Wy≥±cz zapis do pliku ROM Final Expansion"},
	/* ru */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_RU, "Disable Final Expansion write back to ROM file"},
	/* sv */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_SV, "Inaktivera Âterskrivning till ROM-fil fˆr Final Expansion"},
	/* tr */ {IDCLS_DISABLE_FINALEXPANSION_WRITEBACK_TR, "Final Expansion ROM dosyas˝na geri yazmay˝ pasifle˛tir"},
#endif
	
	/* vic20/cart/megacart.c */
	/* en */ {IDCLS_SET_MEGACART_NVRAM_NAME,    N_("Set Mega-Cart NvRAM filename")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_MEGACART_NVRAM_NAME_DA, "VÊlg Mega-Cart NvRAM filnavn"},
	/* de */ {IDCLS_SET_MEGACART_NVRAM_NAME_DE, "Mega-Cart NvRAM Imagename definieren"},
	/* es */ {IDCLS_SET_MEGACART_NVRAM_NAME_ES, "Seleccionar nombre fichero  Mega-Cart NvRAM"},
	/* fr */ {IDCLS_SET_MEGACART_NVRAM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_MEGACART_NVRAM_NAME_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_MEGACART_NVRAM_NAME_IT, "Imposta nome file NvRAM Mega-Cart"},
	/* ko */ {IDCLS_SET_MEGACART_NVRAM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_MEGACART_NVRAM_NAME_NL, "Zet Mega-Cart NvRAM bestandsnaam"},
	/* pl */ {IDCLS_SET_MEGACART_NVRAM_NAME_PL, "Okre∂l nazwÍ pliku NvRAM Mega-Cart"},
	/* ru */ {IDCLS_SET_MEGACART_NVRAM_NAME_RU, "Set Mega-Cart NvRAM filename"},
	/* sv */ {IDCLS_SET_MEGACART_NVRAM_NAME_SV, "V‰lj  Mega-Cart NvRAM-filnamn"},
	/* tr */ {IDCLS_SET_MEGACART_NVRAM_NAME_TR, "Mega-Cart NvRAM dosyaismini gir"},
#endif
	
	/* vic20/cart/megacart.c */
	/* en */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE,    N_("Enable Mega-Cart NvRAM writeback")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_DA, "AktivÈr Mega-Cart NvRAM tilbageskrivning"},
	/* de */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_DE, "Mega-Cart NvRAM R¸ckschreiben aktivieren"},
	/* es */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_ES, "Permitir respuesta Mega-Cart NvRAM"},
	/* fr */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_IT, "Write back NvRAM Mega-Cart"},
	/* ko */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_NL, "Activeer Mega-Cart NvRAM terug schrijven"},
	/* pl */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_PL, "W≥±cz zapis do NvRAM Mega-Cart"},
	/* ru */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_RU, "Enable Mega-Cart NvRAM writeback"},
	/* sv */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_SV, "Aktivera Mega-Cart NvRAM-Âterskrivning"},
	/* tr */ {IDCLS_ENABLE_MEGACART_NVRAM_WRITE_TR, "Mega-Cart NvRAM geri yazmay˝ aktif et"},
#endif
	
	/* vic20/cart/megacart.c */
	/* en */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE,    N_("Disable Mega-Cart NvRAM writeback")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_DA, "DeaktivÈr Mega-Cart NvRAM tilbageskrivning"},
	/* de */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_DE, "Mega-Cart NvRAM R¸ckschreiben deaktivieren"},
	/* es */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_ES, "Deshabilitar grabaciÛn en Mega-Cart NvRAM"},
	/* fr */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_IT, "Disattiva write back su NvRAM Mega-Cart"},
	/* ko */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_NL, "Mega-Cart NvRAM terug schrijven uitschakelen"},
	/* pl */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_PL, "Wy≥±cz zapis do NvRAM Mega-Cart"},
	/* ru */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_RU, "Disable Mega-Cart NvRAM writeback"},
	/* sv */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_SV, "Inaktivera Mega-Cart NvRAM-Âterskrivning"},
	/* tr */ {IDCLS_DISABLE_MEGACART_NVRAM_WRITE_TR, "Mega-Cart NvRAM geri yazmay˝ pasifle˛tir"},
#endif
	
	/* vic20/cart/vic-fp.c */
	/* en */ {IDCLS_ENABLE_VICFP_ROM_WRITE,    N_("Enable Vic Flash Plugin write back to ROM file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_VICFP_ROM_WRITE_DA, "AktivÈr Vic Flash Plugin tilbageskrivning til ROM-fil"},
	/* de */ {IDCLS_ENABLE_VICFP_ROM_WRITE_DE, "Vic Flash Plugin R¸ckschreiben auf ROM Datei aktivieren"},
	/* es */ {IDCLS_ENABLE_VICFP_ROM_WRITE_ES, "Permitir grabacion en ROM Vic Flash Plugin"},
	/* fr */ {IDCLS_ENABLE_VICFP_ROM_WRITE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_VICFP_ROM_WRITE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_VICFP_ROM_WRITE_IT, "Attiva write back per Vic Flash Plugin su file ROM"},
	/* ko */ {IDCLS_ENABLE_VICFP_ROM_WRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_VICFP_ROM_WRITE_NL, "Activeer terug schrijven naar ROM bestand voor Vic Flash Plugin"},
	/* pl */ {IDCLS_ENABLE_VICFP_ROM_WRITE_PL, "W≥±cz zapis do pliku ROM Vic Flash Plugin"},
	/* ru */ {IDCLS_ENABLE_VICFP_ROM_WRITE_RU, "Enable Vic Flash Plugin write back to ROM file"},
	/* sv */ {IDCLS_ENABLE_VICFP_ROM_WRITE_SV, "Aktivera Âterskrivning till ROM-fil fˆr Vic Flash-insticksmodul"},
	/* tr */ {IDCLS_ENABLE_VICFP_ROM_WRITE_TR, "Flash Plugin ROM dosyas˝na geri yazmay˝ aktif et"},
#endif
	
	/* vic20/cart/vic-fp.c */
	/* en */ {IDCLS_DISABLE_VICFP_ROM_WRITE,    N_("Disable Vic Flash Plugin write back to ROM file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_VICFP_ROM_WRITE_DA, "DeaktivÈr Vic Flash Plugin tilbageskrivning til ROM-fil"},
	/* de */ {IDCLS_DISABLE_VICFP_ROM_WRITE_DE, "Vic Flash Plugin R¸ckschreiben auf ROM Datei deaktivieren"},
	/* es */ {IDCLS_DISABLE_VICFP_ROM_WRITE_ES, "Deshabilitar grabacion en ROM Vic Flash Plugin"},
	/* fr */ {IDCLS_DISABLE_VICFP_ROM_WRITE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_VICFP_ROM_WRITE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_VICFP_ROM_WRITE_IT, "Disattiva write back per Vic Flash Plugin su file ROM"},
	/* ko */ {IDCLS_DISABLE_VICFP_ROM_WRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_VICFP_ROM_WRITE_NL, "Terug schrijven naar ROM bestand voor Vic Flash Plugin uitschakelen"},
	/* pl */ {IDCLS_DISABLE_VICFP_ROM_WRITE_PL, "Wy≥±cz zapis do pliku ROM Vic Flash Plugin"},
	/* ru */ {IDCLS_DISABLE_VICFP_ROM_WRITE_RU, "Disable Vic Flash Plugin write back to ROM file"},
	/* sv */ {IDCLS_DISABLE_VICFP_ROM_WRITE_SV, "Inaktivera Âterskrivning till ROM-fil fˆr Vic Flash-insticksmodul"},
	/* tr */ {IDCLS_DISABLE_VICFP_ROM_WRITE_TR, "Flash Plugin ROM dosyas˝na geri yazmay˝ pasifle˛tir"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_SET_BORDER_MODE,    N_("Set VIC-II border display mode (0: normal, 1: full, 2: debug)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_BORDER_MODE_DA, "VÊlg VIC-II-rammevisningstilstand (0: normal, 1: fuld, 2: fejls¯gning)"},
	/* de */ {IDCLS_SET_BORDER_MODE_DE, "VIC-II Rahmen Darstellung Modus (0: normal, 1: full, 2: debug)"},
	/* es */ {IDCLS_SET_BORDER_MODE_ES, "Seleccionar VIC-II tipo de borde (0: normal, 1: completo, 2: depuraciÛn)"},
	/* fr */ {IDCLS_SET_BORDER_MODE_FR, "RÈgler le mode de bordure VIC-II (0: normal, 1: complet, 2: debug)"},
	/* hu */ {IDCLS_SET_BORDER_MODE_HU, "VIC-II keret megjelenÌtÈsi mÛd (0: norm·l, 1: teljes, 2: hibakeresÈs)"},
	/* it */ {IDCLS_SET_BORDER_MODE_IT, "Imposta la modalit‡ di visualizzazione del bordo del VIC-II (0: normale, 1: intero, 2: debug)"},
	/* ko */ {IDCLS_SET_BORDER_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_BORDER_MODE_NL, "Zet VIC-II border weergavemodus (0: normaal, 1: volledig, 2: debug)"},
	/* pl */ {IDCLS_SET_BORDER_MODE_PL, "Okre∂l tryb wy∂wietlania ramki VIC-II (0: zwyk≥a, 1: pe≥na, 2: debug)"},
	/* ru */ {IDCLS_SET_BORDER_MODE_RU, "Set VIC-II border display mode (0: normal, 1: full, 2: debug)"},
	/* sv */ {IDCLS_SET_BORDER_MODE_SV, "V‰lj VIC II-ramvisningsl‰ge (0: normal, 1: full, 2: felsˆkning)"},
	/* tr */ {IDCLS_SET_BORDER_MODE_TR, "VIC-II ÁerÁeve gˆsterim modunu ayarlay˝n (0: normal, 1: tam, 2: hata ay˝klama)"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_SPRITE_BACKGROUND,    N_("Enable sprite-background collision registers")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SPRITE_BACKGROUND_DA, "AktivÈr sprite-til-baggrunds-kollisionsregistre"},
	/* de */ {IDCLS_ENABLE_SPRITE_BACKGROUND_DE, "Sprite-Hintergrund Kollisionen aktivieren"},
	/* es */ {IDCLS_ENABLE_SPRITE_BACKGROUND_ES, "Habilitar registros colisiÛn sprite-fondo"},
	/* fr */ {IDCLS_ENABLE_SPRITE_BACKGROUND_FR, "Activer les registres de collisions de sprite avec arriËre-plan"},
	/* hu */ {IDCLS_ENABLE_SPRITE_BACKGROUND_HU, "Sprite-h·ttÈr ¸tkˆzÈsi regiszterek engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_SPRITE_BACKGROUND_IT, "Attiva registri di collisione sprite-sfondo"},
	/* ko */ {IDCLS_ENABLE_SPRITE_BACKGROUND_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SPRITE_BACKGROUND_NL, "Activeer sprite-achtergrond botsing registers"},
	/* pl */ {IDCLS_ENABLE_SPRITE_BACKGROUND_PL, "W≥±cz rejestry kolizji duszkÛw z t≥em"},
	/* ru */ {IDCLS_ENABLE_SPRITE_BACKGROUND_RU, "Enable sprite-background collision registers"},
	/* sv */ {IDCLS_ENABLE_SPRITE_BACKGROUND_SV, "Aktivera sprite-till-bakgrund-kollisionsregister"},
	/* tr */ {IDCLS_ENABLE_SPRITE_BACKGROUND_TR, "Yarat˝k-arka plan Áarp˝˛ma registerlar˝n˝ aktif et"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_SPRITE_BACKGROUND,    N_("Disable sprite-background collision registers")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SPRITE_BACKGROUND_DA, "DeaktivÈr sprite-til-baggrunds-kollisionsregistre"},
	/* de */ {IDCLS_DISABLE_SPRITE_BACKGROUND_DE, "Sprite-Hintergrund Kollisionen deaktivieren"},
	/* es */ {IDCLS_DISABLE_SPRITE_BACKGROUND_ES, "Deshabilitar registros colisiÛn sprite-fondo"},
	/* fr */ {IDCLS_DISABLE_SPRITE_BACKGROUND_FR, "DÈsactiver les registres de collisions de sprite avec arriËre-plan"},
	/* hu */ {IDCLS_DISABLE_SPRITE_BACKGROUND_HU, "Sprite-h·ttÈr ¸tkˆzÈsi regiszterek tilt·sa"},
	/* it */ {IDCLS_DISABLE_SPRITE_BACKGROUND_IT, "Disattiva registri di collisione sprite-sfondo"},
	/* ko */ {IDCLS_DISABLE_SPRITE_BACKGROUND_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SPRITE_BACKGROUND_NL, "Sprite-achtergrond botsing registers uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SPRITE_BACKGROUND_PL, "Wy≥±cz rejestry kolizji duszkÛw z t≥em"},
	/* ru */ {IDCLS_DISABLE_SPRITE_BACKGROUND_RU, "Disable sprite-background collision registers"},
	/* sv */ {IDCLS_DISABLE_SPRITE_BACKGROUND_SV, "Inaktivera sprite-till-bakgrund-kollisionsregister"},
	/* tr */ {IDCLS_DISABLE_SPRITE_BACKGROUND_TR, "Yarat˝k-arka plan Áarp˝˛ma registerlar˝n˝ pasifle˛tir"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_SPRITE_SPRITE,    N_("Enable sprite-sprite collision registers")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SPRITE_SPRITE_DA, "AktivÈr sprite-til-sprite-kollisionsregistre"},
	/* de */ {IDCLS_ENABLE_SPRITE_SPRITE_DE, "Sprite-Sprite Kollisionen aktivieren"},
	/* es */ {IDCLS_ENABLE_SPRITE_SPRITE_ES, "Habilitar registros colisiÛn sprite-sprite"},
	/* fr */ {IDCLS_ENABLE_SPRITE_SPRITE_FR, "Activer les registres de collisions de sprite avec sprite"},
	/* hu */ {IDCLS_ENABLE_SPRITE_SPRITE_HU, "Sprite-sprite ¸tkˆzÈsi regiszterek engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_SPRITE_SPRITE_IT, "Attiva registri di collisione sprite-sprite"},
	/* ko */ {IDCLS_ENABLE_SPRITE_SPRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SPRITE_SPRITE_NL, "Activeer sprite-sprite botsing registers"},
	/* pl */ {IDCLS_ENABLE_SPRITE_SPRITE_PL, "W≥±cz rejestry kolizji duszkÛw"},
	/* ru */ {IDCLS_ENABLE_SPRITE_SPRITE_RU, "Enable sprite-sprite collision registers"},
	/* sv */ {IDCLS_ENABLE_SPRITE_SPRITE_SV, "Aktivera sprite-till-sprite-kollisionsregister"},
	/* tr */ {IDCLS_ENABLE_SPRITE_SPRITE_TR, "Yarat˝k-yarat˝k Áarp˝˛ma registerlar˝n˝ aktif et"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_SPRITE_SPRITE,    N_("Disable sprite-sprite collision registers")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SPRITE_SPRITE_DA, "DeaktivÈr sprite-til-sprite-kollisionsregistre"},
	/* de */ {IDCLS_DISABLE_SPRITE_SPRITE_DE, "Sprite-Sprite Kollisionen deaktivieren"},
	/* es */ {IDCLS_DISABLE_SPRITE_SPRITE_ES, "Deshabilitar registros colisiÛn sprite-sprite"},
	/* fr */ {IDCLS_DISABLE_SPRITE_SPRITE_FR, "DÈsactiver les registres de collisions de sprite avec sprite"},
	/* hu */ {IDCLS_DISABLE_SPRITE_SPRITE_HU, "Sprite-sprite ¸tkˆzÈsi regiszterek tilt·sa"},
	/* it */ {IDCLS_DISABLE_SPRITE_SPRITE_IT, "Disattiva registri di collisione sprite-sprite"},
	/* ko */ {IDCLS_DISABLE_SPRITE_SPRITE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SPRITE_SPRITE_NL, "Sprite-sprite botsing registers uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SPRITE_SPRITE_PL, "Wy≥±cz rejestry kolizji duszkÛw"},
	/* ru */ {IDCLS_DISABLE_SPRITE_SPRITE_RU, "Disable sprite-sprite collision registers"},
	/* sv */ {IDCLS_DISABLE_SPRITE_SPRITE_SV, "Inaktivera sprite-till-sprite-kollisionsregister"},
	/* tr */ {IDCLS_DISABLE_SPRITE_SPRITE_TR, "Yarat˝k-yarat˝k Áarp˝˛ma registerlar˝n˝ pasifle˛tir"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_USE_NEW_LUMINANCES,    N_("Use new luminances")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_NEW_LUMINANCES_DA, "Brug nye lysstyrker"},
	/* de */ {IDCLS_USE_NEW_LUMINANCES_DE, "Neue Helligkeitsemulation"},
	/* es */ {IDCLS_USE_NEW_LUMINANCES_ES, "Usar luminancias nuevas"},
	/* fr */ {IDCLS_USE_NEW_LUMINANCES_FR, "Utiliser les nouvelles luminescences"},
	/* hu */ {IDCLS_USE_NEW_LUMINANCES_HU, "Az ˙j fÈnyerıket haszn·lja"},
	/* it */ {IDCLS_USE_NEW_LUMINANCES_IT, "Usa nuove luminanze"},
	/* ko */ {IDCLS_USE_NEW_LUMINANCES_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_NEW_LUMINANCES_NL, "Gebruik nieuwe kleuren"},
	/* pl */ {IDCLS_USE_NEW_LUMINANCES_PL, "Uøyj nowego typu jaskrawo∂ci"},
	/* ru */ {IDCLS_USE_NEW_LUMINANCES_RU, "Use new luminances"},
	/* sv */ {IDCLS_USE_NEW_LUMINANCES_SV, "Anv‰nd nya ljusstyrkor"},
	/* tr */ {IDCLS_USE_NEW_LUMINANCES_TR, "Yeni parlakl˝klar˝ kullan"},
#endif
	
	/* vicii/vicii-cmdline-options.c */
	/* en */ {IDCLS_USE_OLD_LUMINANCES,    N_("Use old luminances")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_OLD_LUMINANCES_DA, "Brug gamle lysstyrker"},
	/* de */ {IDCLS_USE_OLD_LUMINANCES_DE, "Alte Helligkeitsemulation"},
	/* es */ {IDCLS_USE_OLD_LUMINANCES_ES, "Usar luminancias antiguas"},
	/* fr */ {IDCLS_USE_OLD_LUMINANCES_FR, "Utiliser les anciennes luminescences"},
	/* hu */ {IDCLS_USE_OLD_LUMINANCES_HU, "A rÈgi fÈnyerıket haszn·lja"},
	/* it */ {IDCLS_USE_OLD_LUMINANCES_IT, "Usa vecchie luminanze"},
	/* ko */ {IDCLS_USE_OLD_LUMINANCES_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_OLD_LUMINANCES_NL, "Gebruik oude kleuren"},
	/* pl */ {IDCLS_USE_OLD_LUMINANCES_PL, "Uøyj starego typu jaskrawo∂ci"},
	/* ru */ {IDCLS_USE_OLD_LUMINANCES_RU, "Use old luminances"},
	/* sv */ {IDCLS_USE_OLD_LUMINANCES_SV, "Anv‰nd gamla ljusstyrkor"},
	/* tr */ {IDCLS_USE_OLD_LUMINANCES_TR, "Eski parlakl˝klar˝ kullan"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DOUBLE_SIZE,    N_("Enable double size")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DOUBLE_SIZE_DA, "AktivÈr dobbelt st¯rrelse"},
	/* de */ {IDCLS_ENABLE_DOUBLE_SIZE_DE, "Doppelte Grˆﬂe aktivieren"},
	/* es */ {IDCLS_ENABLE_DOUBLE_SIZE_ES, "Permitir tamaÒo doble"},
	/* fr */ {IDCLS_ENABLE_DOUBLE_SIZE_FR, "Taille double"},
	/* hu */ {IDCLS_ENABLE_DOUBLE_SIZE_HU, "Dupla mÈret engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_DOUBLE_SIZE_IT, "Attiva dimensione doppia"},
	/* ko */ {IDCLS_ENABLE_DOUBLE_SIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DOUBLE_SIZE_NL, "Activeer dubbele grootte"},
	/* pl */ {IDCLS_ENABLE_DOUBLE_SIZE_PL, "W≥±cz podwÛjny rozmiar"},
	/* ru */ {IDCLS_ENABLE_DOUBLE_SIZE_RU, "Enable double size"},
	/* sv */ {IDCLS_ENABLE_DOUBLE_SIZE_SV, "Aktivera dubbel storlek"},
	/* tr */ {IDCLS_ENABLE_DOUBLE_SIZE_TR, "«ift boyutu aktif et"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DOUBLE_SIZE,    N_("Disable double size")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DOUBLE_SIZE_DA, "DeaktivÈr dobbelt st¯rrelse"},
	/* de */ {IDCLS_DISABLE_DOUBLE_SIZE_DE, "Doppelte Grˆﬂe deaktivieren"},
	/* es */ {IDCLS_DISABLE_DOUBLE_SIZE_ES, "Deshabilitar tamaÒo doble"},
	/* fr */ {IDCLS_DISABLE_DOUBLE_SIZE_FR, "Taille normale"},
	/* hu */ {IDCLS_DISABLE_DOUBLE_SIZE_HU, "Dupla mÈret tilt·sa"},
	/* it */ {IDCLS_DISABLE_DOUBLE_SIZE_IT, "Disattiva dimensione doppia"},
	/* ko */ {IDCLS_DISABLE_DOUBLE_SIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DOUBLE_SIZE_NL, "Dubbele grootte uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DOUBLE_SIZE_PL, "Wy≥±cz podwÛjny rozmiar"},
	/* ru */ {IDCLS_DISABLE_DOUBLE_SIZE_RU, "Disable double size"},
	/* sv */ {IDCLS_DISABLE_DOUBLE_SIZE_SV, "Inaktivera dubbel storlek"},
	/* tr */ {IDCLS_DISABLE_DOUBLE_SIZE_TR, "«ift boyutu pasifle˛tir"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_DOUBLE_SCAN,    N_("Enable double scan")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DOUBLE_SCAN_DA, "AktivÈr dobbelt-skan"},
	/* de */ {IDCLS_ENABLE_DOUBLE_SCAN_DE, "Doppelt Scan aktivieren"},
	/* es */ {IDCLS_ENABLE_DOUBLE_SCAN_ES, "Permitir doble escaneado"},
	/* fr */ {IDCLS_ENABLE_DOUBLE_SCAN_FR, "Activer le mode double scan"},
	/* hu */ {IDCLS_ENABLE_DOUBLE_SCAN_HU, "Dupla p·szt·z·s engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_DOUBLE_SCAN_IT, "Attiva scansione doppia"},
	/* ko */ {IDCLS_ENABLE_DOUBLE_SCAN_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DOUBLE_SCAN_NL, "Activeer dubbele scan"},
	/* pl */ {IDCLS_ENABLE_DOUBLE_SCAN_PL, "W≥±cz podwÛjne skanowanie"},
	/* ru */ {IDCLS_ENABLE_DOUBLE_SCAN_RU, "Enable double scan"},
	/* sv */ {IDCLS_ENABLE_DOUBLE_SCAN_SV, "Aktivera dubbelskanning"},
	/* tr */ {IDCLS_ENABLE_DOUBLE_SCAN_TR, "«ift taramay˝ aktif et"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_DOUBLE_SCAN,    N_("Disable double scan")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DOUBLE_SCAN_DA, "DeaktivÈr dobbelt-skan"},
	/* de */ {IDCLS_DISABLE_DOUBLE_SCAN_DE, "Doppelt Scan deaktivieren"},
	/* es */ {IDCLS_DISABLE_DOUBLE_SCAN_ES, "Deshabilitar doble escaneado"},
	/* fr */ {IDCLS_DISABLE_DOUBLE_SCAN_FR, "DÈsactiver le mode double scan"},
	/* hu */ {IDCLS_DISABLE_DOUBLE_SCAN_HU, "Dupla p·szt·z·s tilt·sa"},
	/* it */ {IDCLS_DISABLE_DOUBLE_SCAN_IT, "Disattiva scansione doppia"},
	/* ko */ {IDCLS_DISABLE_DOUBLE_SCAN_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DOUBLE_SCAN_NL, "Dubbele scan uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DOUBLE_SCAN_PL, "Wy≥±cz podwÛjne skanowanie"},
	/* ru */ {IDCLS_DISABLE_DOUBLE_SCAN_RU, "Disable double scan"},
	/* sv */ {IDCLS_DISABLE_DOUBLE_SCAN_SV, "Inaktivera dubbelskanning"},
	/* tr */ {IDCLS_DISABLE_DOUBLE_SCAN_TR, "«ift taramay˝ pasifle˛tir"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_AUDIO_LEAK,    N_("Enable audio leak emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_AUDIO_LEAK_DA, "AktivÈr audiolÊkage-emulering"},
	/* de */ {IDCLS_ENABLE_AUDIO_LEAK_DE, "Audio Leak Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_AUDIO_LEAK_ES, "Permitir emulaciÛn audio leak"},
	/* fr */ {IDCLS_ENABLE_AUDIO_LEAK_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_AUDIO_LEAK_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_AUDIO_LEAK_IT, "Attiva emulazione audio leak"},
	/* ko */ {IDCLS_ENABLE_AUDIO_LEAK_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_AUDIO_LEAK_NL, "Activeer audio lek emulatie"},
	/* pl */ {IDCLS_ENABLE_AUDIO_LEAK_PL, "W≥±cz emulacjÍ brudÛw w dºwiÍku"},
	/* ru */ {IDCLS_ENABLE_AUDIO_LEAK_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_AUDIO_LEAK_SV, "Aktivera emulering av audiol‰ckage"},
	/* tr */ {IDCLS_ENABLE_AUDIO_LEAK_TR, "Ses kaÁa˝ em¸lasyonunu aktif et"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_AUDIO_LEAK,    N_("Disable audio leak emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_AUDIO_LEAK_DA, "DeaktivÈr audiolÊkage-emulering"},
	/* de */ {IDCLS_DISABLE_AUDIO_LEAK_DE, "Audio Leak Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_AUDIO_LEAK_ES, "Deshabilitar emulaciÛn audio leak"},
	/* fr */ {IDCLS_DISABLE_AUDIO_LEAK_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_AUDIO_LEAK_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_AUDIO_LEAK_IT, "Disattiva emulazione audio leak"},
	/* ko */ {IDCLS_DISABLE_AUDIO_LEAK_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_AUDIO_LEAK_NL, "De audio lek emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_AUDIO_LEAK_PL, "Wy≥±cz emulacjÍ brudÛw w dºwiÍku"},
	/* ru */ {IDCLS_DISABLE_AUDIO_LEAK_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_AUDIO_LEAK_SV, "Inaktivera emulering av audiol‰ckage"},
	/* tr */ {IDCLS_DISABLE_AUDIO_LEAK_TR, "Ses kaÁa˝ em¸lasyonunu pasifle˛tir"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_ENABLE_HARDWARE_SCALING,    N_("Enable hardware scaling")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_HARDWARE_SCALING_DA, "AktivÈr hardware-skalering"},
	/* de */ {IDCLS_ENABLE_HARDWARE_SCALING_DE, "Hardwareunterst¸tzung f¸r Skalierung aktivieren"},
	/* es */ {IDCLS_ENABLE_HARDWARE_SCALING_ES, "Permitir escalado hardware"},
	/* fr */ {IDCLS_ENABLE_HARDWARE_SCALING_FR, "Activer le \"scaling\" matÈriel"},
	/* hu */ {IDCLS_ENABLE_HARDWARE_SCALING_HU, "Hardver ·tmÈretezÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_HARDWARE_SCALING_IT, "Attiva hardware scaling"},
	/* ko */ {IDCLS_ENABLE_HARDWARE_SCALING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_HARDWARE_SCALING_NL, "Activeer hardwareschaling"},
	/* pl */ {IDCLS_ENABLE_HARDWARE_SCALING_PL, "W≥±cz skalowanie sprzÍtowe"},
	/* ru */ {IDCLS_ENABLE_HARDWARE_SCALING_RU, "Enable hardware scaling"},
	/* sv */ {IDCLS_ENABLE_HARDWARE_SCALING_SV, "Aktivera maskinvaruskalning"},
	/* tr */ {IDCLS_ENABLE_HARDWARE_SCALING_TR, "Donan˝m destekli ˆlÁeklendirmeyi aktif et"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_DISABLE_HARDWARE_SCALING,    N_("Disable hardware scaling")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_HARDWARE_SCALING_DA, "DeaktivÈr hardware-skalering"},
	/* de */ {IDCLS_DISABLE_HARDWARE_SCALING_DE, "Hardwareunterst¸tzung f¸r Skalierung deaktivieren"},
	/* es */ {IDCLS_DISABLE_HARDWARE_SCALING_ES, "Deshabilitar escalado hardware"},
	/* fr */ {IDCLS_DISABLE_HARDWARE_SCALING_FR, "DÈsactiver le \"scaling\" matÈriel"},
	/* hu */ {IDCLS_DISABLE_HARDWARE_SCALING_HU, "Hardver ·tmÈretezÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_HARDWARE_SCALING_IT, "Disattiva hardware scaling"},
	/* ko */ {IDCLS_DISABLE_HARDWARE_SCALING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_HARDWARE_SCALING_NL, "Hardwareschaling uitschakelen"},
	/* pl */ {IDCLS_DISABLE_HARDWARE_SCALING_PL, "Wy≥±cz skalowanie sprzÍtowe"},
	/* ru */ {IDCLS_DISABLE_HARDWARE_SCALING_RU, "Disable hardware scaling"},
	/* sv */ {IDCLS_DISABLE_HARDWARE_SCALING_SV, "Inaktivera maskinvaruskalning"},
	/* tr */ {IDCLS_DISABLE_HARDWARE_SCALING_TR, "Donan˝m destekli ˆlÁeklendirmeyi pasifle˛tir"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_SET_VIDEO_FILTER,    N_("Select rendering filter, 0:none, 1:CRT emulation, 2: scale2x")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_VIDEO_FILTER_DA, "VÊlg renderingsfilter (0:intet, 1:CRT-emulering, 2: scale2x)"},
	/* de */ {IDCLS_SET_VIDEO_FILTER_DE, "W‰hle Rendering Filter, 0:kein, 1:CRT Emulation, 2: Scale2x"},
	/* es */ {IDCLS_SET_VIDEO_FILTER_ES, "Seleccionar filtro de renderizador, 0:no, 1:emulaciÛn CRT, 2: escala2x"},
	/* fr */ {IDCLS_SET_VIDEO_FILTER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_VIDEO_FILTER_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_VIDEO_FILTER_IT, "Seleziona il filtro di rendering, 0:none, 1:CRT emulation, 2: scale2x"},
	/* ko */ {IDCLS_SET_VIDEO_FILTER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_VIDEO_FILTER_NL, "Selecteer de rendering filter: 0:geen, 1:CRT emulatie, 2:Schaal2x"},
	/* pl */ {IDCLS_SET_VIDEO_FILTER_PL, "Wybierz filtr renderera, 0:brak, 1: emulacja CRT, 2: skalowanie2x"},
	/* ru */ {IDCLS_SET_VIDEO_FILTER_RU, "Select rendering filter, 0:none, 1:CRT emulation, 2: scale2x"},
	/* sv */ {IDCLS_SET_VIDEO_FILTER_SV, "Ange rendreringsfiler, 0:ingen, 1:CRT-emulering, 2:scale2x"},
	/* tr */ {IDCLS_SET_VIDEO_FILTER_TR, "Gˆr¸nt¸ olu˛turma filitresini seÁ, 0:yok, 1:CRT em¸lasyonu, 2: geni˛let2x"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_USE_INTERNAL_CALC_PALETTE,    N_("Use an internal calculated palette")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_INTERNAL_CALC_PALETTE_DA, "Brug en internt beregnet palette"},
	/* de */ {IDCLS_USE_INTERNAL_CALC_PALETTE_DE, "Benutze intern berechnete Palette"},
	/* es */ {IDCLS_USE_INTERNAL_CALC_PALETTE_ES, "Usar paleta calculada internamente"},
	/* fr */ {IDCLS_USE_INTERNAL_CALC_PALETTE_FR, "Utiliser une palette interne calculÈe"},
	/* hu */ {IDCLS_USE_INTERNAL_CALC_PALETTE_HU, "Belsıleg sz·mÌtott paletta haszn·lata"},
	/* it */ {IDCLS_USE_INTERNAL_CALC_PALETTE_IT, "Usa una palette interna calcolata"},
	/* ko */ {IDCLS_USE_INTERNAL_CALC_PALETTE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_INTERNAL_CALC_PALETTE_NL, "Gebruik een intern berekend kleurenpalet"},
	/* pl */ {IDCLS_USE_INTERNAL_CALC_PALETTE_PL, "Uøywaj wewnÍtrznej obliczonej palety kolorystycznej"},
	/* ru */ {IDCLS_USE_INTERNAL_CALC_PALETTE_RU, "Use an internal calculated palette"},
	/* sv */ {IDCLS_USE_INTERNAL_CALC_PALETTE_SV, "Anv‰nd en internt ber‰knad palett"},
	/* tr */ {IDCLS_USE_INTERNAL_CALC_PALETTE_TR, "Dahili hesaplanm˝˛ bir palet kullan"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_USE_EXTERNAL_FILE_PALETTE,    N_("Use an external palette (file)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_DA, "Brug en ekstern palette (fil)"},
	/* de */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_DE, "Benutze externe Palette (Datei)"},
	/* es */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_ES, "Usar paleta externa (fichero)"},
	/* fr */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_FR, "Utiliser une palette externe (fichier)"},
	/* hu */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_HU, "K¸lsı paletta haszn·lata (f·jl)"},
	/* it */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_IT, "Usa una palette esterna (file)"},
	/* ko */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_NL, "Gebruik een extern kleurenpalet (bestand)"},
	/* pl */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_PL, "Uøywaj zewnÍtrznej palety kolorystycznej (z pliku)"},
	/* ru */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_RU, "Use an external palette (file)"},
	/* sv */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_SV, "Anv‰nd en extern palett (fil)"},
	/* tr */ {IDCLS_USE_EXTERNAL_FILE_PALETTE_TR, "Harici bir palet (dosyadan) kullan"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME,    N_("Specify name of file of external palette")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_DA, "Angiv filnavn for ekstern palette"},
	/* de */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_DE, "Dateiname f¸r externe Palette definieren"},
	/* es */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_ES, "Especificar nombre fichero de la paleta externa"},
	/* fr */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_FR, "SpÈcifier le nom du fichier de la palette externe"},
	/* hu */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_HU, "Adja meg a k¸lsı paletta nevÈt"},
	/* it */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_IT, "Specifica il nome del file della palette esterna"},
	/* ko */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_NL, "Geef de naam van het extern kleurenpaletbestand"},
	/* pl */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_PL, "Okre∂l nazwÍ pliku zewnÍtrznej palety barw"},
	/* ru */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_RU, "Specify name of file of external palette"},
	/* sv */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_SV, "Ange namn pÂ fil fˆr extern palett"},
	/* tr */ {IDCLS_SPECIFY_EXTERNAL_PALETTE_NAME_TR, "Harici palet dosyas˝n˝n ismini belirt"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_P_DEVICE,    N_("<device>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_DEVICE_DA, "<enhed>"},
	/* de */ {IDCLS_P_DEVICE_DE, "<Ger‰t>"},
	/* es */ {IDCLS_P_DEVICE_ES, "<perifÈrico>"},
	/* fr */ {IDCLS_P_DEVICE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_DEVICE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_DEVICE_IT, "<dispositivo>"},
	/* ko */ {IDCLS_P_DEVICE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_DEVICE_NL, "<apparaat>"},
	/* pl */ {IDCLS_P_DEVICE_PL, "<device>"},
	/* ru */ {IDCLS_P_DEVICE_RU, "<device>"},
	/* sv */ {IDCLS_P_DEVICE_SV, "<enhet>"},
	/* tr */ {IDCLS_P_DEVICE_TR, "<ayg˝t>"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_SELECT_FULLSCREEN_DEVICE,    N_("Select fullscreen device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SELECT_FULLSCREEN_DEVICE_DA, "Angiv fuldskÊrmsenhed"},
	/* de */ {IDCLS_SELECT_FULLSCREEN_DEVICE_DE, "Vollbild Ger‰t ausw‰hlen"},
	/* es */ {IDCLS_SELECT_FULLSCREEN_DEVICE_ES, "Seleccionar perifÈrico pantalla completa"},
	/* fr */ {IDCLS_SELECT_FULLSCREEN_DEVICE_FR, "SÈlectionner le pÈriphÈrique plein Ècran"},
	/* hu */ {IDCLS_SELECT_FULLSCREEN_DEVICE_HU, "TeljeskÈpernyıs eszkˆz kiv·laszt·sa"},
	/* it */ {IDCLS_SELECT_FULLSCREEN_DEVICE_IT, "Seleziona il dispositivo per la visualizzazione a schermo intero"},
	/* ko */ {IDCLS_SELECT_FULLSCREEN_DEVICE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SELECT_FULLSCREEN_DEVICE_NL, "Selecteer volschermapparaat"},
	/* pl */ {IDCLS_SELECT_FULLSCREEN_DEVICE_PL, "Wybierz urz±dzenie pe≥nego ekranu"},
	/* ru */ {IDCLS_SELECT_FULLSCREEN_DEVICE_RU, "Select fullscreen device"},
	/* sv */ {IDCLS_SELECT_FULLSCREEN_DEVICE_SV, "Ange fullsk‰rmsenhet"},
	/* tr */ {IDCLS_SELECT_FULLSCREEN_DEVICE_TR, "Tam ekran ayg˝t˝ seÁ"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_P_MODE,    N_("<Mode>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_MODE_DA, "<Tilstand>"},
	/* de */ {IDCLS_P_MODE_DE, "<Modus>"},
	/* es */ {IDCLS_P_MODE_ES, "<Modo>"},
	/* fr */ {IDCLS_P_MODE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_MODE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_MODE_IT, "<Modalit‡>"},
	/* ko */ {IDCLS_P_MODE_KO, "<∏µÂ>"},
	/* nl */ {IDCLS_P_MODE_NL, "<Modus>"},
	/* pl */ {IDCLS_P_MODE_PL, "<Tryb>"},
	/* ru */ {IDCLS_P_MODE_RU, "<Mode>"},
	/* sv */ {IDCLS_P_MODE_SV, "<L‰ge>"},
	/* tr */ {IDCLS_P_MODE_TR, "<Mod>"},
#endif
	
	/* video/video-cmdline-options.c */
	/* en */ {IDCLS_SELECT_FULLSCREEN_MODE,    N_("Select fullscreen mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SELECT_FULLSCREEN_MODE_DA, "AktivÈr fuldskÊrms-tilstand"},
	/* de */ {IDCLS_SELECT_FULLSCREEN_MODE_DE, "Vollbild Modus w‰hlen"},
	/* es */ {IDCLS_SELECT_FULLSCREEN_MODE_ES, "Seleccionar modo pantalla completa"},
	/* fr */ {IDCLS_SELECT_FULLSCREEN_MODE_FR, "SÈlectionner le mode plein Ècran"},
	/* hu */ {IDCLS_SELECT_FULLSCREEN_MODE_HU, "Teljes kÈpernyıs mÛd kiv·laszt·sa"},
	/* it */ {IDCLS_SELECT_FULLSCREEN_MODE_IT, "Seleziona modalit‡ a schermo intero"},
	/* ko */ {IDCLS_SELECT_FULLSCREEN_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SELECT_FULLSCREEN_MODE_NL, "Activeer volschermmodus"},
	/* pl */ {IDCLS_SELECT_FULLSCREEN_MODE_PL, "Wybierz tryb pe≥nego ekranu"},
	/* ru */ {IDCLS_SELECT_FULLSCREEN_MODE_RU, "Select fullscreen mode"},
	/* sv */ {IDCLS_SELECT_FULLSCREEN_MODE_SV, "Aktivera fullsk‰rmsl‰ge"},
	/* tr */ {IDCLS_SELECT_FULLSCREEN_MODE_TR, "Tam ekran modu seÁ"},
#endif
	
	/* aciacore.c */
	/* en */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE,    N_("Specify RS232 device this ACIA should work on")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_DA, "Angiv RS232-enhed denne ACIA skal bruge"},
	/* de */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_DE, "RS232 Ger‰t f¸r welches ACIA funktionieren soll ist zu spezifizieren"},
	/* es */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_ES, "Specificar perifÈrico RS232 con el que funcionar· esta ACIA"},
	/* fr */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_FR, "SpÈcifier le pÈriphÈrique RS232 sur lequel cet ACIA doit fonctionner"},
	/* hu */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_HU, "Adja meg az RS232-es egysÈget, amivel az ACIA m˚kˆdni fog"},
	/* it */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_IT, "Specifica il dispositivo RS232 con il quale questa ACIA dovrebbe funzionare"},
	/* ko */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_NL, "Geef het RS232 apparaat waarmee deze ACIA moet werken"},
	/* pl */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_PL, "Okre∂l urz±dzenie RS232, na ktÛrym ma dzia≥aÊ ACIA"},
	/* ru */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_RU, "Specify RS232 device this ACIA should work on"},
	/* sv */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_SV, "Ange RS232-enhet denna ACIA skall arbeta pÂ"},
	/* tr */ {IDCLS_SPECIFY_ACIA_RS232_DEVICE_TR, "Bu ACIA'in Áal˝˛mas˝ gereken RS232 ayg˝t˝n˝ belirt"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_SET_DEVICE_TYPE_8,    N_("Set device type for device #8 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DEVICE_TYPE_8_DA, "VÊlg type for enhed #8 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOKENHED)"},
	/* de */ {IDCLS_SET_DEVICE_TYPE_8_DE, "Ger‰te Typ f¸r Ger‰t #8 (0: Kein, 1: Dateisystem, 2: OpenCBM, 3: Block Ger‰t)"},
	/* es */ {IDCLS_SET_DEVICE_TYPE_8_ES, "Seleccionar tipo para perifÈrico #8  (0: NINGUNO, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* fr */ {IDCLS_SET_DEVICE_TYPE_8_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_DEVICE_TYPE_8_HU, "Adja meg a #8-es egysÈg tÌpus·t (0: Nincs, 1: f·jlrendszer, 2: OPENCBM, 3 blokk eszkˆz)"},
	/* it */ {IDCLS_SET_DEVICE_TYPE_8_IT, "Imposta il tipo di periferica #8 (0 NESSUNA, 1: FILESYSTEM, 2: OPENCBM, 3: DISPOSITIVO A BLOCCHI)"},
	/* ko */ {IDCLS_SET_DEVICE_TYPE_8_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DEVICE_TYPE_8_NL, "Zet het apparaatsoort voor apparaat #8 (0: GEEN, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK APPARAAT)"},
	/* pl */ {IDCLS_SET_DEVICE_TYPE_8_PL, "Okre∂l typ urz±dzenia #8 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* ru */ {IDCLS_SET_DEVICE_TYPE_8_RU, "Set device type for device #8 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* sv */ {IDCLS_SET_DEVICE_TYPE_8_SV, "St‰ll in enhetstyp fˆr enhet 8 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOCKENHET)"},
	/* tr */ {IDCLS_SET_DEVICE_TYPE_8_TR, "Ayg˝t #8 iÁin ayg˝t tipini belirt (0: YOK, 1: DOSYAS›STEM›, 2: OPENCBM, 3: BLOK AYIGTI)"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_SET_DEVICE_TYPE_9,    N_("Set device type for device #9 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DEVICE_TYPE_9_DA, "VÊlg type for enhed #9 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOKENHED)"},
	/* de */ {IDCLS_SET_DEVICE_TYPE_9_DE, "Ger‰te Typ f¸r Ger‰t #9 (0: Kein, 1: Dateisystem, 2: OpenCBM, 3: Block Ger‰t)"},
	/* es */ {IDCLS_SET_DEVICE_TYPE_9_ES, "Seleccionar tipo para perifÈrico #9  (0: NINGUNO, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* fr */ {IDCLS_SET_DEVICE_TYPE_9_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_DEVICE_TYPE_9_HU, "Adja meg a #9-es egysÈg tÌpus·t (0: Nincs, 1: f·jlrendszer, 2: OPENCBM, 3: blokk eszkˆz)"},
	/* it */ {IDCLS_SET_DEVICE_TYPE_9_IT, "Imposta il tipo di periferica #9 (0 NESSUNA, 1: FILESYSTEM, 2: OPENCBM, 3: DISPOSITIVO A BLOCCHI)"},
	/* ko */ {IDCLS_SET_DEVICE_TYPE_9_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DEVICE_TYPE_9_NL, "Zet het apparaatsoort voor apparaat #9 (0: GEEN, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK APPARAAT)"},
	/* pl */ {IDCLS_SET_DEVICE_TYPE_9_PL, "Okre∂l typ urz±dzenia #8 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* ru */ {IDCLS_SET_DEVICE_TYPE_9_RU, "Set device type for device #9 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* sv */ {IDCLS_SET_DEVICE_TYPE_9_SV, "St‰ll in enhetstyp fˆr enhet 9 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOCKENHET)"},
	/* tr */ {IDCLS_SET_DEVICE_TYPE_9_TR, "Ayg˝t #9 iÁin ayg˝t tipini belirt (0: YOK, 1: DOSYAS›STEM›, 2: OPENCBM, 3: BLOK AYIGTI)"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_SET_DEVICE_TYPE_10,    N_("Set device type for device #10 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DEVICE_TYPE_10_DA, "VÊlg type for enhed #10 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOKENHED)"},
	/* de */ {IDCLS_SET_DEVICE_TYPE_10_DE, "Ger‰te Typ f¸r Ger‰t #10 (0: Kein, 1: Dateisystem, 2: OpenCBM, 3: Block Ger‰t)"},
	/* es */ {IDCLS_SET_DEVICE_TYPE_10_ES, "Seleccionar tipo para perifÈrico #10  (0: NINGUNO, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* fr */ {IDCLS_SET_DEVICE_TYPE_10_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_DEVICE_TYPE_10_HU, "Adja meg a #10-es egysÈg tÌpus·t (0: Nincs, 1: f·jlrendszer, 2: OPENVMB, 3: blokk eszkˆz)"},
	/* it */ {IDCLS_SET_DEVICE_TYPE_10_IT, "Imposta il tipo di periferica #10 (0 NESSUNA, 1: FILESYSTEM, 2: OPENCBM, 3: DISPOSITIVO A BLOCCHI)"},
	/* ko */ {IDCLS_SET_DEVICE_TYPE_10_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DEVICE_TYPE_10_NL, "Zet het apparaatsoort voor apparaat #10 (0: GEEN, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK APPARAAT)"},
	/* pl */ {IDCLS_SET_DEVICE_TYPE_10_PL, "Okre∂l typ urz±dzenia #8 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* ru */ {IDCLS_SET_DEVICE_TYPE_10_RU, "Set device type for device #10 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* sv */ {IDCLS_SET_DEVICE_TYPE_10_SV, "St‰ll in enhetstyp fˆr enhet 10 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOCKENHET)"},
	/* tr */ {IDCLS_SET_DEVICE_TYPE_10_TR, "Ayg˝t #10 iÁin ayg˝t tipini belirt (0: YOK, 1: DOSYAS›STEM›, 2: OPENCBM, 3: BLOK AYIGTI)"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_SET_DEVICE_TYPE_11,    N_("Set device type for device #11 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_DEVICE_TYPE_11_DA, "VÊlg type for enhed #11 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOKENHED)"},
	/* de */ {IDCLS_SET_DEVICE_TYPE_11_DE, "Ger‰te Typ f¸r Ger‰t #11 (0: Kein, 1: Dateisystem, 2: OpenCBM, 3: Block Ger‰t)"},
	/* es */ {IDCLS_SET_DEVICE_TYPE_11_ES, "Seleccionar tipo para perifÈrico #11  (0: NINGUNO, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* fr */ {IDCLS_SET_DEVICE_TYPE_11_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_DEVICE_TYPE_11_HU, "Adja meg a #11-es egysÈg tÌpus·t (0: Nincs, 1: f·jlrendszer, 2: OPENCBM, 3: blokk eszkˆz)"},
	/* it */ {IDCLS_SET_DEVICE_TYPE_11_IT, "Imposta il tipo di periferica #11 (0 NESSUNA, 1: FILESYSTEM, 2: OPENCBM, 3: DISPOSITIVO A BLOCCHI)"},
	/* ko */ {IDCLS_SET_DEVICE_TYPE_11_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_DEVICE_TYPE_11_NL, "Zet het apparaatsoort voor apparaat #11 (0: GEEN, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK APPARAAT)"},
	/* pl */ {IDCLS_SET_DEVICE_TYPE_11_PL, "Okre∂l typ urz±dzenia #8 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* ru */ {IDCLS_SET_DEVICE_TYPE_11_RU, "Set device type for device #11 (0: NONE, 1: FILESYSTEM, 2: OPENCBM, 3: BLOCK DEVICE)"},
	/* sv */ {IDCLS_SET_DEVICE_TYPE_11_SV, "St‰ll in enhetstyp fˆr enhet 11 (0: INGEN, 1: FILSYSTEM, 2: OPENCBM, 3: BLOCKENHET)"},
	/* tr */ {IDCLS_SET_DEVICE_TYPE_11_TR, "Ayg˝t #11 iÁin ayg˝t tipini belirt (0: YOK, 1: DOSYAS›STEM›, 2: OPENCBM, 3: BLOK AYIGTI)"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_ONLY_8,    N_("Attach disk image for drive #8 read only")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_ONLY_8_DA, "Tilslut disk-image til drev #8 skrivebeskyttet"},
	/* de */ {IDCLS_ATTACH_READ_ONLY_8_DE, "Disk Image als Laufwerk #8 benutzen (schreibgesch¸tzt)"},
	/* es */ {IDCLS_ATTACH_READ_ONLY_8_ES, "Insertar imagen disco sÛlo lectura para unidad disco #8"},
	/* fr */ {IDCLS_ATTACH_READ_ONLY_8_FR, "Charger une image de disque pour le lecteur #8 en lecture seule"},
	/* hu */ {IDCLS_ATTACH_READ_ONLY_8_HU, "Csak olvashatÛ kÈpm·s csatol·sa a #8-as lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_ONLY_8_IT, "Seleziona immagine del disco per il drive #8 in sola lettura"},
	/* ko */ {IDCLS_ATTACH_READ_ONLY_8_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_ONLY_8_NL, "Koppel schijfbestand voor drive #8 als alleen-lezen"},
	/* pl */ {IDCLS_ATTACH_READ_ONLY_8_PL, "Zamontuj obraz dysku w stacji #8 tylko do odczytu"},
	/* ru */ {IDCLS_ATTACH_READ_ONLY_8_RU, "Attach disk image for drive #8 read only"},
	/* sv */ {IDCLS_ATTACH_READ_ONLY_8_SV, "Anslut diskettavbildningsfil fˆr enhet 8 med skrivskydd"},
	/* tr */ {IDCLS_ATTACH_READ_ONLY_8_TR, "S¸r¸c¸ #8 iÁin disk imaj˝n˝ salt okunur olarak yerle˛tir"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_WRITE_8,    N_("Attach disk image for drive #8 read write (if possible)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_WRITE_8_DA, "Tilslut disk-image til drev #8 skrivbar (hvis muligt)"},
	/* de */ {IDCLS_ATTACH_READ_WRITE_8_DE, "Disk Image als Laufwerk #8 benutzen (Schreibzugriff, wenn mˆglich)"},
	/* es */ {IDCLS_ATTACH_READ_WRITE_8_ES, "Insertar imagen disco sÛlo lectura/grabaciÛn (si es posible) para unidad disco #8"},
	/* fr */ {IDCLS_ATTACH_READ_WRITE_8_FR, "Charger une image de disque pour le lecteur #8 en lecture-Ècriture (si possible)"},
	/* hu */ {IDCLS_ATTACH_READ_WRITE_8_HU, "ÕrhatÛ-olvashatÛ kÈpm·s csatol·sa a #8-as lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_WRITE_8_IT, "Seleziona immagine del disco per il drive #8 in lettura/scrittura (se possibile)"},
	/* ko */ {IDCLS_ATTACH_READ_WRITE_8_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_WRITE_8_NL, "Koppel schijfbestand voor drive #8 als schrijfbaar (indien mogelijk)"},
	/* pl */ {IDCLS_ATTACH_READ_WRITE_8_PL, "Zamontuj obraz dyskietki w stacji #8 w trybie zapisu i odczytu (o ile to moøliwe)"},
	/* ru */ {IDCLS_ATTACH_READ_WRITE_8_RU, "Attach disk image for drive #8 read write (if possible)"},
	/* sv */ {IDCLS_ATTACH_READ_WRITE_8_SV, "Anslut diskettavbildningsfil fˆr enhet 8 skrivbar (om mˆjligt)"},
	/* tr */ {IDCLS_ATTACH_READ_WRITE_8_TR, "S¸r¸c¸ #8 iÁin disk imaj˝n˝ okunur/yaz˝l˝r olarak yerle˛tir (m¸mk¸nse)"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_ONLY_9,    N_("Attach disk image for drive #9 read only")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_ONLY_9_DA, "Tilslut disk-image til drev #9 skrivebeskyttet"},
	/* de */ {IDCLS_ATTACH_READ_ONLY_9_DE, "Disk Image als Laufwerk #9 benutzen (schreibgesch¸tzt)"},
	/* es */ {IDCLS_ATTACH_READ_ONLY_9_ES, "Insertar imagen disco sÛlo lectura para unidad disco #9"},
	/* fr */ {IDCLS_ATTACH_READ_ONLY_9_FR, "Charger une image de disque pour le lecteur #9 en lecture seule"},
	/* hu */ {IDCLS_ATTACH_READ_ONLY_9_HU, "Csak olvashatÛ kÈpm·s csatol·sa a #9-es lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_ONLY_9_IT, "Seleziona immagine del disco per il drive #9 in sola lettura"},
	/* ko */ {IDCLS_ATTACH_READ_ONLY_9_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_ONLY_9_NL, "Koppel schijfbestand voor drive #9 als alleen-lezen"},
	/* pl */ {IDCLS_ATTACH_READ_ONLY_9_PL, "Zamontuj obraz dysku w stacji #9 tylko do odczytu"},
	/* ru */ {IDCLS_ATTACH_READ_ONLY_9_RU, "Attach disk image for drive #9 read only"},
	/* sv */ {IDCLS_ATTACH_READ_ONLY_9_SV, "Anslut diskettavbildningsfil fˆr enhet 9 med skrivskydd"},
	/* tr */ {IDCLS_ATTACH_READ_ONLY_9_TR, "S¸r¸c¸ #9 iÁin disk imaj˝n˝ salt okunur olarak yerle˛tir"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_WRITE_9,    N_("Attach disk image for drive #9 read write (if possible)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_WRITE_9_DA, "Tilslut disk-image til drev #9 skrivbar (hvis muligt)"},
	/* de */ {IDCLS_ATTACH_READ_WRITE_9_DE, "Disk Image als Laufwerk #9 benutzen (Schreibzugriff, wenn mˆglich)"},
	/* es */ {IDCLS_ATTACH_READ_WRITE_9_ES, "Insertar imagen disco sÛlo lectura/grabaciÛn (si es posible) para unidad disco #9"},
	/* fr */ {IDCLS_ATTACH_READ_WRITE_9_FR, "Charger une image de disque pour le lecteur #9 en lecture-Ècriture (si possible)"},
	/* hu */ {IDCLS_ATTACH_READ_WRITE_9_HU, "ÕrhatÛ-olvashatÛ kÈpm·s csatol·sa a #9-es lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_WRITE_9_IT, "Seleziona immagine del disco per il drive #9 in lettura/scrittura (se possibile)"},
	/* ko */ {IDCLS_ATTACH_READ_WRITE_9_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_WRITE_9_NL, "Koppel schijfbestand voor drive #9 als schrijfbaar (indien mogelijk)"},
	/* pl */ {IDCLS_ATTACH_READ_WRITE_9_PL, "Zamontuj obraz dyskietki w stacji #9 w trybie zapisu i odczytu (o ile to moøliwe)"},
	/* ru */ {IDCLS_ATTACH_READ_WRITE_9_RU, "Attach disk image for drive #9 read write (if possible)"},
	/* sv */ {IDCLS_ATTACH_READ_WRITE_9_SV, "Anslut diskettavbildningsfil fˆr enhet 9 skrivbar (om mˆjligt)"},
	/* tr */ {IDCLS_ATTACH_READ_WRITE_9_TR, "S¸r¸c¸ #9 iÁin disk imaj˝n˝ okunur/yaz˝l˝r olarak yerle˛tir (m¸mk¸nse)"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_ONLY_10,    N_("Attach disk image for drive #10 read only")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_ONLY_10_DA, "Tilslut disk-image til drev #10 skrivebeskyttet"},
	/* de */ {IDCLS_ATTACH_READ_ONLY_10_DE, "Disk Image als Laufwerk #10 benutzen (schreibgesch¸tzt)"},
	/* es */ {IDCLS_ATTACH_READ_ONLY_10_ES, "Insertar imagen disco sÛlo lectura para unidad disco #10"},
	/* fr */ {IDCLS_ATTACH_READ_ONLY_10_FR, "Charger une image de disque pour le lecteur #10 en lecture seule"},
	/* hu */ {IDCLS_ATTACH_READ_ONLY_10_HU, "Csak olvashatÛ kÈpm·s csatol·sa a #10-es lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_ONLY_10_IT, "Seleziona immagine del disco per il drive #10 in sola lettura"},
	/* ko */ {IDCLS_ATTACH_READ_ONLY_10_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_ONLY_10_NL, "Koppel schijfbestand voor drive #10 als alleen-lezen"},
	/* pl */ {IDCLS_ATTACH_READ_ONLY_10_PL, "Zamontuj obraz dysku w stacji #10 tylko do odczytu"},
	/* ru */ {IDCLS_ATTACH_READ_ONLY_10_RU, "Attach disk image for drive #10 read only"},
	/* sv */ {IDCLS_ATTACH_READ_ONLY_10_SV, "Anslut diskettavbildningsfil fˆr enhet 10 med skrivskydd"},
	/* tr */ {IDCLS_ATTACH_READ_ONLY_10_TR, "S¸r¸c¸ #10 iÁin disk imaj˝n˝ salt okunur olarak yerle˛tir"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_WRITE_10,    N_("Attach disk image for drive #10 read write (if possible)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_WRITE_10_DA, "Tilslut disk-image til drev #10 skrivbar (hvis muligt)"},
	/* de */ {IDCLS_ATTACH_READ_WRITE_10_DE, "Disk Image als Laufwerk #10 benutzen (Schreibzugriff, wenn mˆglich)"},
	/* es */ {IDCLS_ATTACH_READ_WRITE_10_ES, "Insertar imagen disco sÛlo lectura/grabaciÛn (si es posible) para unidad disco #10"},
	/* fr */ {IDCLS_ATTACH_READ_WRITE_10_FR, "Charger une image de disque pour le lecteur #10 en lecture-Ècriture (si possible)"},
	/* hu */ {IDCLS_ATTACH_READ_WRITE_10_HU, "ÕrhatÛ-olvashatÛ kÈpm·s csatol·sa a #10-es lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_WRITE_10_IT, "Seleziona immagine del disco per il drive #10 in lettura/scrittura (se possibile)"},
	/* ko */ {IDCLS_ATTACH_READ_WRITE_10_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_WRITE_10_NL, "Koppel schijfbestand voor drive #10 als schrijfbaar (indien mogelijk)"},
	/* pl */ {IDCLS_ATTACH_READ_WRITE_10_PL, "Zamontuj obraz dyskietki w stacji #10 w trybie zapisu i odczytu (o ile to moøliwe)"},
	/* ru */ {IDCLS_ATTACH_READ_WRITE_10_RU, "Attach disk image for drive #10 read write (if possible)"},
	/* sv */ {IDCLS_ATTACH_READ_WRITE_10_SV, "Anslut diskettavbildningsfil fˆr enhet 10 skrivbar (om mˆjligt)"},
	/* tr */ {IDCLS_ATTACH_READ_WRITE_10_TR, "S¸r¸c¸ #10 iÁin disk imaj˝n˝ okunur/yaz˝l˝r olarak yerle˛tir (m¸mk¸nse)"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_ONLY_11,    N_("Attach disk image for drive #11 read only")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_ONLY_11_DA, "Tilslut disk-image til drev #11 skrivebeskyttet"},
	/* de */ {IDCLS_ATTACH_READ_ONLY_11_DE, "Disk Image als Laufwerk #11 benutzen (schreibgesch¸tzt)"},
	/* es */ {IDCLS_ATTACH_READ_ONLY_11_ES, "Insertar imagen disco sÛlo lectura para unidad disco #11"},
	/* fr */ {IDCLS_ATTACH_READ_ONLY_11_FR, "Charger une image de disque pour le lecteur #11 en lecture seule"},
	/* hu */ {IDCLS_ATTACH_READ_ONLY_11_HU, "Csak olvashatÛ kÈpm·s csatol·sa a #11-es lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_ONLY_11_IT, "Seleziona immagine del disco per il drive #11 in sola lettura"},
	/* ko */ {IDCLS_ATTACH_READ_ONLY_11_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_ONLY_11_NL, "Koppel schijfbestand voor drive #11 als alleen-lezen"},
	/* pl */ {IDCLS_ATTACH_READ_ONLY_11_PL, "Zamontuj obraz dysku w stacji #11 tylko do odczytu"},
	/* ru */ {IDCLS_ATTACH_READ_ONLY_11_RU, "Attach disk image for drive #11 read only"},
	/* sv */ {IDCLS_ATTACH_READ_ONLY_11_SV, "Anslut diskettavbildningsfil fˆr enhet 11 med skrivskydd"},
	/* tr */ {IDCLS_ATTACH_READ_ONLY_11_TR, "S¸r¸c¸ #11 iÁin disk imaj˝n˝ salt okunur olarak yerle˛tir"},
#endif
	
	/* attach.c */
	/* en */ {IDCLS_ATTACH_READ_WRITE_11,    N_("Attach disk image for drive #11 read write (if possible)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_READ_WRITE_11_DA, "Tilslut disk-image til drev #11 skrivbar (hvis muligt)"},
	/* de */ {IDCLS_ATTACH_READ_WRITE_11_DE, "Disk Image als Laufwerk #11 benutzen (Schreibzugriff, wenn mˆglich)"},
	/* es */ {IDCLS_ATTACH_READ_WRITE_11_ES, "Insertar imagen disco sÛlo lectura/grabaciÛn (si es posible) para unidad disco #11"},
	/* fr */ {IDCLS_ATTACH_READ_WRITE_11_FR, "Charger une image de disque pour le lecteur #11 en lecture-Ècriture (si possible)"},
	/* hu */ {IDCLS_ATTACH_READ_WRITE_11_HU, "ÕrhatÛ-olvashatÛ kÈpm·s csatol·sa a #11-es lemezegysÈghez"},
	/* it */ {IDCLS_ATTACH_READ_WRITE_11_IT, "Seleziona immagine del disco per il drive #11 in lettura/scrittura (se possibile)"},
	/* ko */ {IDCLS_ATTACH_READ_WRITE_11_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_READ_WRITE_11_NL, "Koppel schijfbestand voor drive #11 als schrijfbaar (indien mogelijk)"},
	/* pl */ {IDCLS_ATTACH_READ_WRITE_11_PL, "Zamontuj obraz dyskietki w stacji #11 w trybie zapisu i odczytu (o ile to moøliwe)"},
	/* ru */ {IDCLS_ATTACH_READ_WRITE_11_RU, "Attach disk image for drive #11 read write (if possible)"},
	/* sv */ {IDCLS_ATTACH_READ_WRITE_11_SV, "Anslut diskettavbildningsfil fˆr enhet 11 skrivbar (om mˆjligt)"},
	/* tr */ {IDCLS_ATTACH_READ_WRITE_11_TR, "S¸r¸c¸ #11 iÁin disk imaj˝n˝ okunur/yaz˝l˝r olarak yerle˛tir (m¸mk¸nse)"},
#endif
	
	/* datasette.c */
	/* en */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET,    N_("Enable automatic Datasette-Reset")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_DA, "AktivÈr automatisk Datasette-reset"},
	/* de */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_DE, "Automatisches Datasette-Reset aktivieren"},
	/* es */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_ES, "Permitir reinicio autom·tico de la unidad de cinta"},
	/* fr */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_FR, "Activer le redÈmarrage automatique du Datasette"},
	/* hu */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_HU, "Automatikus magnÛ Reset engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_IT, "Attiva reset automatico del registratore"},
	/* ko */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_NL, "Activeer automatische Datasette-Reset"},
	/* pl */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_PL, "W≥±cz automatyczny reset magnetofonu"},
	/* ru */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_RU, "Enable automatic Datasette-Reset"},
	/* sv */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_SV, "Aktivera automatisk DatasetteÂterst‰llning"},
	/* tr */ {IDCLS_ENABLE_AUTO_DATASETTE_RESET_TR, "Otomatik Teyp-Reset'i aktif et"},
#endif
	
	/* datasette.c */
	/* en */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET,    N_("Disable automatic Datasette-Reset")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_DA, "DeaktivÈr automatisk Datasette-reset"},
	/* de */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_DE, "Automatisches Datasette-Reset deaktivieren"},
	/* es */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_ES, "Deshabilitar reinicio autom·tico de la unidad de cinta"},
	/* fr */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_FR, "DÈsactiver le redÈmarrage automatique du Datasette"},
	/* hu */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_HU, "Automatikus magnÛ Reset tilt·sa"},
	/* it */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_IT, "Disattiva reset automatico del registratore"},
	/* ko */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_NL, "Automatische Datasette-Reset uitschakelen"},
	/* pl */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_PL, "Wy≥±cz automatyczny reset magnetofonu"},
	/* ru */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_RU, "Disable automatic Datasette-Reset"},
	/* sv */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_SV, "Inaktivera automatisk DatasetteÂterst‰llning"},
	/* tr */ {IDCLS_DISABLE_AUTO_DATASETTE_RESET_TR, "Otomatik Teyp-Reset'i pasifle˛tir"},
#endif
	
	/* datasette.c */
	/* en */ {IDCLS_SET_ZERO_TAP_DELAY,    N_("Set delay in cycles for a zero in the tap")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_ZERO_TAP_DELAY_DA, "Angiv forsinkelse i cykler for et nul i tap-filen"},
	/* de */ {IDCLS_SET_ZERO_TAP_DELAY_DE, "Verzˆgerung f¸r Zero in Zyklen im Tap"},
	/* es */ {IDCLS_SET_ZERO_TAP_DELAY_ES, "Seleccionar retardo en ciclos para cero en la cinta"},
	/* fr */ {IDCLS_SET_ZERO_TAP_DELAY_FR, "SpÈcifier le dÈlai en cycles pour un zÈro sur le ruban"},
	/* hu */ {IDCLS_SET_ZERO_TAP_DELAY_HU, "Adja meg ciklusokban a legelsı szalagrÈs hossz·t"},
	/* it */ {IDCLS_SET_ZERO_TAP_DELAY_IT, "Imposta il ritardo in cicli per uno zero nel tap"},
	/* ko */ {IDCLS_SET_ZERO_TAP_DELAY_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_ZERO_TAP_DELAY_NL, "Zet de vertraging in cycli voor een nul in de tap"},
	/* pl */ {IDCLS_SET_ZERO_TAP_DELAY_PL, "Okre∂l opÛºnienie cyklÛw dla pocz±tku ta∂my"},
	/* ru */ {IDCLS_SET_ZERO_TAP_DELAY_RU, "Set delay in cycles for a zero in the tap"},
	/* sv */ {IDCLS_SET_ZERO_TAP_DELAY_SV, "Ange v‰ntecykler fˆr nolla i tap-filen"},
	/* tr */ {IDCLS_SET_ZERO_TAP_DELAY_TR, "Balant˝ an˝nda cycle tipinden bekleme s¸resini ayarla"},
#endif
	
	/* datasette.c */
	/* en */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP,    N_("Set number of cycles added to each gap in the tap")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_DA, "Angiv antal cykler der lÊgges til hvert hul i tap-filen"},
	/* de */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_DE, "Setze Anzahl der Zyklen f¸r jedes Loch im Tap"},
	/* es */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_ES, "Seleccionar n˙mero ciclos aÒadidos en cada espacio en la cinta"},
	/* fr */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_FR, "SpÈcifier le nombre de cycles ajoutÈ a chaque raccord du ruban"},
	/* hu */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_HU, "Adja meg ciklusokban a szalagf·jlok kˆzti ¸res rÈs hossz·t"},
	/* it */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_IT, "Imposta il numero di cicli aggiunti ad ogni gap nel tap"},
	/* ko */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_NL, "Zet aantal extra cycli voor elk gat in de tap"},
	/* pl */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_PL, "Okre∂l liczbÍ cyklÛw dodanych do kaødej przerwy w ta∂mie"},
	/* ru */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_RU, "Set number of cycles added to each gap in the tap"},
	/* sv */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_SV, "Ange cykler som l‰ggs till varje gap i tap-filen"},
	/* tr */ {IDCLS_SET_CYCLES_ADDED_GAP_TAP_TR, "Balant˝ an˝nda her bo˛luk iÁin eklenecek cycle say˝s˝n˝ ayarla"},
#endif
	
#ifdef DEBUG
	/* debug.c */
	/* en */ {IDCLS_TRACE_MAIN_CPU,    N_("Trace the main CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TRACE_MAIN_CPU_DA, "Trace hovedprocessoren"},
	/* de */ {IDCLS_TRACE_MAIN_CPU_DE, "Haupt CPU verfolgen"},
	/* es */ {IDCLS_TRACE_MAIN_CPU_ES, "Rastrear CPU principal"},
	/* fr */ {IDCLS_TRACE_MAIN_CPU_FR, "Tracer l'UCT principal"},
	/* hu */ {IDCLS_TRACE_MAIN_CPU_HU, "Fı CPU nyomkˆvetÈse"},
	/* it */ {IDCLS_TRACE_MAIN_CPU_IT, "Traccia la CPU principale"},
	/* ko */ {IDCLS_TRACE_MAIN_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TRACE_MAIN_CPU_NL, "Traceer de hoofd CPU"},
	/* pl */ {IDCLS_TRACE_MAIN_CPU_PL, "¶ledzenie g≥Ûwnego CPU"},
	/* ru */ {IDCLS_TRACE_MAIN_CPU_RU, "Trace the main CPU"},
	/* sv */ {IDCLS_TRACE_MAIN_CPU_SV, "SpÂra huvudprocessorn"},
	/* tr */ {IDCLS_TRACE_MAIN_CPU_TR, "Ana CPU'yu izle"},
#endif
	
	/* debug.c */
	/* en */ {IDCLS_DONT_TRACE_MAIN_CPU,    N_("Do not trace the main CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_TRACE_MAIN_CPU_DA, "Trace ikke hovedprocessoren"},
	/* de */ {IDCLS_DONT_TRACE_MAIN_CPU_DE, "Haupt CPU nicht verfolgen"},
	/* es */ {IDCLS_DONT_TRACE_MAIN_CPU_ES, "No rastrear CPU principal"},
	/* fr */ {IDCLS_DONT_TRACE_MAIN_CPU_FR, "Ne pas tracer l'UCT principal"},
	/* hu */ {IDCLS_DONT_TRACE_MAIN_CPU_HU, "Fı CPU nyomkˆvetÈsÈnek tilt·sa"},
	/* it */ {IDCLS_DONT_TRACE_MAIN_CPU_IT, "Non tracciare la CPU principale"},
	/* ko */ {IDCLS_DONT_TRACE_MAIN_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_TRACE_MAIN_CPU_NL, "Traceer de hoofd CPU niet"},
	/* pl */ {IDCLS_DONT_TRACE_MAIN_CPU_PL, "Bez ∂ledzenia g≥Ûwnego CPU"},
	/* ru */ {IDCLS_DONT_TRACE_MAIN_CPU_RU, "Do not trace the main CPU"},
	/* sv */ {IDCLS_DONT_TRACE_MAIN_CPU_SV, "SpÂra inte huvudprocessorn"},
	/* tr */ {IDCLS_DONT_TRACE_MAIN_CPU_TR, "Ana CPU'yu izleme"},
#endif
	
	/* debug.c */
	/* en */ {IDCLS_TRACE_DRIVE0_CPU,    N_("Trace the drive0 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TRACE_DRIVE0_CPU_DA, "Trace processor i drev 0"},
	/* de */ {IDCLS_TRACE_DRIVE0_CPU_DE, "Laufwerk0 CPU verfolgen"},
	/* es */ {IDCLS_TRACE_DRIVE0_CPU_ES, "Rastrear la CPU de la unidad de disco 0"},
	/* fr */ {IDCLS_TRACE_DRIVE0_CPU_FR, "Tracer l'UCT du drive0"},
	/* hu */ {IDCLS_TRACE_DRIVE0_CPU_HU, "A 0-s lemezegysÈg CPU-j·nak nyomkˆvetÈse"},
	/* it */ {IDCLS_TRACE_DRIVE0_CPU_IT, "Traccia la CPU del drive0"},
	/* ko */ {IDCLS_TRACE_DRIVE0_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TRACE_DRIVE0_CPU_NL, "Traceer de CPU van drive 0/8"},
	/* pl */ {IDCLS_TRACE_DRIVE0_CPU_PL, "¶ledzenie CPU stacji0"},
	/* ru */ {IDCLS_TRACE_DRIVE0_CPU_RU, "Trace the drive0 CPU"},
	/* sv */ {IDCLS_TRACE_DRIVE0_CPU_SV, "SpÂra processor i diskettstation 0"},
	/* tr */ {IDCLS_TRACE_DRIVE0_CPU_TR, "S¸r¸c¸0 CPU'sunu izle"},
#endif
	
	/* debug.c */
	/* en */ {IDCLS_DONT_TRACE_DRIVE0_CPU,    N_("Do not trace the drive0 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_TRACE_DRIVE0_CPU_DA, "Trace ikke processor i drev 0"},
	/* de */ {IDCLS_DONT_TRACE_DRIVE0_CPU_DE, "Laufwerk0 CPU nicht verfolgen"},
	/* es */ {IDCLS_DONT_TRACE_DRIVE0_CPU_ES, "No rastrear la CPU de la unidad de disco 0"},
	/* fr */ {IDCLS_DONT_TRACE_DRIVE0_CPU_FR, "Ne pas tracer l'UCT du drive0"},
	/* hu */ {IDCLS_DONT_TRACE_DRIVE0_CPU_HU, "A 0-s lemezegysÈg CPU-ja nyomkˆvetÈsÈnek tilt·sa"},
	/* it */ {IDCLS_DONT_TRACE_DRIVE0_CPU_IT, "Non tracciare la CPU del drive0"},
	/* ko */ {IDCLS_DONT_TRACE_DRIVE0_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_TRACE_DRIVE0_CPU_NL, "Traceer de CPU van drive 0/8 niet"},
	/* pl */ {IDCLS_DONT_TRACE_DRIVE0_CPU_PL, "Bez ∂ledzenia CPU stacji0"},
	/* ru */ {IDCLS_DONT_TRACE_DRIVE0_CPU_RU, "Do not trace the drive0 CPU"},
	/* sv */ {IDCLS_DONT_TRACE_DRIVE0_CPU_SV, "SpÂra inte processor i diskettstation 0"},
	/* tr */ {IDCLS_DONT_TRACE_DRIVE0_CPU_TR, "S¸r¸c¸0 CPU'sunu izleme"},
#endif
	
	/* debug.c */
	/* en */ {IDCLS_TRACE_DRIVE1_CPU,    N_("Trace the drive1 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TRACE_DRIVE1_CPU_DA, "Trace processor i drev 1"},
	/* de */ {IDCLS_TRACE_DRIVE1_CPU_DE, "Laufwerk1 CPU verfolgen"},
	/* es */ {IDCLS_TRACE_DRIVE1_CPU_ES, "Rastrear la CPU de la unidad de disco 1"},
	/* fr */ {IDCLS_TRACE_DRIVE1_CPU_FR, "Tracer l'UCT du drive1"},
	/* hu */ {IDCLS_TRACE_DRIVE1_CPU_HU, "Az 1-es lemezegysÈg CPU-j·nak nyomkˆvetÈse"},
	/* it */ {IDCLS_TRACE_DRIVE1_CPU_IT, "Traccia la CPU del drive1"},
	/* ko */ {IDCLS_TRACE_DRIVE1_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TRACE_DRIVE1_CPU_NL, "Traceer de CPU van drive 1/9"},
	/* pl */ {IDCLS_TRACE_DRIVE1_CPU_PL, "¶ledzenie CPU stacji1"},
	/* ru */ {IDCLS_TRACE_DRIVE1_CPU_RU, "Trace the drive1 CPU"},
	/* sv */ {IDCLS_TRACE_DRIVE1_CPU_SV, "SpÂra processor i diskettstation 1"},
	/* tr */ {IDCLS_TRACE_DRIVE1_CPU_TR, "S¸r¸c¸1 CPU'sunu izle"},
#endif
	
	/* debug.c */
	/* en */ {IDCLS_DONT_TRACE_DRIVE1_CPU,    N_("Do not trace the drive1 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_TRACE_DRIVE1_CPU_DA, "Trace ikke processor i drev 1"},
	/* de */ {IDCLS_DONT_TRACE_DRIVE1_CPU_DE, "Laufwerk1 CPU nicht verfolgen"},
	/* es */ {IDCLS_DONT_TRACE_DRIVE1_CPU_ES, "No rastrear la CPU de la unidad de disco 1"},
	/* fr */ {IDCLS_DONT_TRACE_DRIVE1_CPU_FR, "Ne pas tracer l'UCT du drive1"},
	/* hu */ {IDCLS_DONT_TRACE_DRIVE1_CPU_HU, "Az 1-es lemezegysÈg CPU-ja nyomkˆvetÈsÈnek tilt·sa"},
	/* it */ {IDCLS_DONT_TRACE_DRIVE1_CPU_IT, "Non tracciare la CPU del drive1"},
	/* ko */ {IDCLS_DONT_TRACE_DRIVE1_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_TRACE_DRIVE1_CPU_NL, "Traceer de CPU van drive 1/9 niet"},
	/* pl */ {IDCLS_DONT_TRACE_DRIVE1_CPU_PL, "Bez ∂ledzenia CPU stacji1"},
	/* ru */ {IDCLS_DONT_TRACE_DRIVE1_CPU_RU, "Do not trace the drive1 CPU"},
	/* sv */ {IDCLS_DONT_TRACE_DRIVE1_CPU_SV, "SpÂra inte processor i diskettstation 1"},
	/* tr */ {IDCLS_DONT_TRACE_DRIVE1_CPU_TR, "S¸r¸c¸1 CPU'sunu izleme"},
#endif
	
#if DRIVE_NUM > 2
	/* debug.c */
	/* en */ {IDCLS_TRACE_DRIVE2_CPU,    N_("Trace the drive2 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TRACE_DRIVE2_CPU_DA, "Trace processor i drev 2"},
	/* de */ {IDCLS_TRACE_DRIVE2_CPU_DE, "Laufwerk2 CPU verfolgen"},
	/* es */ {IDCLS_TRACE_DRIVE2_CPU_ES, "Rastrear la CPU de la unidad de disco 2"},
	/* fr */ {IDCLS_TRACE_DRIVE2_CPU_FR, "Tracer l'UCT du drive2"},
	/* hu */ {IDCLS_TRACE_DRIVE2_CPU_HU, "A 2-es lemezegysÈg CPU-j·nak nyomkˆvetÈse"},
	/* it */ {IDCLS_TRACE_DRIVE2_CPU_IT, "Traccia la CPU del drive2"},
	/* ko */ {IDCLS_TRACE_DRIVE2_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TRACE_DRIVE2_CPU_NL, "Traceer de CPU van drive 2/10"},
	/* pl */ {IDCLS_TRACE_DRIVE2_CPU_PL, "¶ledzenie CPU stacji2"},
	/* ru */ {IDCLS_TRACE_DRIVE2_CPU_RU, "Trace the drive2 CPU"},
	/* sv */ {IDCLS_TRACE_DRIVE2_CPU_SV, "SpÂra processor i diskettstation 2"},
	/* tr */ {IDCLS_TRACE_DRIVE2_CPU_TR, "S¸r¸c¸2 CPU'sunu izle"},
#endif
	
	/* debug.c */
	/* en */ {IDCLS_DONT_TRACE_DRIVE2_CPU,    N_("Do not trace the drive2 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_TRACE_DRIVE2_CPU_DA, "Trace ikke processor i drev 2"},
	/* de */ {IDCLS_DONT_TRACE_DRIVE2_CPU_DE, "Laufwerk2 CPU nicht verfolgen"},
	/* es */ {IDCLS_DONT_TRACE_DRIVE2_CPU_ES, "No rastrear la CPU de la unidad de disco 2"},
	/* fr */ {IDCLS_DONT_TRACE_DRIVE2_CPU_FR, "Ne pas tracer l'UCT du drive2"},
	/* hu */ {IDCLS_DONT_TRACE_DRIVE2_CPU_HU, "A 2-es lemezegysÈg CPU-ja nyomkˆvetÈsÈnek tilt·sa"},
	/* it */ {IDCLS_DONT_TRACE_DRIVE2_CPU_IT, "Non tracciare la CPU del drive2"},
	/* ko */ {IDCLS_DONT_TRACE_DRIVE2_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_TRACE_DRIVE2_CPU_NL, "Traceer de CPU van drive 2/10 niet"},
	/* pl */ {IDCLS_DONT_TRACE_DRIVE2_CPU_PL, "Bez ∂ledzenia CPU stacji2"},
	/* ru */ {IDCLS_DONT_TRACE_DRIVE2_CPU_RU, "Do not trace the drive2 CPU"},
	/* sv */ {IDCLS_DONT_TRACE_DRIVE2_CPU_SV, "SpÂra inte processor i diskettstation 2"},
	/* tr */ {IDCLS_DONT_TRACE_DRIVE2_CPU_TR, "S¸r¸c¸2 CPU'sunu izleme"},
#endif
#endif
	
#if DRIVE_NUM > 3
	/* debug.c */
	/* en */ {IDCLS_TRACE_DRIVE3_CPU,    N_("Trace the drive3 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TRACE_DRIVE3_CPU_DA, "Trace processor i drev 3"},
	/* de */ {IDCLS_TRACE_DRIVE3_CPU_DE, "Laufwerk3 CPU verfolgen"},
	/* es */ {IDCLS_TRACE_DRIVE3_CPU_ES, "Rastrear la CPU de la unidad de disco 3"},
	/* fr */ {IDCLS_TRACE_DRIVE3_CPU_FR, "Tracer l'UCT du drive3"},
	/* hu */ {IDCLS_TRACE_DRIVE3_CPU_HU, "A 3-as lemezegysÈg CPU-j·nak nyomkˆvetÈse"},
	/* it */ {IDCLS_TRACE_DRIVE3_CPU_IT, "Traccia la CPU del drive3"},
	/* ko */ {IDCLS_TRACE_DRIVE3_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TRACE_DRIVE3_CPU_NL, "Traceer de CPU van drive 3/11"},
	/* pl */ {IDCLS_TRACE_DRIVE3_CPU_PL, "¶ledzenie CPU stacji3"},
	/* ru */ {IDCLS_TRACE_DRIVE3_CPU_RU, "Trace the drive3 CPU"},
	/* sv */ {IDCLS_TRACE_DRIVE3_CPU_SV, "SpÂra processor i diskettstation 3"},
	/* tr */ {IDCLS_TRACE_DRIVE3_CPU_TR, "S¸r¸c¸3 CPU'sunu izle"},
#endif
	
	/* debug.c */
	/* en */ {IDCLS_DONT_TRACE_DRIVE3_CPU,    N_("Do not trace the drive3 CPU")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_TRACE_DRIVE3_CPU_DA, "Trace ikke processor i drev 3"},
	/* de */ {IDCLS_DONT_TRACE_DRIVE3_CPU_DE, "Laufwerk3 CPU nicht verfolgen"},
	/* es */ {IDCLS_DONT_TRACE_DRIVE3_CPU_ES, "No rastrear la CPU de la unidad de disco 3"},
	/* fr */ {IDCLS_DONT_TRACE_DRIVE3_CPU_FR, "Ne pas tracer l'UCT du drive3"},
	/* hu */ {IDCLS_DONT_TRACE_DRIVE3_CPU_HU, "A 3-as lemezegysÈg CPU-ja nyomkˆvetÈsÈnek tilt·sa"},
	/* it */ {IDCLS_DONT_TRACE_DRIVE3_CPU_IT, "Non tracciare la CPU del drive3"},
	/* ko */ {IDCLS_DONT_TRACE_DRIVE3_CPU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_TRACE_DRIVE3_CPU_NL, "Traceer de CPU van drive 3/11 niet"},
	/* pl */ {IDCLS_DONT_TRACE_DRIVE3_CPU_PL, "Bez ∂ledzenia CPU stacji3"},
	/* ru */ {IDCLS_DONT_TRACE_DRIVE3_CPU_RU, "Do not trace the drive3 CPU"},
	/* sv */ {IDCLS_DONT_TRACE_DRIVE3_CPU_SV, "SpÂra inte processor i diskettstation 3"},
	/* tr */ {IDCLS_DONT_TRACE_DRIVE3_CPU_TR, "S¸r¸c¸3 CPU'sunu izleme"},
#endif
#endif
	
	/* debug.c */
	/* en */ {IDCLS_TRACE_MODE,    N_("Trace mode (0=normal 1=small 2=history)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_TRACE_MODE_DA, "Trace-tilstand (0=normal 1=lille 2=historik)"},
	/* de */ {IDCLS_TRACE_MODE_DE, "Verfolgung Modus (0=normal 1=klein 2=Geschichte)"},
	/* es */ {IDCLS_TRACE_MODE_ES, "Modo de rastreo (0=normal, 1=pequeÒo, 2=historial)"},
	/* fr */ {IDCLS_TRACE_MODE_FR, "Mode de trace (0=normal 1=petit 2=historique)"},
	/* hu */ {IDCLS_TRACE_MODE_HU, "NyomkˆvetÈsi mÛd (0=norm·l 1=kicsi 2=elızmÈnyek)"},
	/* it */ {IDCLS_TRACE_MODE_IT, "Modalit‡ di tracciamento (0=normale 1=piccola 2=storica)"},
	/* ko */ {IDCLS_TRACE_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_TRACE_MODE_NL, "Traceermodus (0=normaal 1=klein 2=geschiedenis"},
	/* pl */ {IDCLS_TRACE_MODE_PL, "Tryb ∂ledzenia (0=zwyk≥e 1=ma≥e 2=w historii)"},
	/* ru */ {IDCLS_TRACE_MODE_RU, "Trace mode (0=normal 1=small 2=history)"},
	/* sv */ {IDCLS_TRACE_MODE_SV, "SpÂrningsl‰ge (0=normal 1=liten 2=historik)"},
	/* tr */ {IDCLS_TRACE_MODE_TR, "›zleme modu (0=normal 1=k¸Á¸k 2=tarihÁe)"},
#endif
#endif
	
	/* event.c */
	/* en */ {IDCLS_PLAYBACK_RECORDED_EVENTS,    N_("Playback recorded events")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PLAYBACK_RECORDED_EVENTS_DA, "Afspil hÊndelsesoptagelse"},
	/* de */ {IDCLS_PLAYBACK_RECORDED_EVENTS_DE, "Wiedergabe von aufgenommener Ereignisse"},
	/* es */ {IDCLS_PLAYBACK_RECORDED_EVENTS_ES, "Reproducir eventos grabados"},
	/* fr */ {IDCLS_PLAYBACK_RECORDED_EVENTS_FR, "Lire les ÈvÈnements enregistrÈs"},
	/* hu */ {IDCLS_PLAYBACK_RECORDED_EVENTS_HU, "A felvett esemÈnyek visszaj·tsz·sa"},
	/* it */ {IDCLS_PLAYBACK_RECORDED_EVENTS_IT, "Riproduzione eventi registrati"},
	/* ko */ {IDCLS_PLAYBACK_RECORDED_EVENTS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PLAYBACK_RECORDED_EVENTS_NL, "Afspelen opgenomen gebeurtenissen"},
	/* pl */ {IDCLS_PLAYBACK_RECORDED_EVENTS_PL, "OdtwÛrz zapisane zdarzenia"},
	/* ru */ {IDCLS_PLAYBACK_RECORDED_EVENTS_RU, "Playback recorded events"},
	/* sv */ {IDCLS_PLAYBACK_RECORDED_EVENTS_SV, "Spela upp inspelade h‰ndelser"},
	/* tr */ {IDCLS_PLAYBACK_RECORDED_EVENTS_TR, "Kay˝ttan y¸r¸tme kaydedilmi˛ olaylar˝"},
#endif
	
	/* monitor.c */
	/* en */ {IDCLS_EXECUTE_MONITOR_FROM_FILE,    N_("Execute monitor commands from file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_DA, "Udf¯r monitorkommandoer fra fil"},
	/* de */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_DE, "Monitor Kommandos aus Datei ausf¸hren"},
	/* es */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_ES, "Ejecutar comandos del monitor desde fichero"},
	/* fr */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_FR, "ExÈcuter des commandes moniteur depuis un fichier"},
	/* hu */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_HU, "Monitorprogram parancsok futtat·sa f·jlbÛl"},
	/* it */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_IT, "Esegui i comandi del monitor da un file"},
	/* ko */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_NL, "Uitvoeren van commandos uit bestand"},
	/* pl */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_PL, "Wykonaj polecenia monitora z pliku"},
	/* ru */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_RU, "Execute monitor commands from file"},
	/* sv */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_SV, "Exekvera monitorkommandon frÂn fil"},
	/* tr */ {IDCLS_EXECUTE_MONITOR_FROM_FILE_TR, "Dosyadan monitˆr komutlar˝ Áal˝˛t˝r"},
#endif
	
	/* monitor.c */
	/* en */ {IDCLS_SET_INITIAL_BREAKPOINT,    N_("Set an initial breakpoint for the monitor")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_INITIAL_BREAKPOINT_DA, "SÊt et initielt breakpoint for monitoren"},
	/* de */ {IDCLS_SET_INITIAL_BREAKPOINT_DE, "Setze initialen Breakpoint f¸r Monitor"},
	/* es */ {IDCLS_SET_INITIAL_BREAKPOINT_ES, "Seleccionar un punto inicial de ruptura para el monitor"},
	/* fr */ {IDCLS_SET_INITIAL_BREAKPOINT_FR, "RÈgler un point díarrÍt initial pour le moniteur"},
	/* hu */ {IDCLS_SET_INITIAL_BREAKPOINT_HU, "Kezdeti tˆrÈspont megad·sa a monitorprogramnak"},
	/* it */ {IDCLS_SET_INITIAL_BREAKPOINT_IT, "Imposta un breakpoint iniziale per il monitor"},
	/* ko */ {IDCLS_SET_INITIAL_BREAKPOINT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_INITIAL_BREAKPOINT_NL, "Zet een beginnende breakpunt voor de monitor"},
	/* pl */ {IDCLS_SET_INITIAL_BREAKPOINT_PL, "Okre∂l pocz±tkowy punkt wstrzymania w monitorze"},
	/* ru */ {IDCLS_SET_INITIAL_BREAKPOINT_RU, "Set an initial breakpoint for the monitor"},
	/* sv */ {IDCLS_SET_INITIAL_BREAKPOINT_SV, "S‰tt en ursprunglig brytpunkt fˆr monitorn"},
	/* tr */ {IDCLS_SET_INITIAL_BREAKPOINT_TR, "Monitˆr iÁin dahili bir kesme noktas˝ ayarla"},
#endif
	
	/* monitor_network.c */
	/* en */ {IDCLS_ENABLE_REMOTE_MONITOR,    N_("Enable remote monitor")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_REMOTE_MONITOR_DA, "AktivÈr fjern-monitor"},
	/* de */ {IDCLS_ENABLE_REMOTE_MONITOR_DE, "Monitor Fernsteuerung aktivieren"},
	/* es */ {IDCLS_ENABLE_REMOTE_MONITOR_ES, "Permitir monitor remoto"},
	/* fr */ {IDCLS_ENABLE_REMOTE_MONITOR_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_REMOTE_MONITOR_HU, "T·voli monitor engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_REMOTE_MONITOR_IT, "Attiva monitor remoto"},
	/* ko */ {IDCLS_ENABLE_REMOTE_MONITOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_REMOTE_MONITOR_NL, "Activeer monitor afstandsbediening"},
	/* pl */ {IDCLS_ENABLE_REMOTE_MONITOR_PL, "W≥±cz zdalny monitor"},
	/* ru */ {IDCLS_ENABLE_REMOTE_MONITOR_RU, "Enable remote monitor"},
	/* sv */ {IDCLS_ENABLE_REMOTE_MONITOR_SV, "Aktivera fj‰rrmonitor"},
	/* tr */ {IDCLS_ENABLE_REMOTE_MONITOR_TR, "Uzak monitˆr¸ aktif et"},
#endif
	
	/* monitor_network.c */
	/* en */ {IDCLS_DISABLE_REMOTE_MONITOR,    N_("Disable remote monitor")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_REMOTE_MONITOR_DA, "DeaktivÈr fjern-monitor"},
	/* de */ {IDCLS_DISABLE_REMOTE_MONITOR_DE, "Monitor Fernsteuerung deaktivieren"},
	/* es */ {IDCLS_DISABLE_REMOTE_MONITOR_ES, "Deshabilitar monitor remoto"},
	/* fr */ {IDCLS_DISABLE_REMOTE_MONITOR_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_REMOTE_MONITOR_HU, "T·voli monitor tilt·sa"},
	/* it */ {IDCLS_DISABLE_REMOTE_MONITOR_IT, "Disattiva monitor remoto"},
	/* ko */ {IDCLS_DISABLE_REMOTE_MONITOR_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_REMOTE_MONITOR_NL, "afstandsbediening monitor uitschakelen"},
	/* pl */ {IDCLS_DISABLE_REMOTE_MONITOR_PL, "Wy≥±cz zdalny monitor"},
	/* ru */ {IDCLS_DISABLE_REMOTE_MONITOR_RU, "Disable remote monitor"},
	/* sv */ {IDCLS_DISABLE_REMOTE_MONITOR_SV, "Inaktivera fj‰rrmonitor"},
	/* tr */ {IDCLS_DISABLE_REMOTE_MONITOR_TR, "Uzak monitˆr¸ pasifle˛tir"},
#endif
	
	/* monitor_network.c */
	/* en */ {IDCLS_REMOTE_MONITOR_ADDRESS,    N_("The local address the remote monitor should bind to")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_REMOTE_MONITOR_ADDRESS_DA, "Lokal adresse fjern-monitoren skal binde til"},
	/* de */ {IDCLS_REMOTE_MONITOR_ADDRESS_DE, "Lokale Adresse f¸r die Monitorfernsteuerung"},
	/* es */ {IDCLS_REMOTE_MONITOR_ADDRESS_ES, "DirecciÛn del monitor remoto al que se debe unir"},
	/* fr */ {IDCLS_REMOTE_MONITOR_ADDRESS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_REMOTE_MONITOR_ADDRESS_HU, "A helyi cÌm, amelyet a monitorprogram lefoglal"},
	/* it */ {IDCLS_REMOTE_MONITOR_ADDRESS_IT, "Indirizzo locale a cui il monitor remoto dovrebbe collegarsi"},
	/* ko */ {IDCLS_REMOTE_MONITOR_ADDRESS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_REMOTE_MONITOR_ADDRESS_NL, "Lokaal adres waar de afstandsbediening voor de monitor aan gebonden moet worden"},
	/* pl */ {IDCLS_REMOTE_MONITOR_ADDRESS_PL, "Lokalny adres, z ktÛrym ma siÍ po≥±czyÊ zdalny monitor"},
	/* ru */ {IDCLS_REMOTE_MONITOR_ADDRESS_RU, "The local address the remote monitor should bind to"},
	/* sv */ {IDCLS_REMOTE_MONITOR_ADDRESS_SV, "Lokal adress fˆr fj‰rrmonitor att ansluta till"},
	/* tr */ {IDCLS_REMOTE_MONITOR_ADDRESS_TR, "Uzak monitˆr¸n balanmas˝ gereken lokal adres"},
#endif
	
	/* fliplist.c */
	/* en */ {IDCLS_SPECIFY_FLIP_LIST_NAME,    N_("Specify name of the flip list file image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_FLIP_LIST_NAME_DA, "Angiv navn pÂ bladreliste"},
	/* de */ {IDCLS_SPECIFY_FLIP_LIST_NAME_DE, "Namen f¸r Fliplist Datei definieren"},
	/* es */ {IDCLS_SPECIFY_FLIP_LIST_NAME_ES, "Especificar nombre fichero lista de intercambio imagenes"},
	/* fr */ {IDCLS_SPECIFY_FLIP_LIST_NAME_FR, "SpÈcifier le nom de l'image du fichier de groupement de disques"},
	/* hu */ {IDCLS_SPECIFY_FLIP_LIST_NAME_HU, "Adja meg a lemezlista f·jl nevÈt"},
	/* it */ {IDCLS_SPECIFY_FLIP_LIST_NAME_IT, "Specifica il nome immagine del file della flip list"},
	/* ko */ {IDCLS_SPECIFY_FLIP_LIST_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_FLIP_LIST_NAME_NL, "Geef de naam van het fliplijstbestand"},
	/* pl */ {IDCLS_SPECIFY_FLIP_LIST_NAME_PL, "Okre∂l nazwÍ pliku obrazu listy podmiany no∂nikÛw"},
	/* ru */ {IDCLS_SPECIFY_FLIP_LIST_NAME_RU, "Specify name of the flip list file image"},
	/* sv */ {IDCLS_SPECIFY_FLIP_LIST_NAME_SV, "Ange namn pÂ vallistefilavbildningen"},
	/* tr */ {IDCLS_SPECIFY_FLIP_LIST_NAME_TR, "S˝ralama listesi dosya imaj˝ ismi belirt"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS,    N_("Show a list of the available options and exit normally")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_DA, "Vis en liste over tilgÊngelige parametre og afslut"},
	/* de */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_DE, "Liste von verf¸gbaren Optionen zeigen und beenden"},
	/* es */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_ES, "Muestra lista de las opcciones disponibles al salir normalmente"},
	/* fr */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_FR, "Montrer une liste des options disponibles et terminer normalement"},
	/* hu */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_HU, "Kilist·zza a lehetsÈges opciÛkat Ès kilÈp"},
	/* it */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_IT, "Mostra la lista delle opzioni disponibili ed esce"},
	/* ko */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_NL, "Toon een lijst van de beschikbare opties en exit zoals normaal"},
	/* pl */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_PL, "Pokaø listÍ dostÍpnych poleceÒ i normalnie wyjdº"},
	/* ru */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_RU, "Show a list of the available options and exit normally"},
	/* sv */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_SV, "Visa lista ˆver tillg‰ngliga flaggor och avsluta normalt"},
	/* tr */ {IDCLS_SHOW_COMMAND_LINE_OPTIONS_TR, "Mevcut seÁeneklerin listesini gˆster ve normal Á˝k"},
#endif
	
#if (!defined  __OS2__ && !defined __BEOS__)
	/* initcmdline.c */
	/* en */ {IDCLS_CONSOLE_MODE,    N_("Console mode (for music playback)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_CONSOLE_MODE_DA, "Konsoltilstand (for musikafspilning)"},
	/* de */ {IDCLS_CONSOLE_MODE_DE, "Konsolenmodus (f¸r Musikwiedergabe)"},
	/* es */ {IDCLS_CONSOLE_MODE_ES, "Modo consola (para reproducciÛn m˙sica)"},
	/* fr */ {IDCLS_CONSOLE_MODE_FR, "Mode console (pour l'Ècoute de musique)"},
	/* hu */ {IDCLS_CONSOLE_MODE_HU, "Konzol mÛd (zene lej·tsz·shoz)"},
	/* it */ {IDCLS_CONSOLE_MODE_IT, "Modalit‡ console (per la riproduzione musicale)"},
	/* ko */ {IDCLS_CONSOLE_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_CONSOLE_MODE_NL, "Consolemodus (voor afspelen voor muziek)"},
	/* pl */ {IDCLS_CONSOLE_MODE_PL, "Tryb konsolowy (do odtwarzania muzyki)"},
	/* ru */ {IDCLS_CONSOLE_MODE_RU, "Console mode (for music playback)"},
	/* sv */ {IDCLS_CONSOLE_MODE_SV, "Konsoll‰ge (fˆr musikspelning)"},
	/* tr */ {IDCLS_CONSOLE_MODE_TR, "Konsol modu (m¸zik Áalmak iÁin)"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ALLOW_CORE_DUMPS,    N_("Allow production of core dumps")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ALLOW_CORE_DUMPS_DA, "Tillad generering af core-dumps"},
	/* de */ {IDCLS_ALLOW_CORE_DUMPS_DE, "Core Dumps ermˆglichen"},
	/* es */ {IDCLS_ALLOW_CORE_DUMPS_ES, "Permitir producciÛn volcados de nucleo"},
	/* fr */ {IDCLS_ALLOW_CORE_DUMPS_FR, "Permettre la production de \"core dumps\""},
	/* hu */ {IDCLS_ALLOW_CORE_DUMPS_HU, "Core dump kÈszÌtÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ALLOW_CORE_DUMPS_IT, "Consente la produzione di core dump"},
	/* ko */ {IDCLS_ALLOW_CORE_DUMPS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ALLOW_CORE_DUMPS_NL, "Maken van core dumps toestaan"},
	/* pl */ {IDCLS_ALLOW_CORE_DUMPS_PL, "PozwÛl tworzyÊ zrzuty rdzenia"},
	/* ru */ {IDCLS_ALLOW_CORE_DUMPS_RU, "Allow production of core dumps"},
	/* sv */ {IDCLS_ALLOW_CORE_DUMPS_SV, "TillÂt skapa minnesutskrift"},
	/* tr */ {IDCLS_ALLOW_CORE_DUMPS_TR, "Bellek durumunun kay˝tlar˝n˝n ¸retilmesine izin ver"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_DONT_ALLOW_CORE_DUMPS,    N_("Do not produce core dumps")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_ALLOW_CORE_DUMPS_DA, "Lav ikke core-dumps"},
	/* de */ {IDCLS_DONT_ALLOW_CORE_DUMPS_DE, "Core Dumps verhindern"},
	/* es */ {IDCLS_DONT_ALLOW_CORE_DUMPS_ES, "No permitir producciÛn volcados de nucleo"},
	/* fr */ {IDCLS_DONT_ALLOW_CORE_DUMPS_FR, "Ne pas produire de \"core dumps\""},
	/* hu */ {IDCLS_DONT_ALLOW_CORE_DUMPS_HU, "Core dump kÈszÌtÈs tilt·sa"},
	/* it */ {IDCLS_DONT_ALLOW_CORE_DUMPS_IT, "Non produce core dump"},
	/* ko */ {IDCLS_DONT_ALLOW_CORE_DUMPS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_ALLOW_CORE_DUMPS_NL, "Maken van core dumps niet toestaan"},
	/* pl */ {IDCLS_DONT_ALLOW_CORE_DUMPS_PL, "Nie twÛrz zrzutÛw rdzenia"},
	/* ru */ {IDCLS_DONT_ALLOW_CORE_DUMPS_RU, "Do not produce core dumps"},
	/* sv */ {IDCLS_DONT_ALLOW_CORE_DUMPS_SV, "Skapa inte minnesutskrift"},
	/* tr */ {IDCLS_DONT_ALLOW_CORE_DUMPS_TR, "Bellek durumunun kay˝tlar˝n˝ ¸retme"},
#endif
	
#else
	
	/* initcmdline.c */
	/* en */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER,    N_("Don't call exception handler")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_DA, "Kald ikke exception-handler"},
	/* de */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_DE, "Ausnahmebehandlung vermeiden"},
	/* es */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_ES, "No llamar al manipulador de excepciones"},
	/* fr */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_FR, "Ne pas utiliser l'assistant d'exception"},
	/* hu */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_HU, "Ne hÌvja a kivÈtel kezelıt"},
	/* it */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_IT, "Richiama il gestore delle eccezioni"},
	/* ko */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_NL, "Geen gebruik maken van de exception handler"},
	/* pl */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_PL, "Nie zajmuj siÍ wyj±tkami"},
	/* ru */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_RU, "Don't call exception handler"},
	/* sv */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_SV, "Anropa inte undantagshanterare"},
	/* tr */ {IDCLS_DONT_CALL_EXCEPTION_HANDLER_TR, "Kural d˝˛˝ i˛leyiciyi Áa˝rma"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_CALL_EXCEPTION_HANDLER,    N_("Call exception handler (default)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_CALL_EXCEPTION_HANDLER_DA, "Kald exception-handler (standard)"},
	/* de */ {IDCLS_CALL_EXCEPTION_HANDLER_DE, "Ausnahmebehandlung aktivieren (Default)"},
	/* es */ {IDCLS_CALL_EXCEPTION_HANDLER_ES, "Llamar al manipulador de excepciones (por defecto)"},
	/* fr */ {IDCLS_CALL_EXCEPTION_HANDLER_FR, "Utiliser l'assistant d'exception (par dÈfaut)"},
	/* hu */ {IDCLS_CALL_EXCEPTION_HANDLER_HU, "KivÈtel kezelı hÌv·sa (alapÈrtelmezÈs)"},
	/* it */ {IDCLS_CALL_EXCEPTION_HANDLER_IT, "Richiama il gestore delle eccezioni (predefinito)"},
	/* ko */ {IDCLS_CALL_EXCEPTION_HANDLER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_CALL_EXCEPTION_HANDLER_NL, "Gebruik maken van de exception handler (standaard)"},
	/* pl */ {IDCLS_CALL_EXCEPTION_HANDLER_PL, "Zajmij siÍ wyj±tkami (domy∂lnie)"},
	/* ru */ {IDCLS_CALL_EXCEPTION_HANDLER_RU, "Call exception handler (default)"},
	/* sv */ {IDCLS_CALL_EXCEPTION_HANDLER_SV, "Anropa undantagshanterare (standard)"},
	/* tr */ {IDCLS_CALL_EXCEPTION_HANDLER_TR, "Kural d˝˛˝ i˛leyiciyi Áa˝r (varsay˝lan)"},
#endif
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_RESTORE_DEFAULT_SETTINGS,    N_("Restore default settings")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_RESTORE_DEFAULT_SETTINGS_DA, "Gendan standardindstillinger"},
	/* de */ {IDCLS_RESTORE_DEFAULT_SETTINGS_DE, "Standard Einstellungen wiederherstellen"},
	/* es */ {IDCLS_RESTORE_DEFAULT_SETTINGS_ES, "Restaurar valores por defecto"},
	/* fr */ {IDCLS_RESTORE_DEFAULT_SETTINGS_FR, "RÈtablir les paramËtres par dÈfaut"},
	/* hu */ {IDCLS_RESTORE_DEFAULT_SETTINGS_HU, "AlapÈrtelmezÈs vissza·llÌt·sa"},
	/* it */ {IDCLS_RESTORE_DEFAULT_SETTINGS_IT, "Ripristina impostazioni predefinite"},
	/* ko */ {IDCLS_RESTORE_DEFAULT_SETTINGS_KO, "µ∆˙∆Æ º≥¡§ ∫πø¯Ω√≈∞±‚"},
	/* nl */ {IDCLS_RESTORE_DEFAULT_SETTINGS_NL, "Herstel standaard instellingen"},
	/* pl */ {IDCLS_RESTORE_DEFAULT_SETTINGS_PL, "PrzywrÛÊ domy∂lne ustawienia"},
	/* ru */ {IDCLS_RESTORE_DEFAULT_SETTINGS_RU, "≤ﬁ··‚–›ﬁ“ÿ‚Ï ›–·‚‡ﬁŸ⁄ÿ ﬂﬁ „‹ﬁ€Á–›ÿÓ"},
	/* sv */ {IDCLS_RESTORE_DEFAULT_SETTINGS_SV, "≈terst‰ll fˆrvalda inst‰llningar"},
	/* tr */ {IDCLS_RESTORE_DEFAULT_SETTINGS_TR, "Varsay˝lan ayarlar˝ geri y¸kle"},
#endif
	
	/* initcmdline.c, c64/cart/mmcreplay.c */
	/* en */ {IDCLS_P_FILE,    N_("<filename>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_FILE_DA, "<filnavn>"},
	/* de */ {IDCLS_P_FILE_DE, "<Dateiname>"},
	/* es */ {IDCLS_P_FILE_ES, "<Nombre fichero>"},
	/* fr */ {IDCLS_P_FILE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_FILE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_FILE_IT, "<nome file>"},
	/* ko */ {IDCLS_P_FILE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_FILE_NL, "<bestandsnaam>"},
	/* pl */ {IDCLS_P_FILE_PL, "<filename>"},
	/* ru */ {IDCLS_P_FILE_RU, "<ÿ‹Ô ‰–Ÿ€–>"},
	/* sv */ {IDCLS_P_FILE_SV, "<filnamn>"},
	/* tr */ {IDCLS_P_FILE_TR, "<dosyaismi>"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_SPECIFY_CONFIG_FILE,    N_("Specify config file")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_CONFIG_FILE_DA, "Angiv konfigurationsfil"},
	/* de */ {IDCLS_SPECIFY_CONFIG_FILE_DE, "Konfigurationsdateiname definieren"},
	/* es */ {IDCLS_SPECIFY_CONFIG_FILE_ES, "Especificar fichero de configuraciÛn"},
	/* fr */ {IDCLS_SPECIFY_CONFIG_FILE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_CONFIG_FILE_HU, "Adja meg a konfigur·ciÛs f·jl nevÈt"},
	/* it */ {IDCLS_SPECIFY_CONFIG_FILE_IT, "Specifica il nome del file di configurazione"},
	/* ko */ {IDCLS_SPECIFY_CONFIG_FILE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_CONFIG_FILE_NL, "Geef configuratie bestandsnaam"},
	/* pl */ {IDCLS_SPECIFY_CONFIG_FILE_PL, "Okre∂l plik konfiguracji"},
	/* ru */ {IDCLS_SPECIFY_CONFIG_FILE_RU, "Specify config file"},
	/* sv */ {IDCLS_SPECIFY_CONFIG_FILE_SV, "Ange inst‰llningsfil"},
	/* tr */ {IDCLS_SPECIFY_CONFIG_FILE_TR, "Konfig¸rasyon dosyas˝n˝ belirt"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ATTACH_AND_AUTOSTART,    N_("Attach and autostart tape/disk image <name>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_AND_AUTOSTART_DA, "Tilslut og autostart bÂnd-/disk-image <navn>"},
	/* de */ {IDCLS_ATTACH_AND_AUTOSTART_DE, "Einlegen und Autostart Disk/Band Image Datei <Name>"},
	/* es */ {IDCLS_ATTACH_AND_AUTOSTART_ES, "Insertar y autoarrancar imagen de cinta/disco <nombre>"},
	/* fr */ {IDCLS_ATTACH_AND_AUTOSTART_FR, "InsÈrer et dÈmarrer l'image de disque/datassette <nom>"},
	/* hu */ {IDCLS_ATTACH_AND_AUTOSTART_HU, "<nÈv> lemez/szalag kÈpm·s csatol·sa Ès automatikus elindÌt·sa"},
	/* it */ {IDCLS_ATTACH_AND_AUTOSTART_IT, "Seleziona ed avvia l'immagine di una cassetta/disco <nome>"},
	/* ko */ {IDCLS_ATTACH_AND_AUTOSTART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_AND_AUTOSTART_NL, "Koppel en autostart een tape/diskbestand <naam>"},
	/* pl */ {IDCLS_ATTACH_AND_AUTOSTART_PL, "Zamontuj i automatycznie uruchom obraz ta∂my lub dysku <nazwa>"},
	/* ru */ {IDCLS_ATTACH_AND_AUTOSTART_RU, "Attach and autostart tape/disk image <name>"},
	/* sv */ {IDCLS_ATTACH_AND_AUTOSTART_SV, "Anslut och starta band-/diskettavbildning <namn>"},
	/* tr */ {IDCLS_ATTACH_AND_AUTOSTART_TR, "Teyp/Disk imaj˝ <isim> yerle˛tir ve otomatik ba˛lat"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ATTACH_AND_AUTOLOAD,    N_("Attach and autoload tape/disk image <name>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_AND_AUTOLOAD_DA, "Tilslut og lÊs bÂnd-/disk-image <navn>"},
	/* de */ {IDCLS_ATTACH_AND_AUTOLOAD_DE, "Einlegen und Autoload Disk/Band Image Datei <Name>"},
	/* es */ {IDCLS_ATTACH_AND_AUTOLOAD_ES, "Insertar y autocargar imagen de cinta/disco <nombre>"},
	/* fr */ {IDCLS_ATTACH_AND_AUTOLOAD_FR, "InsÈrer et charger l'image de disque/datassette <nom>"},
	/* hu */ {IDCLS_ATTACH_AND_AUTOLOAD_HU, "<nÈv> lemez/szalag kÈpm·s csatol·sa Ès automatikus betˆltÈse"},
	/* it */ {IDCLS_ATTACH_AND_AUTOLOAD_IT, "Seleziona e carica l'immagine di una cassetta/disco <nome>"},
	/* ko */ {IDCLS_ATTACH_AND_AUTOLOAD_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_AND_AUTOLOAD_NL, "Koppel en autolaad een tape-/diskbestand <naam>"},
	/* pl */ {IDCLS_ATTACH_AND_AUTOLOAD_PL, "Zamontuj i automatycznie wczytaj obraz ta∂my lub dysku <nazwa>"},
	/* ru */ {IDCLS_ATTACH_AND_AUTOLOAD_RU, "Attach and autoload tape/disk image <name>"},
	/* sv */ {IDCLS_ATTACH_AND_AUTOLOAD_SV, "Anslut och l‰s in band-/diskettavbildning <namn>"},
	/* tr */ {IDCLS_ATTACH_AND_AUTOLOAD_TR, "Teyp/Disk imaj˝ <isim> yerle˛tir ve otomatik y¸kle"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ATTACH_AS_TAPE,    N_("Attach <name> as a tape image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_AS_TAPE_DA, "Tilslut <navn> som bÂnd-image"},
	/* de */ {IDCLS_ATTACH_AS_TAPE_DE, "Image Datei <Name> einlegen"},
	/* es */ {IDCLS_ATTACH_AS_TAPE_ES, "Insertar <nombre> como imagen de cinta"},
	/* fr */ {IDCLS_ATTACH_AS_TAPE_FR, "InsÈrer <nom> comme image de datassette"},
	/* hu */ {IDCLS_ATTACH_AS_TAPE_HU, "<nÈv> szalag kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_AS_TAPE_IT, "Seleziona <nome> come un'immagine di una cassetta"},
	/* ko */ {IDCLS_ATTACH_AS_TAPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_AS_TAPE_NL, "Koppel <naam> als een tapebestand"},
	/* pl */ {IDCLS_ATTACH_AS_TAPE_PL, "Zamontuj <nazwa> jako obraz ta∂my"},
	/* ru */ {IDCLS_ATTACH_AS_TAPE_RU, "Attach <name> as a tape image"},
	/* sv */ {IDCLS_ATTACH_AS_TAPE_SV, "Anslut <namn> som bandavbildning"},
	/* tr */ {IDCLS_ATTACH_AS_TAPE_TR, "Teyp imaj˝ olarak <isim> yerle˛tir"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ATTACH_AS_DISK_8,    N_("Attach <name> as a disk image in drive #8")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_AS_DISK_8_DA, "Tilslut <navn> som disk-image i enhed #8"},
	/* de */ {IDCLS_ATTACH_AS_DISK_8_DE, "Image Datei <Name> im Laufwerk #8 einlegen"},
	/* es */ {IDCLS_ATTACH_AS_DISK_8_ES, "Insertar <nombre> como imagen disco en unidad disco #8"},
	/* fr */ {IDCLS_ATTACH_AS_DISK_8_FR, "InsÈrer <nom> comme image de disque dans le lecteur #8"},
	/* hu */ {IDCLS_ATTACH_AS_DISK_8_HU, "<nÈv> lemezkÈpm·s csatol·sa #8-as egysÈgkÈnt"},
	/* it */ {IDCLS_ATTACH_AS_DISK_8_IT, "Seleziona <nome> come un'immagine di un disco nel drive #8"},
	/* ko */ {IDCLS_ATTACH_AS_DISK_8_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_AS_DISK_8_NL, "Koppel <naam> aan als een schijfbestand in drive #8"},
	/* pl */ {IDCLS_ATTACH_AS_DISK_8_PL, "Zamontuj <nazwa> jako obraz dyskietki w stacji #8"},
	/* ru */ {IDCLS_ATTACH_AS_DISK_8_RU, "Attach <name> as a disk image in drive #8"},
	/* sv */ {IDCLS_ATTACH_AS_DISK_8_SV, "Anslut <namn> som diskettavbildning i enhet 8"},
	/* tr */ {IDCLS_ATTACH_AS_DISK_8_TR, "S¸r¸c¸ #8 disk imaj˝ olarak <isim> yerle˛tir"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ATTACH_AS_DISK_9,    N_("Attach <name> as a disk image in drive #9")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_AS_DISK_9_DA, "Tilslut <navn> som disk-image i enhed #9"},
	/* de */ {IDCLS_ATTACH_AS_DISK_9_DE, "Image Datei <Name> im Laufwerk #9 einlegen"},
	/* es */ {IDCLS_ATTACH_AS_DISK_9_ES, "Insertar <nombre> como imagen disco en unidad disco #9"},
	/* fr */ {IDCLS_ATTACH_AS_DISK_9_FR, "InsÈrer <nom> comme image de disque dans le lecteur #9"},
	/* hu */ {IDCLS_ATTACH_AS_DISK_9_HU, "<nÈv> lemezkÈpm·s csatol·sa #9-es egysÈgkÈnt"},
	/* it */ {IDCLS_ATTACH_AS_DISK_9_IT, "Seleziona <nome> come un'immagine di un disco nel drive #9"},
	/* ko */ {IDCLS_ATTACH_AS_DISK_9_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_AS_DISK_9_NL, "Koppel <naam> aan als een schijfbestand in drive #9"},
	/* pl */ {IDCLS_ATTACH_AS_DISK_9_PL, "Zamontuj <nazwa> jako obraz dyskietki w stacji #9"},
	/* ru */ {IDCLS_ATTACH_AS_DISK_9_RU, "Attach <name> as a disk image in drive #9"},
	/* sv */ {IDCLS_ATTACH_AS_DISK_9_SV, "Anslut <namn> som diskettavbildning i enhet 9"},
	/* tr */ {IDCLS_ATTACH_AS_DISK_9_TR, "S¸r¸c¸ #9 disk imaj˝ olarak <isim> yerle˛tir"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ATTACH_AS_DISK_10,    N_("Attach <name> as a disk image in drive #10")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_AS_DISK_10_DA, "Tilslut <navn> som disk-image i enhed #10"},
	/* de */ {IDCLS_ATTACH_AS_DISK_10_DE, "Image Datei <Name> im Laufwerk #10 einlegen"},
	/* es */ {IDCLS_ATTACH_AS_DISK_10_ES, "Insertar <nombre> como imagen disco en unidad disco #10"},
	/* fr */ {IDCLS_ATTACH_AS_DISK_10_FR, "InsÈrer <nom> comme image de disque dans le lecteur #10"},
	/* hu */ {IDCLS_ATTACH_AS_DISK_10_HU, "<nÈv> lemezkÈpm·s csatol·sa #10-es egysÈgkÈnt"},
	/* it */ {IDCLS_ATTACH_AS_DISK_10_IT, "Seleziona <nome> come un'immagine di un disco nel drive #10"},
	/* ko */ {IDCLS_ATTACH_AS_DISK_10_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_AS_DISK_10_NL, "Koppel <naam> aan als een schijfbestand in drive #10"},
	/* pl */ {IDCLS_ATTACH_AS_DISK_10_PL, "Zamontuj <nazwa> jako obraz dyskietki w stacji #10"},
	/* ru */ {IDCLS_ATTACH_AS_DISK_10_RU, "Attach <name> as a disk image in drive #10"},
	/* sv */ {IDCLS_ATTACH_AS_DISK_10_SV, "Anslut <namn> som diskettavbildning i enhet 10"},
	/* tr */ {IDCLS_ATTACH_AS_DISK_10_TR, "S¸r¸c¸ #10 disk imaj˝ olarak <isim> yerle˛tir"},
#endif
	
	/* initcmdline.c */
	/* en */ {IDCLS_ATTACH_AS_DISK_11,    N_("Attach <name> as a disk image in drive #11")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_AS_DISK_11_DA, "Tilslut <navn> som disk-image i enhed #11"},
	/* de */ {IDCLS_ATTACH_AS_DISK_11_DE, "Image Datei <Name> im Laufwerk #11 einlegen"},
	/* es */ {IDCLS_ATTACH_AS_DISK_11_ES, "Insertar <nombre> como imagen disco en unidad disco #11"},
	/* fr */ {IDCLS_ATTACH_AS_DISK_11_FR, "InsÈrer <nom> comme image de disque dans le lecteur #11"},
	/* hu */ {IDCLS_ATTACH_AS_DISK_11_HU, "<nÈv> lemezkÈpm·s csatol·sa #11-es egysÈgkÈnt"},
	/* it */ {IDCLS_ATTACH_AS_DISK_11_IT, "Seleziona <nome> come un'immagine di un disco nel drive #11"},
	/* ko */ {IDCLS_ATTACH_AS_DISK_11_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_AS_DISK_11_NL, "Koppel <naam> aan als een schijfbestand in drive #11"},
	/* pl */ {IDCLS_ATTACH_AS_DISK_11_PL, "Zamontuj <nazwa> jako obraz dyskietki w stacji #11"},
	/* ru */ {IDCLS_ATTACH_AS_DISK_11_RU, "Attach <name> as a disk image in drive #11"},
	/* sv */ {IDCLS_ATTACH_AS_DISK_11_SV, "Anslut <namn> som diskettavbildning i enhet 11"},
	/* tr */ {IDCLS_ATTACH_AS_DISK_11_TR, "S¸r¸c¸ #11 disk imaj˝ olarak <isim> yerle˛tir"},
#endif
	
	/* kbdbuf.c */
	/* en */ {IDCLS_P_STRING,    N_("<string>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_STRING_DA, "<streng>"},
	/* de */ {IDCLS_P_STRING_DE, "<String>"},
	/* es */ {IDCLS_P_STRING_ES, "<cadena>"},
	/* fr */ {IDCLS_P_STRING_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_STRING_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_STRING_IT, "<stringa>"},
	/* ko */ {IDCLS_P_STRING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_STRING_NL, "<string>"},
	/* pl */ {IDCLS_P_STRING_PL, "<string>"},
	/* ru */ {IDCLS_P_STRING_RU, "<string>"},
	/* sv */ {IDCLS_P_STRING_SV, "<str‰ng>"},
	/* tr */ {IDCLS_P_STRING_TR, "<yaz˝>"},
#endif
	
	/* kbdbuf.c */
	/* en */ {IDCLS_PUT_STRING_INTO_KEYBUF,    N_("Put the specified string into the keyboard buffer.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PUT_STRING_INTO_KEYBUF_DA, "IndsÊt den angivne streng i tastatur-bufferen."},
	/* de */ {IDCLS_PUT_STRING_INTO_KEYBUF_DE, "Definierte Eingabe in Tastaturpuffer bereitstellen."},
	/* es */ {IDCLS_PUT_STRING_INTO_KEYBUF_ES, "Introduce la cadena indicada en el bufer de teclado."},
	/* fr */ {IDCLS_PUT_STRING_INTO_KEYBUF_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_PUT_STRING_INTO_KEYBUF_HU, "A megadott sztring elhelyezÈse a billenty˚zet pufferben."},
	/* it */ {IDCLS_PUT_STRING_INTO_KEYBUF_IT, "Metti la stringa specificata nel buffer di tastiera."},
	/* ko */ {IDCLS_PUT_STRING_INTO_KEYBUF_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PUT_STRING_INTO_KEYBUF_NL, "Plaats de opgegeven string in de toetsenbordbuffer."},
	/* pl */ {IDCLS_PUT_STRING_INTO_KEYBUF_PL, "Umie∂Ê dany ci±g znakÛw w buforze klawiatury"},
	/* ru */ {IDCLS_PUT_STRING_INTO_KEYBUF_RU, "Put the specified string into the keyboard buffer."},
	/* sv */ {IDCLS_PUT_STRING_INTO_KEYBUF_SV, "L‰gg den angivna str‰ngen i tangentbordsbufferten."},
	/* tr */ {IDCLS_PUT_STRING_INTO_KEYBUF_TR, "Klavye arabelleine belirtilen yaz˝y˝ koy."},
#endif
	
	/* log.c */
	/* en */ {IDCLS_SPECIFY_LOG_FILE_NAME,    N_("Specify log file name")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_LOG_FILE_NAME_DA, "Angiv navn pÂ logfil"},
	/* de */ {IDCLS_SPECIFY_LOG_FILE_NAME_DE, "Logdateiname definieren"},
	/* es */ {IDCLS_SPECIFY_LOG_FILE_NAME_ES, "Especificar nombre fichero registro"},
	/* fr */ {IDCLS_SPECIFY_LOG_FILE_NAME_FR, "SpÈcifier le nom du fichier log"},
	/* hu */ {IDCLS_SPECIFY_LOG_FILE_NAME_HU, "Adja meg a naplÛf·jl nevÈt"},
	/* it */ {IDCLS_SPECIFY_LOG_FILE_NAME_IT, "Specifica il nome del file di log"},
	/* ko */ {IDCLS_SPECIFY_LOG_FILE_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_LOG_FILE_NAME_NL, "Geef de naam van het logbestand"},
	/* pl */ {IDCLS_SPECIFY_LOG_FILE_NAME_PL, "Okre∂l nazwÍ pliku z logiem"},
	/* ru */ {IDCLS_SPECIFY_LOG_FILE_NAME_RU, "Specify log file name"},
	/* sv */ {IDCLS_SPECIFY_LOG_FILE_NAME_SV, "Ange namn pÂ loggfil"},
	/* tr */ {IDCLS_SPECIFY_LOG_FILE_NAME_TR, "Log dosyas˝ ismini belirt"},
#endif
	
	/* log.c */
	/* en */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT,    N_("Enable verbose log output.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_DA, "AktivÈr omstÊndeligt log-output"},
	/* de */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_DE, "Ausf¸hrliche Diagnose aktivieren."},
	/* es */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_ES, "Permitir salida escrita registro."},
	/* fr */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_IT, "Attiva output dei log verboso."},
	/* ko */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_NL, "Activeer verbose log uitvoer."},
	/* pl */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_PL, "W≥±cz szczegÛ≥owy zapis do loga"},
	/* ru */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_RU, "Enable verbose log output."},
	/* sv */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_SV, "Aktivera pratsam loggutdata."},
	/* tr */ {IDCLS_ENABLE_VERBOSE_LOG_OUTPUT_TR, "Verbose log Á˝kt˝s˝n˝ aktif et."},
#endif
	
	/* mouse.c */
	/* en */ {IDCLS_ENABLE_MOUSE_GRAB,    N_("Enable mouse grab")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_MOUSE_GRAB_DA, "AktivÈr overtagelse af mus"},
	/* de */ {IDCLS_ENABLE_MOUSE_GRAB_DE, "Maus aktivieren"},
	/* es */ {IDCLS_ENABLE_MOUSE_GRAB_ES, "Permitir captuar del ratÛn"},
	/* fr */ {IDCLS_ENABLE_MOUSE_GRAB_FR, "Saisir la souris"},
	/* hu */ {IDCLS_ENABLE_MOUSE_GRAB_HU, "EgÈr elkap·s engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_MOUSE_GRAB_IT, "Attiva cattura mouse"},
	/* ko */ {IDCLS_ENABLE_MOUSE_GRAB_KO, "∏∂øÏΩ∫ ±◊∑¶ ∞°¥…«œ∞‘ «œ±‚"},
	/* nl */ {IDCLS_ENABLE_MOUSE_GRAB_NL, "Gebruiken van de muis inschakelen"},
	/* pl */ {IDCLS_ENABLE_MOUSE_GRAB_PL, "W≥±cz przechwytywanie myszy"},
	/* ru */ {IDCLS_ENABLE_MOUSE_GRAB_RU, "Enable mouse grab"},
	/* sv */ {IDCLS_ENABLE_MOUSE_GRAB_SV, "Aktivera fÂngande av mus"},
	/* tr */ {IDCLS_ENABLE_MOUSE_GRAB_TR, "Mouse yakalamay˝ aktif et"},
#endif
	
	/* mouse.c */
	/* en */ {IDCLS_DISABLE_MOUSE_GRAB,    N_("Disable mouse grab")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_MOUSE_GRAB_DA, "DeaktivÈr overtagelse af mus"},
	/* de */ {IDCLS_DISABLE_MOUSE_GRAB_DE, "Maus deaktivieren"},
	/* es */ {IDCLS_DISABLE_MOUSE_GRAB_ES, "Deshabilitar captura de ratÛn"},
	/* fr */ {IDCLS_DISABLE_MOUSE_GRAB_FR, "Ne pas saisir la souris"},
	/* hu */ {IDCLS_DISABLE_MOUSE_GRAB_HU, "EgÈr elkap·s tilt·sa"},
	/* it */ {IDCLS_DISABLE_MOUSE_GRAB_IT, "Disattiva cattura mouse"},
	/* ko */ {IDCLS_DISABLE_MOUSE_GRAB_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_MOUSE_GRAB_NL, "Gebruiken van de muis uitschakelen"},
	/* pl */ {IDCLS_DISABLE_MOUSE_GRAB_PL, "Wy≥±cz przechwytywanie myszy"},
	/* ru */ {IDCLS_DISABLE_MOUSE_GRAB_RU, "Disable mouse grab"},
	/* sv */ {IDCLS_DISABLE_MOUSE_GRAB_SV, "Inaktivera fÂngande av mus"},
	/* tr */ {IDCLS_DISABLE_MOUSE_GRAB_TR, "Mouse yakalamay˝ pasifle˛tir"},
#endif
	
	/* mouse.c */
	/* en */ {IDCLS_SELECT_MOUSE_JOY_PORT,    N_("Select the joystick port the mouse is attached to")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SELECT_MOUSE_JOY_PORT_DA, "VÊlg hvilken joystickport musen er tilsluttet"},
	/* de */ {IDCLS_SELECT_MOUSE_JOY_PORT_DE, "Joystickport f¸r Maus ausw‰hlen"},
	/* es */ {IDCLS_SELECT_MOUSE_JOY_PORT_ES, "Seleccionar el puerto de joystick en el que esta insertado el ratÛn"},
	/* fr */ {IDCLS_SELECT_MOUSE_JOY_PORT_FR, "SÈlectionner le port sur lequel attacher la souris"},
	/* hu */ {IDCLS_SELECT_MOUSE_JOY_PORT_HU, "V·lassza ki a joystick portot, ahov· az egÈr csatolva van"},
	/* it */ {IDCLS_SELECT_MOUSE_JOY_PORT_IT, "Seleziona la porta joystick a cui Ë collegato il mouse"},
	/* ko */ {IDCLS_SELECT_MOUSE_JOY_PORT_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SELECT_MOUSE_JOY_PORT_NL, "Selecteer de joystickpoort waar de muis aan gekoppelt is"},
	/* pl */ {IDCLS_SELECT_MOUSE_JOY_PORT_PL, "Wybierz port joysticka, do ktÛrego pod≥±czona jest mysz"},
	/* ru */ {IDCLS_SELECT_MOUSE_JOY_PORT_RU, "Select the joystick port the mouse is attached to"},
	/* sv */ {IDCLS_SELECT_MOUSE_JOY_PORT_SV, "Ange vilken spelport musen ‰r ansluten till"},
	/* tr */ {IDCLS_SELECT_MOUSE_JOY_PORT_TR, "Mouse'un bal˝ olduu joystick portunu seÁin"},
#endif
	
	/* mouse.c */
	/* en */ {IDCLS_SELECT_MOUSE_TYPE,    N_("Select the mouse type (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Smart)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SELECT_MOUSE_TYPE_DA, "VÊlg mussetype (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Smart)"},
	/* de */ {IDCLS_SELECT_MOUSE_TYPE_DE, "Mouse typ w‰hlen (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Smart)"},
	/* es */ {IDCLS_SELECT_MOUSE_TYPE_ES, "Seleccionar tipo de ratÛn  (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Inteligente)"},
	/* fr */ {IDCLS_SELECT_MOUSE_TYPE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SELECT_MOUSE_TYPE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SELECT_MOUSE_TYPE_IT, "Seleziona il tipo di mouse (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Smart)"},
	/* ko */ {IDCLS_SELECT_MOUSE_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SELECT_MOUSE_TYPE_NL, "Selecteer de muis soort (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Smart)"},
	/* pl */ {IDCLS_SELECT_MOUSE_TYPE_PL, "Ustaw typ myszy (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = pokrÍt≥a, 4 = CX-22, 5 = ST, 6 = Smart)"},
	/* ru */ {IDCLS_SELECT_MOUSE_TYPE_RU, "≤Î—’‡ÿ‚’ ‚ÿﬂ ‹ÎËÿ (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Smart)"},
	/* sv */ {IDCLS_SELECT_MOUSE_TYPE_SV, "V‰lj mustyp (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = paddlar, 4 = CX-22, 5 = ST, 6 = Smart)"},
	/* tr */ {IDCLS_SELECT_MOUSE_TYPE_TR, "Mouse tipini seÁin (0 = 1351, 1 = NEOS, 2 = Amiga, 3 = Paddles, 4 = CX-22, 5 = ST, 6 = Smart)"},
#endif
	
	/* ps2mouse.c */
	/* en */ {IDCLS_ENABLE_PS2MOUSE,    N_("Enable PS/2 mouse on userport")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_PS2MOUSE_DA, "AktivÈr PS/2-mus pÂ brugerporten"},
	/* de */ {IDCLS_ENABLE_PS2MOUSE_DE, "PS/2 Userport Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_PS2MOUSE_ES, "Permitir ratÛn PS/2 en puerto usuario"},
	/* fr */ {IDCLS_ENABLE_PS2MOUSE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_PS2MOUSE_HU, "PS/2 egÈr engedÈlyezÈse a userporton"},
	/* it */ {IDCLS_ENABLE_PS2MOUSE_IT, "Attiva mouse PS/2 su userport"},
	/* ko */ {IDCLS_ENABLE_PS2MOUSE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_PS2MOUSE_NL, "Aktiveer emulatie van een PS/2 muis op de userport"},
	/* pl */ {IDCLS_ENABLE_PS2MOUSE_PL, "W≥±cz mysz PS/2 w userporcie"},
	/* ru */ {IDCLS_ENABLE_PS2MOUSE_RU, "Enable PS/2 mouse on userport"},
	/* sv */ {IDCLS_ENABLE_PS2MOUSE_SV, "Aktivera PS/2-mus pÂ anv‰ndarport"},
	/* tr */ {IDCLS_ENABLE_PS2MOUSE_TR, "Userport ¸zerinde PS/2 mouse'u aktif et"},
#endif
	
	/* ps2mouse.c */
	/* en */ {IDCLS_DISABLE_PS2MOUSE,    N_("Disable PS/2 mouse on userport")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_PS2MOUSE_DA, "DeaktivÈr PS/2-mus pÂ brugerporten"},
	/* de */ {IDCLS_DISABLE_PS2MOUSE_DE, "PS/2 Userport Emulation deaktivieren\""},
	/* es */ {IDCLS_DISABLE_PS2MOUSE_ES, "Deshabilitar ratÛn PS/2 en puerto usuario"},
	/* fr */ {IDCLS_DISABLE_PS2MOUSE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_PS2MOUSE_HU, "PS/2 egÈr tilt·sa a userporton"},
	/* it */ {IDCLS_DISABLE_PS2MOUSE_IT, "Disattiva mouse PS/2 su userport"},
	/* ko */ {IDCLS_DISABLE_PS2MOUSE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_PS2MOUSE_NL, "Emulatie van een PS/2 muis op de userport uitschakelen"},
	/* pl */ {IDCLS_DISABLE_PS2MOUSE_PL, "Wy≥±cz mysz PS/2 w userporcie"},
	/* ru */ {IDCLS_DISABLE_PS2MOUSE_RU, "Disable PS/2 mouse on userport"},
	/* sv */ {IDCLS_DISABLE_PS2MOUSE_SV, "Inaktivera PS/2-mus pÂ anv‰ndarport"},
	/* tr */ {IDCLS_DISABLE_PS2MOUSE_TR, "Userport ¸zerinde PS/2 mouse'u pasifle˛tir"},
#endif
	
	/* ram.c */
	/* en */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE,    N_("Set the value for the very first RAM address after powerup")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_DA, "Angiv vÊrdien for den allerf¯rste RAM adresse efter power-up"},
	/* de */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_DE, "Wert f¸r erstes Byte im RAM nach Kaltstart setzen"},
	/* es */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_ES, "Seleccionar el valor para la primera direcciÛn RAM despues del encendido"},
	/* fr */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_FR, "SpÈcifier la valeur de la premiËre adresse RAM aprËs la mise sous tension"},
	/* hu */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_HU, "Adja meg a legelsı RAM cÌm ÈrtÈkÈt bekapcsol·s ut·n"},
	/* it */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_IT, "Imposta il valore del primissimo indirizzo della RAM dopo l'accensione"},
	/* ko */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_NL, "Zet de waarde voor het allereerste RAM adres na koude start"},
	/* pl */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_PL, "Okre∂l warto∂Ê pierwszego adresu RAM po uruchomieniu"},
	/* ru */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_RU, "Set the value for the very first RAM address after powerup"},
	/* sv */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_SV, "Ange v‰rdet pÂ den allra fˆrsta RAM-adressen efter strˆmpÂslag"},
	/* tr */ {IDCLS_SET_FIRST_RAM_ADDRESS_VALUE_TR, "G¸Á verildiinde ba˛lang˝Átaki RAM adreslerine atanacak deeri belirle"},
#endif
	
	/* ram.c */
	/* en */ {IDCLS_P_NUM_OF_BYTES,    N_("<num of bytes>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_NUM_OF_BYTES_DA, "<antal bytes>"},
	/* de */ {IDCLS_P_NUM_OF_BYTES_DE, "<Anzahl an Bytes>"},
	/* es */ {IDCLS_P_NUM_OF_BYTES_ES, "<n˙mero de bytes>"},
	/* fr */ {IDCLS_P_NUM_OF_BYTES_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_NUM_OF_BYTES_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_NUM_OF_BYTES_IT, "<numero di byte>"},
	/* ko */ {IDCLS_P_NUM_OF_BYTES_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_NUM_OF_BYTES_NL, "<aantal bytes>"},
	/* pl */ {IDCLS_P_NUM_OF_BYTES_PL, "<num of bytes>"},
	/* ru */ {IDCLS_P_NUM_OF_BYTES_RU, "<num of bytes>"},
	/* sv */ {IDCLS_P_NUM_OF_BYTES_SV, "<antal byte>"},
	/* tr */ {IDCLS_P_NUM_OF_BYTES_TR, "<byte say˝s˝>"},
#endif
	
	/* ram.c */
	/* en */ {IDCLS_LENGTH_BLOCK_SAME_VALUE,    N_("Length of memory block initialized with the same value")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_DA, "LÊngde pÂ hukommelsesblok som initialiseres med samme vÊrdi"},
	/* de */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_DE, "L‰nge des Speicherblocks der mit dem gleichen Wert initialisiert ist"},
	/* es */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_ES, "Longitud del bloque de memoria inicializado con el mismo valor"},
	/* fr */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_FR, "Longeur du premier bloc mÈmoire initialisÈ avec la mÍme valeur"},
	/* hu */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_HU, "Azonos ÈrtÈkkel feltˆltˆtt memÛria blokkoknak a hossza"},
	/* it */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_IT, "Lunghezza del blocco di memoria inizializzato con lo stesso valore"},
	/* ko */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_NL, "Geheugenblokgrootte die dezelfde waarde krijgt bij initialisatie"},
	/* pl */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_PL, "D≥ugo∂Ê bloku pamiÍci zainicjowanego z t± sam± warto∂ci±"},
	/* ru */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_RU, "Length of memory block initialized with the same value"},
	/* sv */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_SV, "L‰ngd pÂ minnesblock som initierats med samma v‰rde"},
	/* tr */ {IDCLS_LENGTH_BLOCK_SAME_VALUE_TR, "Ayn˝ deerle balang˝Á ayarlar˝ yap˝lan bellek blou uzunluu"},
#endif
	
	/* ram.c */
	/* en */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN,    N_("Length of memory block initialized with the same pattern")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_DA, "LÊngde pÂ hukommelsesblok som initialiseres med samme m¯nster"},
	/* de */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_DE, "L‰nge des Speicherblocks der mit dem gleichen Muster initialisiert ist"},
	/* es */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_ES, "Longitud bloque memoria inicializado con el mismo patrÛn"},
	/* fr */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_FR, "Longeur du premier bloc mÈmoire initialisÈ avec le mÍme pattern"},
	/* hu */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_HU, "Azonos mint·val feltˆltˆtt memÛria blokkoknak a hossza"},
	/* it */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_IT, "Lunghezza del blocco di memoria inizializzato con lo stesso pattern"},
	/* ko */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_NL, "Geheugenblokgrootte met hetzelfde patroon bij initialisatie"},
	/* pl */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_PL, "D≥ugo∂Ê bloku pamiÍci zainicjowanego z tym samym wzorcem"},
	/* ru */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_RU, "Length of memory block initialized with the same pattern"},
	/* sv */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_SV, "L‰ngd pÂ minnesblock som initierats med samma mˆnster"},
	/* tr */ {IDCLS_LENGTH_BLOCK_SAME_PATTERN_TR, "Ayn˝ desenle balang˝Á ayarlar˝ yap˝lan bellek blou uzunluu"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_ENABLE_SOUND_PLAYBACK,    N_("Enable sound playback")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SOUND_PLAYBACK_DA, "SlÂ lydemulering til"},
	/* de */ {IDCLS_ENABLE_SOUND_PLAYBACK_DE, "Sound Wiedergabe einschalten"},
	/* es */ {IDCLS_ENABLE_SOUND_PLAYBACK_ES, "Permitir sonido pregrabado"},
	/* fr */ {IDCLS_ENABLE_SOUND_PLAYBACK_FR, "Activer le son"},
	/* hu */ {IDCLS_ENABLE_SOUND_PLAYBACK_HU, "Hangok engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_SOUND_PLAYBACK_IT, "Attiva riproduzione audio"},
	/* ko */ {IDCLS_ENABLE_SOUND_PLAYBACK_KO, "ªÁøÓµÂ «√∑π¿ÃπÈ ¿ª ªÁøÎ∞°¥…«œ∞‘ «œ±‚"},
	/* nl */ {IDCLS_ENABLE_SOUND_PLAYBACK_NL, "Activeer geluidsweergave"},
	/* pl */ {IDCLS_ENABLE_SOUND_PLAYBACK_PL, "W≥±cz dºwiÍk"},
	/* ru */ {IDCLS_ENABLE_SOUND_PLAYBACK_RU, "Enable sound playback"},
	/* sv */ {IDCLS_ENABLE_SOUND_PLAYBACK_SV, "Aktivera ljudÂtergivning"},
	/* tr */ {IDCLS_ENABLE_SOUND_PLAYBACK_TR, "Sesi aktif et"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_DISABLE_SOUND_PLAYBACK,    N_("Disable sound playback")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SOUND_PLAYBACK_DA, "SlÂ lydemulering fra"},
	/* de */ {IDCLS_DISABLE_SOUND_PLAYBACK_DE, "Sound Wiedergabe ausschalten"},
	/* es */ {IDCLS_DISABLE_SOUND_PLAYBACK_ES, "Desactivar salida de sonido"},
	/* fr */ {IDCLS_DISABLE_SOUND_PLAYBACK_FR, "DÈsactiver le son"},
	/* hu */ {IDCLS_DISABLE_SOUND_PLAYBACK_HU, "Hangok tilt·sa"},
	/* it */ {IDCLS_DISABLE_SOUND_PLAYBACK_IT, "Disattiva riproduzione audio"},
	/* ko */ {IDCLS_DISABLE_SOUND_PLAYBACK_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SOUND_PLAYBACK_NL, "Geluid uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SOUND_PLAYBACK_PL, "Wy≥±cz odtwarzanie dºwiÍku"},
	/* ru */ {IDCLS_DISABLE_SOUND_PLAYBACK_RU, "Disable sound playback"},
	/* sv */ {IDCLS_DISABLE_SOUND_PLAYBACK_SV, "Inaktivera ljudÂtergivning"},
	/* tr */ {IDCLS_DISABLE_SOUND_PLAYBACK_TR, "Sesi pasifle˛tir"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ,    N_("Set sound sample rate to <value> Hz")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_DA, "SÊt lydsamplefrekvens til <vÊrdi> Hz"},
	/* de */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_DE, "Setze Sound Sample Rate zu <Wert> Hz"},
	/* es */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_ES, "Seleccionar velocidad de muestreo de sonido en <valor> Hz"},
	/* fr */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_FR, "RÈgler le taux d'Èchantillonage ‡ <valeur> Hz"},
	/* hu */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_HU, "Hang mintavÈtelezÈsi r·ta be·llÌt·sa <ÈrtÈk> Hz-re"},
	/* it */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_IT, "Imposta la velocit‡ di campionamento audio a <valore> Hz"},
	/* ko */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_NL, "Zet de geluid sample rate naar <waarde> Hz"},
	/* pl */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_PL, "Ustaw prÛbkowanie sampli na <warto∂Ê> Hz"},
	/* ru */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_RU, "Set sound sample rate to <value> Hz"},
	/* sv */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_SV, "S‰tt ljudsamplingshastighet till <v‰rde> Hz"},
	/* tr */ {IDCLS_SET_SAMPLE_RATE_VALUE_HZ_TR, "Ses ˆrnekleme h˝z˝n˝ <deer> Hz olarak ayarla"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC,    N_("Set sound buffer size to <value> msec")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_DA, "SÊt lydbufferst¯rrelse til <vÊrdi> ms"},
	/* de */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_DE, "Setze Source Buffer Grˆﬂe zu <Wert> msek"},
	/* es */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_ES, "Seleccionar tamaÒo bufer sonido en <valor>mseg"},
	/* fr */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_FR, "RÈgler la taille du tampon son ‡ <valeur> ms"},
	/* hu */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_HU, "A hangpuffer mÈretÈt <ÈrtÈk> mp-re ·llÌtja"},
	/* it */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_IT, "Imposta la dimensione del buffer audio a <valore> msec"},
	/* ko */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_NL, "Zet de geluidsbuffergrootte naar <waarde> msec"},
	/* pl */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_PL, "Ustaw rozmiar bufora dºwiÍku na <warto∂Ê> ms"},
	/* ru */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_RU, "Set sound buffer size to <value> msec"},
	/* sv */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_SV, "S‰tt ljudbuffertstorlek till <v‰rde> ms"},
	/* tr */ {IDCLS_SET_SOUND_BUFFER_SIZE_MSEC_TR, "Ses arabellek boyutunu <deer> milisaniye olarak ayarla"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SET_SOUND_FRAGMENT_SIZE,    N_("Set sound fragment size (0 = small, 1 = medium, 2 = large)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_DA, "SÊt st¯rrelse pÂ lydfragmenter (0 = lille, 1 = medium, 2 = stor)"},
	/* de */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_DE, "Setze Sound Fragmentgrˆﬂe (0 = klein, 1 = mittel, 2 = groﬂ)"},
	/* es */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_ES, "Seleccionar tamaÒo fragmento  (0 = pequeÒo, 1 = medio, 2 = grande)"},
	/* fr */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_IT, "Imposta la dimensione dei frammenti audio (0 = piccola, 1 = media, 2 = grande)"},
	/* ko */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_NL, "Zet geluidsfragment grootte (0 = klein, 1 = matig, 2 = groot)"},
	/* pl */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_PL, "Ustaw rozmiar fragmentu dºwiÍku (0 = ma≥y, 1 = ∂redni, 2 = duøy)"},
	/* ru */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_RU, "Set sound fragment size (0 = small, 1 = medium, 2 = large)"},
	/* sv */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_SV, "V‰lj storlek fˆr ljudfragment (0 = liten, 1= medium, 2 = stor)"},
	/* tr */ {IDCLS_SET_SOUND_FRAGMENT_SIZE_TR, "Ses parÁa boyutunu ayarla (0 = k¸Á¸k, 1 = orta, 2 = b¸y¸k)"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SPECIFY_SOUND_DRIVER,    N_("Specify sound driver")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SOUND_DRIVER_DA, "Angiv lyddriver"},
	/* de */ {IDCLS_SPECIFY_SOUND_DRIVER_DE, "Sound Treiber spezifieren"},
	/* es */ {IDCLS_SPECIFY_SOUND_DRIVER_ES, "Especificar controlador de sonido"},
	/* fr */ {IDCLS_SPECIFY_SOUND_DRIVER_FR, "SpÈcifier le pilote de son"},
	/* hu */ {IDCLS_SPECIFY_SOUND_DRIVER_HU, "Adja meg a hangmodul nevÈt"},
	/* it */ {IDCLS_SPECIFY_SOUND_DRIVER_IT, "Specifica il driver audio"},
	/* ko */ {IDCLS_SPECIFY_SOUND_DRIVER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SOUND_DRIVER_NL, "Geef geluidsstuurprogramma"},
	/* pl */ {IDCLS_SPECIFY_SOUND_DRIVER_PL, "Okre∂l sterownik dºwiÍku"},
	/* ru */ {IDCLS_SPECIFY_SOUND_DRIVER_RU, "Specify sound driver"},
	/* sv */ {IDCLS_SPECIFY_SOUND_DRIVER_SV, "Ange ljuddrivrutin"},
	/* tr */ {IDCLS_SPECIFY_SOUND_DRIVER_TR, "Ses s¸r¸c¸s¸ belirt"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_P_ARGS,    N_("<args>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_ARGS_DA, "<argumenter>"},
	/* de */ {IDCLS_P_ARGS_DE, "<Argumente>"},
	/* es */ {IDCLS_P_ARGS_ES, "<argumentos>"},
	/* fr */ {IDCLS_P_ARGS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_ARGS_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_ARGS_IT, "<argomenti>"},
	/* ko */ {IDCLS_P_ARGS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_ARGS_NL, "<parameters>"},
	/* pl */ {IDCLS_P_ARGS_PL, "<args>"},
	/* ru */ {IDCLS_P_ARGS_RU, "<args>"},
	/* sv */ {IDCLS_P_ARGS_SV, "<flaggor>"},
	/* tr */ {IDCLS_P_ARGS_TR, "<arg¸manlar>"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM,    N_("Specify initialization parameters for sound driver")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_DA, "Angiv initialiseringsparametre for lyddriver"},
	/* de */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_DE, "Initialisierungsparameter des Sound Treibers spezifizieren"},
	/* es */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_ES, "Especificar parametros de inicializaciÛn para el controlador de sonido"},
	/* fr */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_FR, "SpÈcifier les paramËtres d'initialisation pour le pilote son"},
	/* hu */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_HU, "Adja meg a hangmodul indul·si paramÈtereit"},
	/* it */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_IT, "Specifica i parametri di inizializzazione del driver audio"},
	/* ko */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_NL, "Geef de initialisatieparameters voor het geluidsstuurprogramma"},
	/* pl */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_PL, "Okre∂l parametry inicjalizacji sterownika dºwiÍku"},
	/* ru */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_RU, "Specify initialization parameters for sound driver"},
	/* sv */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_SV, "Ange initieringsflaggor fˆr ljuddrivrutin"},
	/* tr */ {IDCLS_SPECIFY_SOUND_DRIVER_PARAM_TR, "Ses s¸r¸c¸s¸ iÁin ba˛lang˝Á parametrelerini belirt"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER,    N_("Specify recording sound driver")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_DA, "Angiv driver til lydoptagelse"},
	/* de */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_DE, "Sound Treiber f¸r Aufnahme spezifizieren"},
	/* es */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_ES, "Especificar controlador grabaciÛn sonido"},
	/* fr */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_FR, "SpÈcifier le pilote d'enregistrement"},
	/* hu */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_HU, "Adja meg a felvÈtelhez haszn·lt hangmodult"},
	/* it */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_IT, "Specifica il driver audio di registrazione"},
	/* ko */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_NL, "Geef geluidsstuurprogramma voor opname"},
	/* pl */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_PL, "Okre∂l sterownik zapisu dºwiÍku"},
	/* ru */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_RU, "Specify recording sound driver"},
	/* sv */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_SV, "Ange ljuddrivrutin fˆr inspelning"},
	/* tr */ {IDCLS_SPECIFY_RECORDING_SOUND_DRIVER_TR, "Ses kay˝t s¸r¸c¸s¸n¸ belirt"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM,    N_("Specify initialization parameters for recording sound driver")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_DA, "Angiv initialiseringsparametre for driver til lydoptagelse"},
	/* de */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_DE, "Initialisierungsparameter f¸r Aufnahme Sound Treiber spezifieren"},
	/* es */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_ES, "Especificar parametros inicializaciÛn para el controlador grabaciÛn sonido "},
	/* fr */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_FR, "SpÈcifier les paramËtres d'initialisation pour le pilote d'enregistrement"},
	/* hu */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_HU, "Adja meg a felvÈtelhez haszn·lt hangmodul indul·si paramÈtereit"},
	/* it */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_IT, "Specifica i parametri di inizializzazione per il driver audio di registrazione"},
	/* ko */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_NL, "Geef initialisatieparameters voor het geluidsstuurprogramma voor opname"},
	/* pl */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_PL, "Okre∂l parametry inicjalizacji sterownika zapisu dºwiÍku"},
	/* ru */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_RU, "Specify initialization parameters for recording sound driver"},
	/* sv */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_SV, "Ange initieringsflaggor fˆr ljuddrivrutin fˆr inspelning"},
	/* tr */ {IDCLS_SPECIFY_REC_SOUND_DRIVER_PARAM_TR, "Ses kay˝t s¸r¸c¸s¸ iÁin ba˛lang˝Á parametrelerini belirt"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_P_SYNC,    N_("<sync>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_SYNC_DA, "<sync>"},
	/* de */ {IDCLS_P_SYNC_DE, "<Sync>"},
	/* es */ {IDCLS_P_SYNC_ES, "<sincronÌa>"},
	/* fr */ {IDCLS_P_SYNC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_SYNC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_SYNC_IT, "<sync>"},
	/* ko */ {IDCLS_P_SYNC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_SYNC_NL, "<sync>"},
	/* pl */ {IDCLS_P_SYNC_PL, "<sync>"},
	/* ru */ {IDCLS_P_SYNC_RU, "<sync>"},
	/* sv */ {IDCLS_P_SYNC_SV, "<synk>"},
	/* tr */ {IDCLS_P_SYNC_TR, "<senkron>"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SET_SOUND_SPEED_ADJUST,    N_("Set sound speed adjustment (0: flexible, 1: adjusting, 2: exact)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_SOUND_SPEED_ADJUST_DA, "Indstil lydjusteringshastighed (0: fleksibel, 1: justerende, 2: n¯jagtig)"},
	/* de */ {IDCLS_SET_SOUND_SPEED_ADJUST_DE, "Setze Sound Geschwindigkeit Anpassung (0: flexibel, 1: anpassend, 2: exakt)"},
	/* es */ {IDCLS_SET_SOUND_SPEED_ADJUST_ES, "Ajsute velocidad sonido (0: flexible, 1: ajustado, 2: exacto)"},
	/* fr */ {IDCLS_SET_SOUND_SPEED_ADJUST_FR, "Choisir la mÈthode d'ajustement du son (0: flexible, 1: ajustÈ 2: exact)"},
	/* hu */ {IDCLS_SET_SOUND_SPEED_ADJUST_HU, "Adja meg a zene sebessÈg igazÌt·s·t (0: rugalmas. 1: igazodÛ, 2: pontos)"},
	/* it */ {IDCLS_SET_SOUND_SPEED_ADJUST_IT, "Imposta il tipo di adattamento della velocit‡ audio (0: flessibile, 1: adattabile, 2: esatta)"},
	/* ko */ {IDCLS_SET_SOUND_SPEED_ADJUST_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_SOUND_SPEED_ADJUST_NL, "Zet geluidssnelheid aanpassing (0: flexibel, 1: aanpassend, 2: exact)"},
	/* pl */ {IDCLS_SET_SOUND_SPEED_ADJUST_PL, "Ustaw dopasowanie prÍdko∂ci dºwiÍku (0: elastyczne, 1: dopasowane, 2: dok≥adne)"},
	/* ru */ {IDCLS_SET_SOUND_SPEED_ADJUST_RU, "Set sound speed adjustment (0: flexible, 1: adjusting, 2: exact)"},
	/* sv */ {IDCLS_SET_SOUND_SPEED_ADJUST_SV, "St‰ll in ljudhastighetsjustering (0: flexibel, 1: justerande, 2: exakt)"},
	/* tr */ {IDCLS_SET_SOUND_SPEED_ADJUST_TR, "Ses h˝z˝ ayarlamas˝n˝ yap˝n (0: esnek, 1: d¸zeltme, 2: aynen)"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_P_OUTPUT_MODE,    N_("<output mode>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_OUTPUT_MODE_DA, "<Uddata-tilstand>"},
	/* de */ {IDCLS_P_OUTPUT_MODE_DE, "<Ausgabe Modus>"},
	/* es */ {IDCLS_P_OUTPUT_MODE_ES, "<Modo de salida>"},
	/* fr */ {IDCLS_P_OUTPUT_MODE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_OUTPUT_MODE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_OUTPUT_MODE_IT, "<modalit‡ di uscita>"},
	/* ko */ {IDCLS_P_OUTPUT_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_OUTPUT_MODE_NL, "<uitvoer modus>"},
	/* pl */ {IDCLS_P_OUTPUT_MODE_PL, "<tryb wyj∂cia>"},
	/* ru */ {IDCLS_P_OUTPUT_MODE_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_P_OUTPUT_MODE_SV, "<utdatal‰ge>"},
	/* tr */ {IDCLS_P_OUTPUT_MODE_TR, "<Á˝k˝˛ modu>"},
#endif
	
	/* sound.c */
	/* en */ {IDCLS_SOUND_OUTPUT_MODE,    N_("Sound output mode: (0: system decides mono/stereo, 1: always mono, 2: always stereo)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SOUND_OUTPUT_MODE_DA, "Lydindstillinger: "},
	/* de */ {IDCLS_SOUND_OUTPUT_MODE_DE, "Ton Ausgabe Modus: "},
	/* es */ {IDCLS_SOUND_OUTPUT_MODE_ES, "Modo salida sonido: "},
	/* fr */ {IDCLS_SOUND_OUTPUT_MODE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SOUND_OUTPUT_MODE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_SOUND_OUTPUT_MODE_IT, "Modalit‡ di uscita audio: "},
	/* ko */ {IDCLS_SOUND_OUTPUT_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SOUND_OUTPUT_MODE_NL, "Geluid uitvoer modus: "},
	/* pl */ {IDCLS_SOUND_OUTPUT_MODE_PL, "Tryb wyj∂cia dºwiÍku: "},
	/* ru */ {IDCLS_SOUND_OUTPUT_MODE_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_SOUND_OUTPUT_MODE_SV, "Utdatal‰ge fˆr ljud: "},
	/* tr */ {IDCLS_SOUND_OUTPUT_MODE_TR, "Ses Á˝k˝˛˝ modu: "},
#endif
	
	/* sysfile.c */
	/* en */ {IDCLS_P_PATH,    N_("<Path>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_PATH_DA, "<Sti>"},
	/* de */ {IDCLS_P_PATH_DE, "<Pfad>"},
	/* es */ {IDCLS_P_PATH_ES, "<Camino>"},
	/* fr */ {IDCLS_P_PATH_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_PATH_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_PATH_IT, "<Percorso>"},
	/* ko */ {IDCLS_P_PATH_KO, "<±Ê>"},
	/* nl */ {IDCLS_P_PATH_NL, "<Pad>"},
	/* pl */ {IDCLS_P_PATH_PL, "<¶cieøka>"},
	/* ru */ {IDCLS_P_PATH_RU, "<ø„‚Ï>"},
	/* sv */ {IDCLS_P_PATH_SV, "<Sˆkv‰g>"},
	/* tr */ {IDCLS_P_PATH_TR, "<Yol>"},
#endif
	
	/* sysfile.c */
	/* en */ {IDCLS_DEFINE_SYSTEM_FILES_PATH,    N_("Define search path to locate system files")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_DA, "Angiv sti til systemfiler"},
	/* de */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_DE, "Suchpfad f¸r Systemdateien definieren"},
	/* es */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_ES, "Definir camino de busqueda para los ficheros locales de sistema"},
	/* fr */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_FR, "DÈfinir le chemin de recherche pour trouver les fichiers systËmes"},
	/* hu */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_HU, "KeresÈsi ˙tvonal megad·sa a rendszerf·jlok megtal·l·s·ra"},
	/* it */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_IT, "Definisci il path di ricerca per cercare i file di sistema"},
	/* ko */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_NL, "Geef het zoek pad waar de systeem bestanden te vinden zijn"},
	/* pl */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_PL, "Definiuj ∂cieøkÍ wyszukiwania plikÛw systemowych"},
	/* ru */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_RU, "Define search path to locate system files"},
	/* sv */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_SV, "Ange sˆkv‰g fˆr att hitta systemfiler"},
	/* tr */ {IDCLS_DEFINE_SYSTEM_FILES_PATH_TR, "Sistem dosyalar˝n˝n konumunu belirlemek iÁin arama yolu tan˝mlay˝n"},
#endif
	
	/* traps.c */
	/* en */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION,    N_("Enable general mechanisms for fast disk/tape emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_DA, "AktivÈr generelle mekanismer for hurtig disk-/bÂndemulering"},
	/* de */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_DE, "Allgemeine Mechanismen f¸r schnelle Disk/Band Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_ES, "Permitir mecanismos generales para emulaciÛn r·pida de cinta/disco"},
	/* fr */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_FR, "Activer les mÈchanismes gÈnÈraux pour l'Èmulation disque/datassette rapide"},
	/* hu */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_HU, "A lemez/szalag emul·ciÛt gyorsÌtÛ mechanizmusok engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_IT, "Attiva meccanismo generale per l'emulazione veloce del disco/cassetta"},
	/* ko */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_NL, "Activeer algemene methoden voor snelle disk/tape emulatie"},
	/* pl */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_PL, "W≥±cz mechanizm szybkiej emulacji dysku i ta∂my"},
	/* ru */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_RU, "Enable general mechanisms for fast disk/tape emulation"},
	/* sv */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_SV, "Aktivera generella mekanismer fˆr snabb disk-/bandemulering"},
	/* tr */ {IDCLS_ENABLE_TRAPS_FAST_EMULATION_TR, "H˝zl˝ disk/teyp em¸lasyonu iÁin genel mekanizmay˝ aktif et"},
#endif
	
	/* traps.c */
	/* en */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION,    N_("Disable general mechanisms for fast disk/tape emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_DA, "DeaktivÈr generelle mekanismer for hurtig disk-/bÂndemulering"},
	/* de */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_DE, "Allgemeine Mechanismen f¸r schnelle Disk/Band Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_ES, "Deshabilitar mecanismos generales para emulaciÛn r·pida de cinta/disco"},
	/* fr */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_FR, "DÈsactiver les mÈchanismes gÈnÈraux pour l'Èmulation disque/datassette rapide"},
	/* hu */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_HU, "A lemez/szalag emul·ciÛt gyorsÌtÛ mechanizmusok tilt·sa"},
	/* it */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_IT, "Disattiva meccanismo generale per l'emulazione veloce del disco/cassetta"},
	/* ko */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_NL, "Algemene methoden voor snelle disk/tape emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_PL, "Wy≥±cz mechanizm szybkiej emulacji dysku i ta∂my"},
	/* ru */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_RU, "Disable general mechanisms for fast disk/tape emulation"},
	/* sv */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_SV, "Inaktivera generella mekanismer fˆr snabb disk-/bandemulering"},
	/* tr */ {IDCLS_DISABLE_TRAPS_FAST_EMULATION_TR, "H˝zl˝ disk/teyp em¸lasyonu iÁin genel mekanizmay˝ pasifle˛tir"},
#endif
	
	/* vsync.c */
	/* en */ {IDCLS_LIMIT_SPEED_TO_VALUE,    N_("Limit emulation speed to specified value")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_LIMIT_SPEED_TO_VALUE_DA, "BegrÊns emuleringshastighed til angiven vÊrdi"},
	/* de */ {IDCLS_LIMIT_SPEED_TO_VALUE_DE, "Emulationsgeschwindigkeit auf Wert beschr‰nken."},
	/* es */ {IDCLS_LIMIT_SPEED_TO_VALUE_ES, "Limitar la velocidad de emulaciÛn al valor indicado"},
	/* fr */ {IDCLS_LIMIT_SPEED_TO_VALUE_FR, "Limiter la vitesse d'Èmulation ‡ une valeur specifiÈe"},
	/* hu */ {IDCLS_LIMIT_SPEED_TO_VALUE_HU, "Emul·ciÛs sebessÈg lehat·rol·sa adott ÈrtÈkre"},
	/* it */ {IDCLS_LIMIT_SPEED_TO_VALUE_IT, "Limita la velocit‡ di emulazione al valore specificato"},
	/* ko */ {IDCLS_LIMIT_SPEED_TO_VALUE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_LIMIT_SPEED_TO_VALUE_NL, "Beperk emulatiesnelheid tot de opgegeven waarde"},
	/* pl */ {IDCLS_LIMIT_SPEED_TO_VALUE_PL, "Ograniczaj prÍdko∂Ê emulacji do podanej warto∂ci"},
	/* ru */ {IDCLS_LIMIT_SPEED_TO_VALUE_RU, "æ”‡–›ÿÁÿ‚Ï ·⁄ﬁ‡ﬁ·‚Ï Ì‹„€ÔÊÿÿ ‘ﬁ ﬁﬂ‡’‘’€’››ﬁ”ﬁ ◊›–Á’›ÿÔ"},
	/* sv */ {IDCLS_LIMIT_SPEED_TO_VALUE_SV, "Begr‰nsa emuleringshastighet till angivet v‰rde"},
	/* tr */ {IDCLS_LIMIT_SPEED_TO_VALUE_TR, "Em¸lasyon h˝z˝n˝ belirtilmi˛ deer ile limitle"},
#endif
	
	/* vsync.c */
	/* en */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES,    N_("Update every <value> frames (`0' for automatic)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_DA, "OpdatÈr for hver <vÊrdi> billeder (\"0\" for automatisk)"},
	/* de */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_DE, "Jedes <Wert> Bild aktualisieren (`0' f¸r Automatik)"},
	/* es */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_ES, "Actualizar cada <valor> cuadros (`0' for automatic)"},
	/* fr */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_FR, "Mise ‡ jour toutes les <valeur> images (`0' pour auto.)"},
	/* hu */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_HU, "FrissÌtsen minden <ÈrtÈk> kÈpkocka elteltÈvel (0 automatikust jelent)"},
	/* it */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_IT, "Aggiorna ogni <valore> frame (`0' per automatico)"},
	/* ko */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_NL, "Elke <waarde> beeld vernieuwen (`0' voor automatisch)"},
	/* pl */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_PL, "Aktualizuj co <warto∂Ê> klatek (`0' - automatycznie)"},
	/* ru */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_RU, "Update every <value> frames (`0' for automatic)"},
	/* sv */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_SV, "Uppdatera varje <v‰rde> ramar (\"0\" fˆr automatiskt)"},
	/* tr */ {IDCLS_UPDATE_EVERY_VALUE_FRAMES_TR, "Her <deer> framede bir g¸ncelle (otomatik iÁin `0')"},
#endif
	
	/* vsync.c */
	/* en */ {IDCLS_ENABLE_WARP_MODE,    N_("Enable warp mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_WARP_MODE_DA, "AktivÈr warp-tilstand"},
	/* de */ {IDCLS_ENABLE_WARP_MODE_DE, "Warp Mode aktivieren"},
	/* es */ {IDCLS_ENABLE_WARP_MODE_ES, "Permitir m·xima velocidad"},
	/* fr */ {IDCLS_ENABLE_WARP_MODE_FR, "Activer Turbo"},
	/* hu */ {IDCLS_ENABLE_WARP_MODE_HU, "Hipergyors mÛd engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_WARP_MODE_IT, "Attiva modalit‡ turbo"},
	/* ko */ {IDCLS_ENABLE_WARP_MODE_KO, "ø˙«¡ ∏µÂ ªÁøÎ∞°¥…«œ∞‘ «œ±‚"},
	/* nl */ {IDCLS_ENABLE_WARP_MODE_NL, "Activeer warpmodus"},
	/* pl */ {IDCLS_ENABLE_WARP_MODE_PL, "W≥±cz tryb przy∂pieszony (Turbo)"},
	/* ru */ {IDCLS_ENABLE_WARP_MODE_RU, "Enable warp mode"},
	/* sv */ {IDCLS_ENABLE_WARP_MODE_SV, "Aktivera warpl‰ge"},
	/* tr */ {IDCLS_ENABLE_WARP_MODE_TR, "Warp modu aktif et"},
#endif
	
	/* vsync.c */
	/* en */ {IDCLS_DISABLE_WARP_MODE,    N_("Disable warp mode")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_WARP_MODE_DA, "DeaktivÈr warp-tilstand"},
	/* de */ {IDCLS_DISABLE_WARP_MODE_DE, "Warp Mode deaktivieren"},
	/* es */ {IDCLS_DISABLE_WARP_MODE_ES, "Desabilitar modo Ultrar·pido"},
	/* fr */ {IDCLS_DISABLE_WARP_MODE_FR, "DÈsactiver Turbo"},
	/* hu */ {IDCLS_DISABLE_WARP_MODE_HU, "Hipergyors mÛd tilt·sa"},
	/* it */ {IDCLS_DISABLE_WARP_MODE_IT, "Disattiva modalit‡ turbo"},
	/* ko */ {IDCLS_DISABLE_WARP_MODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_WARP_MODE_NL, "Warpmodus uitschakelen"},
	/* pl */ {IDCLS_DISABLE_WARP_MODE_PL, "Wy≥±cz tryb przyspieszony"},
	/* ru */ {IDCLS_DISABLE_WARP_MODE_RU, "Disable warp mode"},
	/* sv */ {IDCLS_DISABLE_WARP_MODE_SV, "Inaktivera warpl‰ge"},
	/* tr */ {IDCLS_DISABLE_WARP_MODE_TR, "Warp modu pasifle˛tir"},
#endif
	
	/* translate.c */
	/* en */ {IDCLS_P_ISO_LANGUAGE_CODE,    N_("<iso language code>")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_P_ISO_LANGUAGE_CODE_DA, "<iso-sprogkode>"},
	/* de */ {IDCLS_P_ISO_LANGUAGE_CODE_DE, "<iso Sprachcode>"},
	/* es */ {IDCLS_P_ISO_LANGUAGE_CODE_ES, "<cÛdigo ISO idioma>"},
	/* fr */ {IDCLS_P_ISO_LANGUAGE_CODE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_P_ISO_LANGUAGE_CODE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_P_ISO_LANGUAGE_CODE_IT, "<codice iso lingua>"},
	/* ko */ {IDCLS_P_ISO_LANGUAGE_CODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_P_ISO_LANGUAGE_CODE_NL, "<iso taalcode>"},
	/* pl */ {IDCLS_P_ISO_LANGUAGE_CODE_PL, "<Kod jÍzykowy iso>"},
	/* ru */ {IDCLS_P_ISO_LANGUAGE_CODE_RU, "<iso language code>"},
	/* sv */ {IDCLS_P_ISO_LANGUAGE_CODE_SV, "<iso-sprÂkkod>"},
	/* tr */ {IDCLS_P_ISO_LANGUAGE_CODE_TR, "<iso dil kodu>"},
#endif
	
	/* translate.c */
	/* en */ {IDCLS_SPECIFY_ISO_LANG_CODE,    N_("Specify the iso code of the language")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_ISO_LANG_CODE_DA, "Angiv ISO-koden for sproget"},
	/* de */ {IDCLS_SPECIFY_ISO_LANG_CODE_DE, "Iso Sprachcode spezifizieren"},
	/* es */ {IDCLS_SPECIFY_ISO_LANG_CODE_ES, "Especificar el cÛdigo ISO para el idioma"},
	/* fr */ {IDCLS_SPECIFY_ISO_LANG_CODE_FR, "SpÈcifier le code iso du langage"},
	/* hu */ {IDCLS_SPECIFY_ISO_LANG_CODE_HU, "Adja meg a nyelv iso kÛdj·t"},
	/* it */ {IDCLS_SPECIFY_ISO_LANG_CODE_IT, "Specifica il codice ISO della lingua"},
	/* ko */ {IDCLS_SPECIFY_ISO_LANG_CODE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_ISO_LANG_CODE_NL, "Geef de isocode van de taal"},
	/* pl */ {IDCLS_SPECIFY_ISO_LANG_CODE_PL, "Okre∂l kod iso jÍzyka"},
	/* ru */ {IDCLS_SPECIFY_ISO_LANG_CODE_RU, "Specify the iso code of the language"},
	/* sv */ {IDCLS_SPECIFY_ISO_LANG_CODE_SV, "Ange ISO-koden fˆr sprÂket"},
	/* tr */ {IDCLS_SPECIFY_ISO_LANG_CODE_TR, "Dil iÁin iso kodu belirt"},
#endif
	
	/* c64/plus256k.c */
	/* en */ {IDCLS_ENABLE_PLUS256K_EXPANSION,    N_("Enable the PLUS256K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_PLUS256K_EXPANSION_DA, "AktivÈr PLUS256K RAM-udviddelse"},
	/* de */ {IDCLS_ENABLE_PLUS256K_EXPANSION_DE, "PLUS256K RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_PLUS256K_EXPANSION_ES, "Permitir expansiÛn RAM PLUS256K"},
	/* fr */ {IDCLS_ENABLE_PLUS256K_EXPANSION_FR, "Activer l'expansion PLUS256K RAM"},
	/* hu */ {IDCLS_ENABLE_PLUS256K_EXPANSION_HU, "PLUS256K RAM kiterjesztÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_PLUS256K_EXPANSION_IT, "Attiva l'espansione RAM PLUS256K"},
	/* ko */ {IDCLS_ENABLE_PLUS256K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_PLUS256K_EXPANSION_NL, "Activeer de PLUS256K geheugenuitbreiding"},
	/* pl */ {IDCLS_ENABLE_PLUS256K_EXPANSION_PL, "W≥±cz rozszerzenie RAM PLUS256K"},
	/* ru */ {IDCLS_ENABLE_PLUS256K_EXPANSION_RU, "Enable the PLUS256K RAM expansion"},
	/* sv */ {IDCLS_ENABLE_PLUS256K_EXPANSION_SV, "Aktivera PLUS256K RAM-expansion"},
	/* tr */ {IDCLS_ENABLE_PLUS256K_EXPANSION_TR, "PLUS256K RAM geni˛letmesini aktif et"},
#endif
	
	/* c64/plus256k.c */
	/* en */ {IDCLS_DISABLE_PLUS256K_EXPANSION,    N_("Disable the PLUS256K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_PLUS256K_EXPANSION_DA, "DeaktivÈr PLUS256K RAM-udviddelse"},
	/* de */ {IDCLS_DISABLE_PLUS256K_EXPANSION_DE, "PLUS256K RAM Erweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_PLUS256K_EXPANSION_ES, "Deshabilitar expansiÛn RAM PLUS256K"},
	/* fr */ {IDCLS_DISABLE_PLUS256K_EXPANSION_FR, "DÈsactiver l'expansion PLUS256K RAM"},
	/* hu */ {IDCLS_DISABLE_PLUS256K_EXPANSION_HU, "PLUS256K RAM kiterjesztÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_PLUS256K_EXPANSION_IT, "Disattiva l'espansione RAM PLUS256K"},
	/* ko */ {IDCLS_DISABLE_PLUS256K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_PLUS256K_EXPANSION_NL, "De PLUS256K geheugenuitbreiding uitschakelen"},
	/* pl */ {IDCLS_DISABLE_PLUS256K_EXPANSION_PL, "Wy≥±cz rozszerzenie RAM PLUS256K"},
	/* ru */ {IDCLS_DISABLE_PLUS256K_EXPANSION_RU, "Disable the PLUS256K RAM expansion"},
	/* sv */ {IDCLS_DISABLE_PLUS256K_EXPANSION_SV, "Inaktivera PLUS256K RAM-expansion"},
	/* tr */ {IDCLS_DISABLE_PLUS256K_EXPANSION_TR, "PLUS256K RAM geni˛letmesini pasifle˛tir"},
#endif
	
	/* c64/plus256k.c */
	/* en */ {IDCLS_SPECIFY_PLUS256K_NAME,    N_("Specify name of PLUS256K image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PLUS256K_NAME_DA, "Angiv navn pÂ PLUS256K-image"},
	/* de */ {IDCLS_SPECIFY_PLUS256K_NAME_DE, "Name der PLUS256K Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_PLUS256K_NAME_ES, "Especificar nombre imagen RAM PLUS256K"},
	/* fr */ {IDCLS_SPECIFY_PLUS256K_NAME_FR, "SpÈcifier le nom de l'image PLUS256K RAM"},
	/* hu */ {IDCLS_SPECIFY_PLUS256K_NAME_HU, "Adja meg a PLUS256K-s kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_PLUS256K_NAME_IT, "Specifica il nome immagine PLUS256K"},
	/* ko */ {IDCLS_SPECIFY_PLUS256K_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PLUS256K_NAME_NL, "Geef de naam van het PLUS256K bestand"},
	/* pl */ {IDCLS_SPECIFY_PLUS256K_NAME_PL, "Okre∂l nazwÍ obrazu PLUS256K"},
	/* ru */ {IDCLS_SPECIFY_PLUS256K_NAME_RU, "Specify name of PLUS256K image"},
	/* sv */ {IDCLS_SPECIFY_PLUS256K_NAME_SV, "Ange namn pÂ PLUS256K-avbildning"},
	/* tr */ {IDCLS_SPECIFY_PLUS256K_NAME_TR, "PLUS256K imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/plus60k.c */
	/* en */ {IDCLS_ENABLE_PLUS60K_EXPANSION,    N_("Enable the PLUS60K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_PLUS60K_EXPANSION_DA, "AktivÈr PLUS60K RAM-udviddelse"},
	/* de */ {IDCLS_ENABLE_PLUS60K_EXPANSION_DE, "PLUS60K RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_PLUS60K_EXPANSION_ES, "Permitir expansiÛn RAM PLUS60K"},
	/* fr */ {IDCLS_ENABLE_PLUS60K_EXPANSION_FR, "Activer l'expansion PLUS60K RAM"},
	/* hu */ {IDCLS_ENABLE_PLUS60K_EXPANSION_HU, "PLUS60K RAM bıvÌtÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_PLUS60K_EXPANSION_IT, "Attiva l'espansione RAM PLUS60K"},
	/* ko */ {IDCLS_ENABLE_PLUS60K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_PLUS60K_EXPANSION_NL, "Activeer de PLUS60K geheugenuitbreiding"},
	/* pl */ {IDCLS_ENABLE_PLUS60K_EXPANSION_PL, "W≥±cz rozszerzenie RAM PLUS60K"},
	/* ru */ {IDCLS_ENABLE_PLUS60K_EXPANSION_RU, "Enable the PLUS60K RAM expansion"},
	/* sv */ {IDCLS_ENABLE_PLUS60K_EXPANSION_SV, "Aktivera PLUS60K RAM-expansionen"},
	/* tr */ {IDCLS_ENABLE_PLUS60K_EXPANSION_TR, "PLUS60K RAM geni˛letmesini aktif et"},
#endif
	
	/* c64/plus60k.c */
	/* en */ {IDCLS_DISABLE_PLUS60K_EXPANSION,    N_("Disable the PLUS60K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_PLUS60K_EXPANSION_DA, "DeaktivÈr PLUS60K RAM-udviddelse"},
	/* de */ {IDCLS_DISABLE_PLUS60K_EXPANSION_DE, "PLUS60K RAM Erweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_PLUS60K_EXPANSION_ES, "Deshabilitar expansiÛn RAM PLUS60K"},
	/* fr */ {IDCLS_DISABLE_PLUS60K_EXPANSION_FR, "DÈsactiver l'expansion PLUS60K RAM"},
	/* hu */ {IDCLS_DISABLE_PLUS60K_EXPANSION_HU, "PLUS60K RAM bıvÌtÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_PLUS60K_EXPANSION_IT, "Disattiva l'espansione RAM PLUS60K"},
	/* ko */ {IDCLS_DISABLE_PLUS60K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_PLUS60K_EXPANSION_NL, "De PLUS60K geheugenuitbreiding uitschakelen"},
	/* pl */ {IDCLS_DISABLE_PLUS60K_EXPANSION_PL, "Wy≥±cz rozszerzenie RAM PLUS60K"},
	/* ru */ {IDCLS_DISABLE_PLUS60K_EXPANSION_RU, "Disable the PLUS60K RAM expansion"},
	/* sv */ {IDCLS_DISABLE_PLUS60K_EXPANSION_SV, "Inaktivera PLUS60K RAM-expansion"},
	/* tr */ {IDCLS_DISABLE_PLUS60K_EXPANSION_TR, "PLUS60K RAM geni˛letmesini pasifle˛tir"},
#endif
	
	/* c64/plus60k.c */
	/* en */ {IDCLS_SPECIFY_PLUS60K_NAME,    N_("Specify name of PLUS60K image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_PLUS60K_NAME_DA, "Angiv navn pÂ PLUS60K-image"},
	/* de */ {IDCLS_SPECIFY_PLUS60K_NAME_DE, "Name der PLUS60K Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_PLUS60K_NAME_ES, "Especificar nombe imagen PLUS60K"},
	/* fr */ {IDCLS_SPECIFY_PLUS60K_NAME_FR, "SpÈcifier le nom de l'image PLUS60K RAM"},
	/* hu */ {IDCLS_SPECIFY_PLUS60K_NAME_HU, "Adja meg a nevÈt a PLUS60K kÈpm·snak"},
	/* it */ {IDCLS_SPECIFY_PLUS60K_NAME_IT, "Specifica il nome immagine PLUS60K"},
	/* ko */ {IDCLS_SPECIFY_PLUS60K_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_PLUS60K_NAME_NL, "Geef de naam van het PLUS60K bestand"},
	/* pl */ {IDCLS_SPECIFY_PLUS60K_NAME_PL, "Okre∂l nazwÍ obrazu PLUS60K"},
	/* ru */ {IDCLS_SPECIFY_PLUS60K_NAME_RU, "Specify name of PLUS60K image"},
	/* sv */ {IDCLS_SPECIFY_PLUS60K_NAME_SV, "Ange namn pÂ plUS60K-avbildning"},
	/* tr */ {IDCLS_SPECIFY_PLUS60K_NAME_TR, "PLUS60K imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/plus60k.c */
	/* en */ {IDCLS_PLUS60K_BASE,    N_("Base address of the PLUS60K expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_PLUS60K_BASE_DA, "Baseadresse for PLUS60K-udviddelse"},
	/* de */ {IDCLS_PLUS60K_BASE_DE, "Basis Adresse f¸r PLUS60K Erweiterung"},
	/* es */ {IDCLS_PLUS60K_BASE_ES, "DirecciÛn base de la expansiÛn PLUS60K"},
	/* fr */ {IDCLS_PLUS60K_BASE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_PLUS60K_BASE_HU, "A PLUS60K bıvÌtÈs b·ziscÌme"},
	/* it */ {IDCLS_PLUS60K_BASE_IT, "Indirizzo base espansione PLUS60K"},
	/* ko */ {IDCLS_PLUS60K_BASE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_PLUS60K_BASE_NL, "Basisadres van de PLUS60K geheugenuitbreiding"},
	/* pl */ {IDCLS_PLUS60K_BASE_PL, "Adres bazowy rozszerzenia PLUS60K"},
	/* ru */ {IDCLS_PLUS60K_BASE_RU, "Base address of the PLUS60K expansion"},
	/* sv */ {IDCLS_PLUS60K_BASE_SV, "Basadress fˆr PLUS60K-expansion"},
	/* tr */ {IDCLS_PLUS60K_BASE_TR, "PLUS60K geni˛letmesinin taban adresi"},
#endif
	
	/* c64/c64_256k.c */
	/* en */ {IDCLS_ENABLE_C64_256K_EXPANSION,    N_("Enable the 256K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_C64_256K_EXPANSION_DA, "AktivÈr 256k RAM-udviddelse"},
	/* de */ {IDCLS_ENABLE_C64_256K_EXPANSION_DE, "256K RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_C64_256K_EXPANSION_ES, "Permitir expansiÛn RAM 256K"},
	/* fr */ {IDCLS_ENABLE_C64_256K_EXPANSION_FR, "Activer l'expansion RAM 256K"},
	/* hu */ {IDCLS_ENABLE_C64_256K_EXPANSION_HU, "256K RAM kiterjesztÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_C64_256K_EXPANSION_IT, "Attiva l'espansione 256K RAM"},
	/* ko */ {IDCLS_ENABLE_C64_256K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_C64_256K_EXPANSION_NL, "Activeer de 256K geheugenuitbreiding"},
	/* pl */ {IDCLS_ENABLE_C64_256K_EXPANSION_PL, "W≥±cz rozszerzenie RAM 256K"},
	/* ru */ {IDCLS_ENABLE_C64_256K_EXPANSION_RU, "Enable the 256K RAM expansion"},
	/* sv */ {IDCLS_ENABLE_C64_256K_EXPANSION_SV, "Aktivera 256K RAM-expansion"},
	/* tr */ {IDCLS_ENABLE_C64_256K_EXPANSION_TR, "256K RAM geni˛letmesini aktif et"},
#endif
	
	/* c64/c64_256k.c */
	/* en */ {IDCLS_DISABLE_C64_256K_EXPANSION,    N_("Disable the 256K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_C64_256K_EXPANSION_DA, "DeaktivÈr 256k RAM-udviddelse"},
	/* de */ {IDCLS_DISABLE_C64_256K_EXPANSION_DE, "256K RAM Erweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_C64_256K_EXPANSION_ES, "Deshabilitar expansiÛn RAM 256K"},
	/* fr */ {IDCLS_DISABLE_C64_256K_EXPANSION_FR, "DÈsactiver l'expansion RAM 256K"},
	/* hu */ {IDCLS_DISABLE_C64_256K_EXPANSION_HU, "256K RAM kiterjesztÈs tilt·sa"},
	/* it */ {IDCLS_DISABLE_C64_256K_EXPANSION_IT, "Disattiva l'espansione 256K RAM"},
	/* ko */ {IDCLS_DISABLE_C64_256K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_C64_256K_EXPANSION_NL, "De 256K geheugenuitbreiding uitschakelen"},
	/* pl */ {IDCLS_DISABLE_C64_256K_EXPANSION_PL, "Wy≥±cz rozszerzenie RAM 256K"},
	/* ru */ {IDCLS_DISABLE_C64_256K_EXPANSION_RU, "Disable the 256K RAM expansion"},
	/* sv */ {IDCLS_DISABLE_C64_256K_EXPANSION_SV, "Inaktivera 256K RAM-expansion"},
	/* tr */ {IDCLS_DISABLE_C64_256K_EXPANSION_TR, "256K RAM geni˛letmesini pasifle˛tir"},
#endif
	
	/* c64/c64_256k.c */
	/* en */ {IDCLS_SPECIFY_C64_256K_NAME,    N_("Specify name of 256K image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_C64_256K_NAME_DA, "Angiv navn pÂ 256k-image"},
	/* de */ {IDCLS_SPECIFY_C64_256K_NAME_DE, "Name der 256K Image Datei definieren"},
	/* es */ {IDCLS_SPECIFY_C64_256K_NAME_ES, "Especificar nombre imagen 256K"},
	/* fr */ {IDCLS_SPECIFY_C64_256K_NAME_FR, "SpÈcifier le nom de l'image 256K"},
	/* hu */ {IDCLS_SPECIFY_C64_256K_NAME_HU, "Adja meg a 256K-s kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_C64_256K_NAME_IT, "Specifica il nome immagine 256K"},
	/* ko */ {IDCLS_SPECIFY_C64_256K_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_C64_256K_NAME_NL, "Geef de naam van het 256K bestand"},
	/* pl */ {IDCLS_SPECIFY_C64_256K_NAME_PL, "Okre∂l nazwÍ obrazu 256K"},
	/* ru */ {IDCLS_SPECIFY_C64_256K_NAME_RU, "Specify name of 256K image"},
	/* sv */ {IDCLS_SPECIFY_C64_256K_NAME_SV, "Ange namn pÂ 256K-avbildning"},
	/* tr */ {IDCLS_SPECIFY_C64_256K_NAME_TR, "256K imaj˝n˝n ismini belirt"},
#endif
	
	/* c64/c64_256k.c */
	/* en */ {IDCLS_C64_256K_BASE,    N_("Base address of the 256K expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_C64_256K_BASE_DA, "Baseadresse for 256k-udviddelse"},
	/* de */ {IDCLS_C64_256K_BASE_DE, "Basis Adresse f¸r 256K RAM Erweiterung"},
	/* es */ {IDCLS_C64_256K_BASE_ES, "DirecciÛn base de la expansiÛn 256K"},
	/* fr */ {IDCLS_C64_256K_BASE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_C64_256K_BASE_HU, "A 256K-s RAM kiterjesztÈs b·ziscÌme"},
	/* it */ {IDCLS_C64_256K_BASE_IT, "Indirizzo base dell'espansione 256K"},
	/* ko */ {IDCLS_C64_256K_BASE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_C64_256K_BASE_NL, "Basisadres van de 256K geheugenuitbreiding"},
	/* pl */ {IDCLS_C64_256K_BASE_PL, "Adres bazowy rozszerzenia 256K"},
	/* ru */ {IDCLS_C64_256K_BASE_RU, "Base address of the 256K expansion"},
	/* sv */ {IDCLS_C64_256K_BASE_SV, "Basadress fˆr 256K-expansionen"},
	/* tr */ {IDCLS_C64_256K_BASE_TR, "256K geni˛letmesinin taban adresi"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_STB_CART,    N_("Attach raw Structured Basic cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_STB_CART_DA, "Tilslut rÂ Strucured BASIC-cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_STB_CART_DE, "Erweiterungsmodul Structured Basic (raw) Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_STB_CART_ES, "Insertar imagen cartucho Structured Basic"},
	/* fr */ {IDCLS_ATTACH_RAW_STB_CART_FR, "InsÈrer une cartouche Raw Structured Basic"},
	/* hu */ {IDCLS_ATTACH_RAW_STB_CART_HU, "Structured Basic cartridge kÈpm·s csatol·sa"},
	/* it */ {IDCLS_ATTACH_RAW_STB_CART_IT, "Seleziona immagine cartuccia Structured Basic"},
	/* ko */ {IDCLS_ATTACH_RAW_STB_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_STB_CART_NL, "Koppel binair Structured Basic cartridge bestand aan"},
	/* pl */ {IDCLS_ATTACH_RAW_STB_CART_PL, "Zamontuj surowy obraz kartridøa Structured Basic"},
	/* ru */ {IDCLS_ATTACH_RAW_STB_CART_RU, "Attach raw Structured Basic cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_STB_CART_SV, "Anslut rÂ Strucured Basic-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_STB_CART_TR, "D¸z yap˝land˝r˝lm˝˛ Basic kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_SE5_CART,    N_("Attach raw 16kB Super Explode V5 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_SE5_CART_DA, "Tilslut rÂt 16kB Super Explode V5 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_SE5_CART_DE, "16kB Super Explode V5 Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_SE5_CART_ES, "Insertar imagen cartucho Super Explode V5 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_SE5_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_SE5_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_SE5_CART_IT, "Seleziona immagine cartuccia Super Explode V5 di 16kB"},
	/* ko */ {IDCLS_ATTACH_RAW_SE5_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_SE5_CART_NL, "Koppel binair 16kB Super Snapshot V5 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_SE5_CART_PL, "Zamontuj surowy obraz kartridøa 16kB Super Explode V5"},
	/* ru */ {IDCLS_ATTACH_RAW_SE5_CART_RU, "Attach raw 16kB Super Explode V5 cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_SE5_CART_SV, "Anslut rÂ 16kB Super Explode V5-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_SE5_CART_TR, "D¸z 16kB Super Explode V5 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART,    N_("Attach raw 64kB Super Games cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_DA, "Tilslut rÂt 64kB Super Games cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_DE, "64kB Super Games Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_ES, "Insertar imagen cartucho Super Games 64KB"},
	/* fr */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_IT, "Seleziona immagine cartuccia Super Games di 64kB"},
	/* ko */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_NL, "Koppel binair 64kB Super Games cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_PL, "Zamontuj surowy obraz kartridøa 64kB Super Games"},
	/* ru */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_RU, "Attach raw 64kB Super Games cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_SV, "Anslut rÂ 64kB-Super Games-insticksmodulfil"},
	/* tr */ {IDCLS_ATTACH_RAW_SUPER_GAMES_CART_TR, "D¸z 64kB Super Games kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART,    N_("Attach raw Silverrock 128 cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_DA, "Tilslut rÂt Silverrock 128 cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_DE, "Silverrock 128 Erweiterungsmodul (raw) Image einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_ES, "Insertar imagen cartucho Silverrock 128"},
	/* fr */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_IT, "Seleziona immagine cartuccia Silverrock 128"},
	/* ko */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_NL, "Koppel binair Silverrock 128 cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_PL, "Zamontuj surowy obraz kartridøa Silverrock 128"},
	/* ru */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_SV, "Anslut rÂ Silverrock 128-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_SILVERROCK_128_CART_TR, "D¸z Silverrock 128 kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* c64/cart/c64cart.c */
	/* en */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART,    N_("Attach raw 16kB Simons Basic cartridge image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_DA, "Tilslut rÂt 16kB Simons Basic cartridge image"},
	/* de */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_DE, "16kB Simons Basic Image (raw) einlegen"},
	/* es */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_ES, "Insertar imagen cartucho Simons Basic 16KB"},
	/* fr */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_IT, "Seleziona immagine cartuccia Simons Basic di 16kB"},
	/* ko */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_NL, "Koppel binair 16kB Simons Basic cartridge bestand"},
	/* pl */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_PL, "Zamontuj surowy obraz kartridøa 16kB Simons Basic"},
	/* ru */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_RU, "Attach raw 16kB Simons Basic cartridge image"},
	/* sv */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_SV, "Anslut rÂ 16kB Simons Basic-insticksmodulavbildning"},
	/* tr */ {IDCLS_ATTACH_RAW_SIMONS_BASIC_CART_TR, "D¸z 16kB Simons Basic kartu˛ imaj˝ yerle˛tir"},
#endif
	
	/* plus4/plus4memcsory256k.c */
	/* en */ {IDCLS_ENABLE_CS256K_EXPANSION,    N_("Enable the CSORY 256K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_CS256K_EXPANSION_DA, "AktivÈr CSORY 256k RAM-udviddelse"},
	/* de */ {IDCLS_ENABLE_CS256K_EXPANSION_DE, "CSORY 256K RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_CS256K_EXPANSION_ES, "Permitir expansiÛn RAM CSORY 256KB"},
	/* fr */ {IDCLS_ENABLE_CS256K_EXPANSION_FR, "Activer l'expansion RAM 256K CSORY"},
	/* hu */ {IDCLS_ENABLE_CS256K_EXPANSION_HU, "CSORY 256K RAM kiterjesztÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_CS256K_EXPANSION_IT, "Attiva l'espansione RAM CSORY 256K"},
	/* ko */ {IDCLS_ENABLE_CS256K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_CS256K_EXPANSION_NL, "Activeer de CSORY 256K geheugenuitbreiding"},
	/* pl */ {IDCLS_ENABLE_CS256K_EXPANSION_PL, "W≥±cz rozszerzenie RAM CSORY 256K"},
	/* ru */ {IDCLS_ENABLE_CS256K_EXPANSION_RU, "Enable the CSORY 256K RAM expansion"},
	/* sv */ {IDCLS_ENABLE_CS256K_EXPANSION_SV, "Aktivera CSORY 256K RAM-expansion"},
	/* tr */ {IDCLS_ENABLE_CS256K_EXPANSION_TR, "CSORY 256K RAM geni˛letmesini aktif et"},
#endif
	
	/* plus4/plus4memhannes256k.c */
	/* en */ {IDCLS_ENABLE_H256K_EXPANSION,    N_("Enable the HANNES 256K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_H256K_EXPANSION_DA, "AktivÈr HANNES 256k RAM-udviddelse"},
	/* de */ {IDCLS_ENABLE_H256K_EXPANSION_DE, "HANNES 256K RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_H256K_EXPANSION_ES, "Permitir expansiÛn RAM HANNES 256KB"},
	/* fr */ {IDCLS_ENABLE_H256K_EXPANSION_FR, "Activer l'expansion RAM 256K HANNES"},
	/* hu */ {IDCLS_ENABLE_H256K_EXPANSION_HU, "HANNES 256K RAM kiterjesztÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_H256K_EXPANSION_IT, "Attiva l'espansione RAM HANNES 256K"},
	/* ko */ {IDCLS_ENABLE_H256K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_H256K_EXPANSION_NL, "Activeer de HANNES 256K geheugenuitbreiding"},
	/* pl */ {IDCLS_ENABLE_H256K_EXPANSION_PL, "W≥±cz rozszerzenie RAM HANNES 256K"},
	/* ru */ {IDCLS_ENABLE_H256K_EXPANSION_RU, "Enable the HANNES 256K RAM expansion"},
	/* sv */ {IDCLS_ENABLE_H256K_EXPANSION_SV, "Aktivera HANNES 256K RAM-expansion"},
	/* tr */ {IDCLS_ENABLE_H256K_EXPANSION_TR, "HANNES 256K RAM geni˛letmesini aktif et"},
#endif
	
	/* plus4/plus4memhannes256k.c */
	/* en */ {IDCLS_ENABLE_H1024K_EXPANSION,    N_("Enable the HANNES 1024K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_H1024K_EXPANSION_DA, "AktivÈr HANNES 1024k RAM-udviddelse"},
	/* de */ {IDCLS_ENABLE_H1024K_EXPANSION_DE, "HANNES 1024K RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_H1024K_EXPANSION_ES, "Permitir expansiÛn RAM HANNES 1024KB"},
	/* fr */ {IDCLS_ENABLE_H1024K_EXPANSION_FR, "Activer l'expansion RAM 1024K HANNES"},
	/* hu */ {IDCLS_ENABLE_H1024K_EXPANSION_HU, "HANNES 1024K RAM kiterjesztÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_H1024K_EXPANSION_IT, "Attiva l'espansione RAM HANNES 1024K"},
	/* ko */ {IDCLS_ENABLE_H1024K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_H1024K_EXPANSION_NL, "Activeer de HANNES 1024K geheugenuitbreiding"},
	/* pl */ {IDCLS_ENABLE_H1024K_EXPANSION_PL, "W≥±cz rozszerzenie HANNES 1024K RAM"},
	/* ru */ {IDCLS_ENABLE_H1024K_EXPANSION_RU, "Enable the HANNES 1024K RAM expansion"},
	/* sv */ {IDCLS_ENABLE_H1024K_EXPANSION_SV, "Aktivera HANNES 1024K RAM-expansion"},
	/* tr */ {IDCLS_ENABLE_H1024K_EXPANSION_TR, "HANNES 1024K RAM geni˛letmesini aktif et"},
#endif
	
	/* plus4/plus4memhannes256k.c */
	/* en */ {IDCLS_ENABLE_H4096K_EXPANSION,    N_("Enable the HANNES 4096K RAM expansion")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_H4096K_EXPANSION_DA, "AktivÈr HANNES 4096k RAM-udviddelse"},
	/* de */ {IDCLS_ENABLE_H4096K_EXPANSION_DE, "HANNES 4096K RAM Erweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_H4096K_EXPANSION_ES, "Permitir expansiÛn RAM HANNES 4096KB"},
	/* fr */ {IDCLS_ENABLE_H4096K_EXPANSION_FR, "Activer l'expansion RAM 4096K HANNES"},
	/* hu */ {IDCLS_ENABLE_H4096K_EXPANSION_HU, "HANNES 4096K RAM kiterjesztÈs engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_H4096K_EXPANSION_IT, "Attiva l'espansione RAM HANNES 4096K"},
	/* ko */ {IDCLS_ENABLE_H4096K_EXPANSION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_H4096K_EXPANSION_NL, "Activeer de HANNES 4096K geheugenuitbreiding"},
	/* pl */ {IDCLS_ENABLE_H4096K_EXPANSION_PL, "W≥±cz rozszerzenie HANNES 4096K RAM"},
	/* ru */ {IDCLS_ENABLE_H4096K_EXPANSION_RU, "Enable the HANNES 4096K RAM expansion"},
	/* sv */ {IDCLS_ENABLE_H4096K_EXPANSION_SV, "Aktivera HANNES 4096K RAM-expansion"},
	/* tr */ {IDCLS_ENABLE_H4096K_EXPANSION_TR, "HANNES 4096K RAM geni˛letmesini aktif et"},
#endif
	
	/* c64dtv/c64dtvblitter.c */
	/* en */ {IDCLS_SPECIFY_DTV_REVISION,    N_("Specify DTV Revision (2: DTV2, 3: DTV3)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_DTV_REVISION_DA, "Angiv DTV-revision (2: DTV2, 3: DTV3)"},
	/* de */ {IDCLS_SPECIFY_DTV_REVISION_DE, "DTV Revision definieren (2: DTV2, 3: DTV3)"},
	/* es */ {IDCLS_SPECIFY_DTV_REVISION_ES, "Especificar revisiÛn DTV (2: DTV2, 3: DTV3)"},
	/* fr */ {IDCLS_SPECIFY_DTV_REVISION_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_DTV_REVISION_HU, "Adja meg a DTV verziÛj·t (2: DTV2, 3: DTV3)"},
	/* it */ {IDCLS_SPECIFY_DTV_REVISION_IT, "Specifica la revisione DTV (2: DTV2, 3: DTV3)"},
	/* ko */ {IDCLS_SPECIFY_DTV_REVISION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_DTV_REVISION_NL, "Geef de DTV revisie (2: DTV2, 3: DTV3)"},
	/* pl */ {IDCLS_SPECIFY_DTV_REVISION_PL, "Okre∂l wersjÍ DTV (2: DTV2, 3: DTV3)"},
	/* ru */ {IDCLS_SPECIFY_DTV_REVISION_RU, "Specify DTV Revision (2: DTV2, 3: DTV3)"},
	/* sv */ {IDCLS_SPECIFY_DTV_REVISION_SV, "Ange DTV-revision (2: DTV2, 3: DTV3)"},
	/* tr */ {IDCLS_SPECIFY_DTV_REVISION_TR, "DTV Revizyonunu belirt (2: DTV2, 3: DTV3)"},
#endif
	
	/* c64dtv/c64dtvblitter.c */
	/* en */ {IDCLS_ENABLE_DTV_BLITTER_LOG,    N_("Enable DTV blitter logs.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DTV_BLITTER_LOG_DA, "AktivÈr DTV-blitterlog."},
	/* de */ {IDCLS_ENABLE_DTV_BLITTER_LOG_DE, "DTV Blitter Log aktivieren."},
	/* es */ {IDCLS_ENABLE_DTV_BLITTER_LOG_ES, "Permitir informes blitter DTV"},
	/* fr */ {IDCLS_ENABLE_DTV_BLITTER_LOG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DTV_BLITTER_LOG_HU, "DTV blit naplÛk engedÈlyezÈse."},
	/* it */ {IDCLS_ENABLE_DTV_BLITTER_LOG_IT, "Attiva log del blitter DTV."},
	/* ko */ {IDCLS_ENABLE_DTV_BLITTER_LOG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DTV_BLITTER_LOG_NL, "Aktiveer DTV blitter logs."},
	/* pl */ {IDCLS_ENABLE_DTV_BLITTER_LOG_PL, "W≥±cz logi blittera DTV."},
	/* ru */ {IDCLS_ENABLE_DTV_BLITTER_LOG_RU, "Enable DTV blitter logs."},
	/* sv */ {IDCLS_ENABLE_DTV_BLITTER_LOG_SV, "Aktivera DTV-blitterloggar."},
	/* tr */ {IDCLS_ENABLE_DTV_BLITTER_LOG_TR, "DTV blitter loglar˝n˝ aktif et"},
#endif
	
	/* c64dtv/c64dtvblitter.c */
	/* en */ {IDCLS_DISABLE_DTV_BLITTER_LOG,    N_("Disable DTV blitter logs.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DTV_BLITTER_LOG_DA, "DeaktivÈr DTV-blitterlog."},
	/* de */ {IDCLS_DISABLE_DTV_BLITTER_LOG_DE, "DTV Blitter Log deaktivieren."},
	/* es */ {IDCLS_DISABLE_DTV_BLITTER_LOG_ES, "Deshabilitar informes blitter DTV"},
	/* fr */ {IDCLS_DISABLE_DTV_BLITTER_LOG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DTV_BLITTER_LOG_HU, "DTV blit naplÛk tilt·sa."},
	/* it */ {IDCLS_DISABLE_DTV_BLITTER_LOG_IT, "Disattiva log del blitter DTV."},
	/* ko */ {IDCLS_DISABLE_DTV_BLITTER_LOG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DTV_BLITTER_LOG_NL, "DTV Blitter logs uitschakelen."},
	/* pl */ {IDCLS_DISABLE_DTV_BLITTER_LOG_PL, "Wy≥±cz logi blittera DTV"},
	/* ru */ {IDCLS_DISABLE_DTV_BLITTER_LOG_RU, "Disable DTV blitter logs."},
	/* sv */ {IDCLS_DISABLE_DTV_BLITTER_LOG_SV, "Inaktivera DTV-blitterloggar."},
	/* tr */ {IDCLS_DISABLE_DTV_BLITTER_LOG_TR, "DTV blitter loglar˝n˝ pasifle˛tir"},
#endif
	
	/* c64dtv/c64dtvdma.c */
	/* en */ {IDCLS_ENABLE_DTV_DMA_LOG,    N_("Enable DTV DMA logs.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DTV_DMA_LOG_DA, "AktivÈr DTV DMA-log."},
	/* de */ {IDCLS_ENABLE_DTV_DMA_LOG_DE, "DTV DMA Logs aktivieren."},
	/* es */ {IDCLS_ENABLE_DTV_DMA_LOG_ES, "Permitir informes DTV DMA."},
	/* fr */ {IDCLS_ENABLE_DTV_DMA_LOG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DTV_DMA_LOG_HU, "DTV DMA naplÛk engedÈlyezÈse."},
	/* it */ {IDCLS_ENABLE_DTV_DMA_LOG_IT, "Attiva log DMA DTV."},
	/* ko */ {IDCLS_ENABLE_DTV_DMA_LOG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DTV_DMA_LOG_NL, "Aktiveer DTV DMA logs."},
	/* pl */ {IDCLS_ENABLE_DTV_DMA_LOG_PL, "W≥±cz logowanie DTV DMA"},
	/* ru */ {IDCLS_ENABLE_DTV_DMA_LOG_RU, "Enable DTV DMA logs."},
	/* sv */ {IDCLS_ENABLE_DTV_DMA_LOG_SV, "Aktivera DTV DMA-loggning."},
	/* tr */ {IDCLS_ENABLE_DTV_DMA_LOG_TR, "DTV DMA loglar˝n˝ aktif et"},
#endif
	
	/* c64dtv/c64dtvdma.c */
	/* en */ {IDCLS_DISABLE_DTV_DMA_LOG,    N_("Disable DTV DMA logs.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DTV_DMA_LOG_DA, "DeaktivÈr DTV DMA-log."},
	/* de */ {IDCLS_DISABLE_DTV_DMA_LOG_DE, "DTV DMA Logs deaktivieren."},
	/* es */ {IDCLS_DISABLE_DTV_DMA_LOG_ES, "Deshabilitar informes DTV DMA."},
	/* fr */ {IDCLS_DISABLE_DTV_DMA_LOG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DTV_DMA_LOG_HU, "DTV DMA naplÛk tilt·sa."},
	/* it */ {IDCLS_DISABLE_DTV_DMA_LOG_IT, "Disattiva log DMA DTV."},
	/* ko */ {IDCLS_DISABLE_DTV_DMA_LOG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DTV_DMA_LOG_NL, "DTV DMA logs uitschakelen."},
	/* pl */ {IDCLS_DISABLE_DTV_DMA_LOG_PL, "Wy≥±cz logowanie DTV DMA"},
	/* ru */ {IDCLS_DISABLE_DTV_DMA_LOG_RU, "Disable DTV DMA logs."},
	/* sv */ {IDCLS_DISABLE_DTV_DMA_LOG_SV, "Inaktivera DTV DMA-loggning."},
	/* tr */ {IDCLS_DISABLE_DTV_DMA_LOG_TR, "DTV DMA loglar˝n˝ pasifle˛tir"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDCLS_SPECIFY_C64DTVROM_NAME,    N_("Specify name of C64DTV ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_C64DTVROM_NAME_DA, "Angiv navn pÂ C64DTV-ROM-image"},
	/* de */ {IDCLS_SPECIFY_C64DTVROM_NAME_DE, "Name von C64DTV ROM Datei definieren"},
	/* es */ {IDCLS_SPECIFY_C64DTVROM_NAME_ES, "Especificar nombre imagen ROM C64DTV"},
	/* fr */ {IDCLS_SPECIFY_C64DTVROM_NAME_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_C64DTVROM_NAME_HU, "Adja meg a C64DTV ROM kÈpm·s nevÈt"},
	/* it */ {IDCLS_SPECIFY_C64DTVROM_NAME_IT, "Specifica il nome immagine ROM DTV"},
	/* ko */ {IDCLS_SPECIFY_C64DTVROM_NAME_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_C64DTVROM_NAME_NL, "Geef de naam van her C64DTV ROM bestand"},
	/* pl */ {IDCLS_SPECIFY_C64DTVROM_NAME_PL, "Okre∂l nazwÍ obrazu ROM C64DTV"},
	/* ru */ {IDCLS_SPECIFY_C64DTVROM_NAME_RU, "Specify name of C64DTV ROM image"},
	/* sv */ {IDCLS_SPECIFY_C64DTVROM_NAME_SV, "Ange namn pÂ C64DTV-ROM-avbildning"},
	/* tr */ {IDCLS_SPECIFY_C64DTVROM_NAME_TR, "C64DTV ROM imaj˝n˝n ismini belirt"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDCLS_ENABLE_C64DTVROM_RW,    N_("Enable writes to C64DTV ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_C64DTVROM_RW_DA, "Tillad skrivning til DTV-ROM-image"},
	/* de */ {IDCLS_ENABLE_C64DTVROM_RW_DE, "Erlaube Schreibzugriff auf DTV ROM Datei"},
	/* es */ {IDCLS_ENABLE_C64DTVROM_RW_ES, "Permitir escritura en la imagen C64DTV ROM"},
	/* fr */ {IDCLS_ENABLE_C64DTVROM_RW_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_C64DTVROM_RW_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_C64DTVROM_RW_IT, "Attiva scrittura su immagini ROM C64DTV"},
	/* ko */ {IDCLS_ENABLE_C64DTVROM_RW_KO, "C64DTV ROM ¿ÃπÃ¡ˆø° æ≤±‚ ∞°¥…«œ∞‘ «œ±‚"},
	/* nl */ {IDCLS_ENABLE_C64DTVROM_RW_NL, "Aktiveer schrijven naar DTV ROM bestand"},
	/* pl */ {IDCLS_ENABLE_C64DTVROM_RW_PL, "W≥±cz zapis do obrazu ROM C64DTV"},
	/* ru */ {IDCLS_ENABLE_C64DTVROM_RW_RU, "Enable writes to C64DTV ROM image"},
	/* sv */ {IDCLS_ENABLE_C64DTVROM_RW_SV, "Aktivera skrivning till C64DTV-ROM-avbildning"},
	/* tr */ {IDCLS_ENABLE_C64DTVROM_RW_TR, "C64DTV ROM imaj˝nda yazmalar˝ aktif et"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDCLS_DISABLE_C64DTVROM_RW,    N_("Disable writes to C64DTV ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_C64DTVROM_RW_DA, "Forbyd skrivning til C64DTV-ROM-image."},
	/* de */ {IDCLS_DISABLE_C64DTVROM_RW_DE, "Schreibzugriff auf C64DTV ROM Image verhindern"},
	/* es */ {IDCLS_DISABLE_C64DTVROM_RW_ES, "Deshabilitar grabaciÛn en imagen  C64DTV ROM"},
	/* fr */ {IDCLS_DISABLE_C64DTVROM_RW_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_C64DTVROM_RW_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_C64DTVROM_RW_IT, "Disattiva scrittura sull'immagine ROM C64DTV"},
	/* ko */ {IDCLS_DISABLE_C64DTVROM_RW_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_C64DTVROM_RW_NL, "Schrijven naar C64DTV ROM bestand uitschakelen"},
	/* pl */ {IDCLS_DISABLE_C64DTVROM_RW_PL, "Wy≥±cz zapis do obrazu ROM C64DTV"},
	/* ru */ {IDCLS_DISABLE_C64DTVROM_RW_RU, "Disable writes to C64DTV ROM image"},
	/* sv */ {IDCLS_DISABLE_C64DTVROM_RW_SV, "Inaktivera skrivning till C64DTV-ROM-avbildning"},
	/* tr */ {IDCLS_DISABLE_C64DTVROM_RW_TR, "C64DTV ROM imaj˝na yazmay˝ pasifle˛tir"},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDCLS_ENABLE_DTV_FLASH_LOG,    N_("Enable DTV flash chip logs.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DTV_FLASH_LOG_DA, "AktivÈr logs for DTV-flashkreds."},
	/* de */ {IDCLS_ENABLE_DTV_FLASH_LOG_DE, "DTV Flashchip Log aktivieren."},
	/* es */ {IDCLS_ENABLE_DTV_FLASH_LOG_ES, "Permitir informes chip DTV flash"},
	/* fr */ {IDCLS_ENABLE_DTV_FLASH_LOG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DTV_FLASH_LOG_HU, "DTV flash chip naplÛk engedÈlyezÈse."},
	/* it */ {IDCLS_ENABLE_DTV_FLASH_LOG_IT, "Attiva log del chip flash DTV."},
	/* ko */ {IDCLS_ENABLE_DTV_FLASH_LOG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DTV_FLASH_LOG_NL, "Aktiveer DTV flash chip logs."},
	/* pl */ {IDCLS_ENABLE_DTV_FLASH_LOG_PL, "W≥±cz logi uk≥adu flash DTV."},
	/* ru */ {IDCLS_ENABLE_DTV_FLASH_LOG_RU, "Enable DTV flash chip logs."},
	/* sv */ {IDCLS_ENABLE_DTV_FLASH_LOG_SV, "Aktivera loggar fˆr DTV-flashkrets."},
	/* tr */ {IDCLS_ENABLE_DTV_FLASH_LOG_TR, "DTV flash Áip loglar˝n˝ aktif et."},
#endif
	
	/* c64dtv/c64dtvflash.c */
	/* en */ {IDCLS_DISABLE_DTV_FLASH_LOG,    N_("Disable DTV flash chip logs.")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DTV_FLASH_LOG_DA, "DeaktivÈr logs for DTV-flashkreds."},
	/* de */ {IDCLS_DISABLE_DTV_FLASH_LOG_DE, "DTV Flashchip Log deaktivieren."},
	/* es */ {IDCLS_DISABLE_DTV_FLASH_LOG_ES, "Inhabilitar informes chip DTV flash"},
	/* fr */ {IDCLS_DISABLE_DTV_FLASH_LOG_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DTV_FLASH_LOG_HU, "DTV flash chip naplÛk tilt·sa."},
	/* it */ {IDCLS_DISABLE_DTV_FLASH_LOG_IT, "Disattiva log del chip flash DTV."},
	/* ko */ {IDCLS_DISABLE_DTV_FLASH_LOG_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DTV_FLASH_LOG_NL, "DTV flash chip logs uitschakelen."},
	/* pl */ {IDCLS_DISABLE_DTV_FLASH_LOG_PL, "Wy≥±cz logi uk≥adu flash DTV"},
	/* ru */ {IDCLS_DISABLE_DTV_FLASH_LOG_RU, "Disable DTV flash chip logs."},
	/* sv */ {IDCLS_DISABLE_DTV_FLASH_LOG_SV, "Inaktivera loggar fˆr DTV-flashkrets."},
	/* tr */ {IDCLS_DISABLE_DTV_FLASH_LOG_TR, "DTV flash Áip loglar˝n˝ pasifle˛tir."},
#endif
	
	/* c64dtv/flash-trap.c */
	/* en */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS,    N_("Use <name> as directory for flash file system device")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_DA, "Brug <navn> som katalog for filsystembaseret flashenhed"},
	/* de */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_DE, "Benutze <Name> f¸r Verzeichnis Ger‰t Flash Dateisystem"},
	/* es */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_ES, "Usar <nombre> como directorio para perifÈrico flash files system"},
	/* fr */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_HU, "<nÈv> kˆnyvt·r haszn·lata a flash f·jlrendszer eszkˆzhˆz"},
	/* it */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_IT, "Una <nome> come directory per il file system flash"},
	/* ko */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_NL, "Gebruik <naam> als directory voor het flash bestandssysteem apparaat"},
	/* pl */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_PL, "Uøyj <nazwa> jako katalogu urz±dzenia systemu plikÛw flash"},
	/* ru */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_RU, "Use <name> as directory for flash file system device"},
	/* sv */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_SV, "Ange <namn> som katalog fˆr filsystemsbaserad flashenhet"},
	/* tr */ {IDCLS_USE_AS_DIRECTORY_FLASH_FS_TR, "Flash dosya sistem ayg˝t˝ iÁin <isim>'i dizin olarak kullan"},
#endif
	
	/* c64dtv/flash-trap.c */
	/* en */ {IDCLS_ENABLE_TRUE_FLASH_FS,    N_("Enable true hardware flash file system")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_TRUE_FLASH_FS_DA, "AktivÈr Êgte hardwareemulering af flashfilsystem"},
	/* de */ {IDCLS_ENABLE_TRUE_FLASH_FS_DE, "Pr‰zises Hardware Flashdateisystem aktivieren"},
	/* es */ {IDCLS_ENABLE_TRUE_FLASH_FS_ES, "Permitir flash file system verdadero (hardware)"},
	/* fr */ {IDCLS_ENABLE_TRUE_FLASH_FS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_TRUE_FLASH_FS_HU, "Igazi hardver flash f·jlrendszer engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_TRUE_FLASH_FS_IT, "Attiva emulazione hardware del file system flash"},
	/* ko */ {IDCLS_ENABLE_TRUE_FLASH_FS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_TRUE_FLASH_FS_NL, "Activeer hardwarmatige flash bestandssysteem"},
	/* pl */ {IDCLS_ENABLE_TRUE_FLASH_FS_PL, "W≥±cz prawdziwy sprzÍtowy system plikÛw flash"},
	/* ru */ {IDCLS_ENABLE_TRUE_FLASH_FS_RU, "Enable true hardware flash file system"},
	/* sv */ {IDCLS_ENABLE_TRUE_FLASH_FS_SV, "Aktivera ‰kta maskinvaru-flashfilsystem"},
	/* tr */ {IDCLS_ENABLE_TRUE_FLASH_FS_TR, "GerÁek donan˝m flash dosya sistemini aktif et"},
#endif
	
	/* c64dtv/flash-trap.c */
	/* en */ {IDCLS_DISABLE_TRUE_FLASH_FS,    N_("Disable true hardware flash file system")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_TRUE_FLASH_FS_DA, "DeaktivÈr Êgte hardwareemulering af flashfilsystem"},
	/* de */ {IDCLS_DISABLE_TRUE_FLASH_FS_DE, "Pr‰zises Hardware Flashdateisystem deaktivieren"},
	/* es */ {IDCLS_DISABLE_TRUE_FLASH_FS_ES, "Deshabilitar flash file system verdadero (hardware)"},
	/* fr */ {IDCLS_DISABLE_TRUE_FLASH_FS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_TRUE_FLASH_FS_HU, "Igazi hardver flash f·jlrendszer tilt·sa"},
	/* it */ {IDCLS_DISABLE_TRUE_FLASH_FS_IT, "Disattiva emulazione hardware del file system flash"},
	/* ko */ {IDCLS_DISABLE_TRUE_FLASH_FS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_TRUE_FLASH_FS_NL, "Hardwatematig flash bestandssysteem uitschakelen"},
	/* pl */ {IDCLS_DISABLE_TRUE_FLASH_FS_PL, "Wy≥±cz prawdziwy system plikÛw flash"},
	/* ru */ {IDCLS_DISABLE_TRUE_FLASH_FS_RU, "Disable true hardware flash file system"},
	/* sv */ {IDCLS_DISABLE_TRUE_FLASH_FS_SV, "Inaktivera maskinvaruemelring fˆr flashfilsystem"},
	/* tr */ {IDCLS_DISABLE_TRUE_FLASH_FS_TR, "GerÁek donan˝m flash dosya sistemini pasifle˛tir"},
#endif
	
#ifdef HAVE_MIDI
	/* midi.c */
	/* en */ {IDCLS_ENABLE_MIDI_EMU,    N_("Enable MIDI emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_MIDI_EMU_DA, "AktivÈr MIDI-emulering"},
	/* de */ {IDCLS_ENABLE_MIDI_EMU_DE, "MIDI Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_MIDI_EMU_ES, "Habilitar emulaciÛn MIDI"},
	/* fr */ {IDCLS_ENABLE_MIDI_EMU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_MIDI_EMU_HU, "MIDI emul·ciÛ engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_MIDI_EMU_IT, "Attiva emulazione MIDI"},
	/* ko */ {IDCLS_ENABLE_MIDI_EMU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_MIDI_EMU_NL, "Activeer MIDI emulatie"},
	/* pl */ {IDCLS_ENABLE_MIDI_EMU_PL, "W≥±cz emulacjÍ MIDI"},
	/* ru */ {IDCLS_ENABLE_MIDI_EMU_RU, "≤⁄€ÓÁÿ‚Ï Ì‹„€ÔÊÿÓ MIDI"},
	/* sv */ {IDCLS_ENABLE_MIDI_EMU_SV, "Aktivera MIDI-emulering"},
	/* tr */ {IDCLS_ENABLE_MIDI_EMU_TR, "MIDI em¸lasyonunu aktif et"},
#endif
	
	/* midi.c */
	/* en */ {IDCLS_DISABLE_MIDI_EMU,    N_("Disable MIDI emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_MIDI_EMU_DA, "DeaktivÈr MIDI-emulering"},
	/* de */ {IDCLS_DISABLE_MIDI_EMU_DE, "MIDI Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_MIDI_EMU_ES, "Deshabilitar emulaciÛn MIDI"},
	/* fr */ {IDCLS_DISABLE_MIDI_EMU_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_MIDI_EMU_HU, "MIDI emul·ciÛ tilt·sa"},
	/* it */ {IDCLS_DISABLE_MIDI_EMU_IT, "Disattiva emulazione MIDI"},
	/* ko */ {IDCLS_DISABLE_MIDI_EMU_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_MIDI_EMU_NL, "MIDI emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_MIDI_EMU_PL, "Wy≥±cz emulacjÍ MIDI"},
	/* ru */ {IDCLS_DISABLE_MIDI_EMU_RU, "Disable MIDI emulation"},
	/* sv */ {IDCLS_DISABLE_MIDI_EMU_SV, "Inaktivera MIDI-emulering"},
	/* tr */ {IDCLS_DISABLE_MIDI_EMU_TR, "MIDI em¸lasyonunu pasifle˛tir"},
#endif
	
	/* c64/cart/c64-midi.c */
	/* en */ {IDCLS_SPECIFY_C64_MIDI_TYPE,    N_("MIDI interface type (0: Sequential, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SPECIFY_C64_MIDI_TYPE_DA, "MIDI-interfacetype (0: Sekventiel, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* de */ {IDCLS_SPECIFY_C64_MIDI_TYPE_DE, "MIDI Interface Typ (0: Sequential, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* es */ {IDCLS_SPECIFY_C64_MIDI_TYPE_ES, "Tipo interface MIDI (0: Secuencial, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* fr */ {IDCLS_SPECIFY_C64_MIDI_TYPE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SPECIFY_C64_MIDI_TYPE_HU, "MIDI interfÈsz tÌpus (0: soros, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* it */ {IDCLS_SPECIFY_C64_MIDI_TYPE_IT, "Tipo interfaccia MIDI (0: Sequential, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* ko */ {IDCLS_SPECIFY_C64_MIDI_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SPECIFY_C64_MIDI_TYPE_NL, "MIDI interface soort (0: Sequential, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* pl */ {IDCLS_SPECIFY_C64_MIDI_TYPE_PL, "Typ interfejsu MIDI (0: Sequential, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* ru */ {IDCLS_SPECIFY_C64_MIDI_TYPE_RU, "MIDI interface type (0: Sequential, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* sv */ {IDCLS_SPECIFY_C64_MIDI_TYPE_SV, "Typ av MIDI-gr‰nssnitt (0: sekventiell, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
	/* tr */ {IDCLS_SPECIFY_C64_MIDI_TYPE_TR, "MIDI arabirim tipi (0: Sequential, 1: Passport, 2: DATEL, 3: Namesoft, 4: Maplin)"},
#endif
#endif
	
	/* plus4/digiblaster.c */
	/* en */ {IDCLS_ENABLE_DIGIBLASTER,    N_("Enable the digiblaster add-on")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DIGIBLASTER_DA, "AktivÈr digiblaster-tilf¯jelse"},
	/* de */ {IDCLS_ENABLE_DIGIBLASTER_DE, "Digiblaster add-on aktivieren"},
	/* es */ {IDCLS_ENABLE_DIGIBLASTER_ES, "Permitir complementos digiblaster"},
	/* fr */ {IDCLS_ENABLE_DIGIBLASTER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DIGIBLASTER_HU, "Digiblaster engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_DIGIBLASTER_IT, "Attiva l'estensione digiblaster"},
	/* ko */ {IDCLS_ENABLE_DIGIBLASTER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DIGIBLASTER_NL, "Activeer de digiblaster add-on"},
	/* pl */ {IDCLS_ENABLE_DIGIBLASTER_PL, "W≥±cz dodatek digiblaster"},
	/* ru */ {IDCLS_ENABLE_DIGIBLASTER_RU, "Enable the digiblaster add-on"},
	/* sv */ {IDCLS_ENABLE_DIGIBLASTER_SV, "Aktivera digiblaster-till‰gg"},
	/* tr */ {IDCLS_ENABLE_DIGIBLASTER_TR, "Digiblaster eklentisini aktif et"},
#endif
	
	/* plus4/digiblaster.c */
	/* en */ {IDCLS_DISABLE_DIGIBLASTER,    N_("Disable the digiblaster add-on")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DIGIBLASTER_DA, "DeaktivÈr digiblaster-tilf¯jelse"},
	/* de */ {IDCLS_DISABLE_DIGIBLASTER_DE, "Digiblaster add-on deaktivieren"},
	/* es */ {IDCLS_DISABLE_DIGIBLASTER_ES, "Deshabilitar complementos digiblaster"},
	/* fr */ {IDCLS_DISABLE_DIGIBLASTER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DIGIBLASTER_HU, "Digiblaster tilt·sa"},
	/* it */ {IDCLS_DISABLE_DIGIBLASTER_IT, "Disattiva l'estensione digiblaster"},
	/* ko */ {IDCLS_DISABLE_DIGIBLASTER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DIGIBLASTER_NL, "De digiblaster add-on uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DIGIBLASTER_PL, "Wy≥±cz dodatek digiblaster"},
	/* ru */ {IDCLS_DISABLE_DIGIBLASTER_RU, "Disable the digiblaster add-on"},
	/* sv */ {IDCLS_DISABLE_DIGIBLASTER_SV, "Inaktivera digiblaster-till‰gg"},
	/* tr */ {IDCLS_DISABLE_DIGIBLASTER_TR, "Digiblaster eklentisini pasifle˛tir"},
#endif
	
	/* plus4/plus4speech.c */
	/* en */ {IDCLS_ENABLE_PLUS4SPEECH,    N_("Enable the v364 speech add-on")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_PLUS4SPEECH_DA, "AktivÈr v364 Speech-tilf¯jelse"},
	/* de */ {IDCLS_ENABLE_PLUS4SPEECH_DE, "v364 Spracherweiterung aktivieren"},
	/* es */ {IDCLS_ENABLE_PLUS4SPEECH_ES, "Permitir complementos v364 speech"},
	/* fr */ {IDCLS_ENABLE_PLUS4SPEECH_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_PLUS4SPEECH_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_PLUS4SPEECH_IT, "Attiva l'estensione v364 speech"},
	/* ko */ {IDCLS_ENABLE_PLUS4SPEECH_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_PLUS4SPEECH_NL, "Activeer de v364 spraak add-on"},
	/* pl */ {IDCLS_ENABLE_PLUS4SPEECH_PL, "W≥±cz rozszerzenie mowy v364"},
	/* ru */ {IDCLS_ENABLE_PLUS4SPEECH_RU, "Enable the v364 speech add-on"},
	/* sv */ {IDCLS_ENABLE_PLUS4SPEECH_SV, "Aktivera v364-rˆsttill‰gg"},
	/* tr */ {IDCLS_ENABLE_PLUS4SPEECH_TR, "V364 speech eklentisini aktif et"},
#endif
	
	/* plus4/plus4speech.c */
	/* en */ {IDCLS_DISABLE_PLUS4SPEECH,    N_("Disable the v364 speech add-on")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_PLUS4SPEECH_DA, "DeaktivÈr v364 Speech-tilf¯jelse"},
	/* de */ {IDCLS_DISABLE_PLUS4SPEECH_DE, "v364 Spracherweiterung deaktivieren"},
	/* es */ {IDCLS_DISABLE_PLUS4SPEECH_ES, "Deshabilitar complementos v364 speech"},
	/* fr */ {IDCLS_DISABLE_PLUS4SPEECH_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_PLUS4SPEECH_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_PLUS4SPEECH_IT, "Disattiva l'estensione v364 speech"},
	/* ko */ {IDCLS_DISABLE_PLUS4SPEECH_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_PLUS4SPEECH_NL, "De v364 spraak add-on uitschakelen"},
	/* pl */ {IDCLS_DISABLE_PLUS4SPEECH_PL, "Wy≥±cz rozszerzenie mowy v364"},
	/* ru */ {IDCLS_DISABLE_PLUS4SPEECH_RU, "Disable the v364 speech add-on"},
	/* sv */ {IDCLS_DISABLE_PLUS4SPEECH_SV, "Inaktivera v364-rˆsttill‰gg"},
	/* tr */ {IDCLS_DISABLE_PLUS4SPEECH_TR, "V364 speech eklentisini pasifle˛tir"},
#endif
	
	/* plus4/plus4speech.c */
	/* en */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE,    N_("Attach Speech ROM image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_DA, "Tilslut Speech ROM image"},
	/* de */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_DE, "Spracherweiterung ROM Imagedatei einlegen"},
	/* es */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_ES, "Insertar imagen ROM Speech"},
	/* fr */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_IT, "Seleziona immagine Speech ROM"},
	/* ko */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_NL, "Koppel spraak ROM bestand aan"},
	/* pl */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_PL, "Zamontuj obraz ROM mowy"},
	/* ru */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_RU, "Attach Speech ROM image"},
	/* sv */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_SV, "Anslut rˆst-ROM-avbildning"},
	/* tr */ {IDCLS_ATTACH_SPEECH_ROM_IMAGE_TR, "Speech ROM imaj˝n˝ yerle˛tir"},
#endif
	
	/* plus4/sidcartjoy.c */
	/* en */ {IDCLS_ENABLE_SIDCARTJOY,    N_("Enable SID cartridge joystick")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SIDCARTJOY_DA, "AktivÈr SID-cartridge joystick"},
	/* de */ {IDCLS_ENABLE_SIDCARTJOY_DE, "SIDcart Modul aktivieren"},
	/* es */ {IDCLS_ENABLE_SIDCARTJOY_ES, "Permitir joystic cartucho SID"},
	/* fr */ {IDCLS_ENABLE_SIDCARTJOY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_SIDCARTJOY_HU, "SID cartridge botkorm·ny engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_SIDCARTJOY_IT, "Attiva joystick su cartuccia SID"},
	/* ko */ {IDCLS_ENABLE_SIDCARTJOY_KO, "SID ƒ´∆Æ∏Æ¡ˆ ¡∂¿ÃΩ∫∆Ω ªÁøÎ«œ±‚"},
	/* nl */ {IDCLS_ENABLE_SIDCARTJOY_NL, "Activeer SID cartridge joystick"},
	/* pl */ {IDCLS_ENABLE_SIDCARTJOY_PL, "W≥±cz joystick kartridøa SID"},
	/* ru */ {IDCLS_ENABLE_SIDCARTJOY_RU, "Enable SID cartridge joystick"},
	/* sv */ {IDCLS_ENABLE_SIDCARTJOY_SV, "Aktivera SID-insticksmodul-styrspak"},
	/* tr */ {IDCLS_ENABLE_SIDCARTJOY_TR, "SID kartu˛u joystick'ini aktif et"},
#endif
	
	/* plus4/sidcartjoy.c */
	/* en */ {IDCLS_DISABLE_SIDCARTJOY,    N_("Disable SID cartridge joystick")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SIDCARTJOY_DA, "DeaktivÈr SID-cartridge joystick"},
	/* de */ {IDCLS_DISABLE_SIDCARTJOY_DE, "SIDcart Modul deaktivieren"},
	/* es */ {IDCLS_DISABLE_SIDCARTJOY_ES, "Deshabilitar joystic cartucho SID"},
	/* fr */ {IDCLS_DISABLE_SIDCARTJOY_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_SIDCARTJOY_HU, "SID cartridge botkorm·ny tilt·sa"},
	/* it */ {IDCLS_DISABLE_SIDCARTJOY_IT, "Disattiva joystick su cartuccia SID"},
	/* ko */ {IDCLS_DISABLE_SIDCARTJOY_KO, "SID ƒ´∆Æ∏Æ¡ˆ ¡∂¿ÃΩ∫∆Ω ªÁøÎ«œ¡ˆ æ ±‚"},
	/* nl */ {IDCLS_DISABLE_SIDCARTJOY_NL, "De SID cartridge joystick uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SIDCARTJOY_PL, "Wy≥±cz joystick kartridøa SID"},
	/* ru */ {IDCLS_DISABLE_SIDCARTJOY_RU, "Disable SID cartridge joystick"},
	/* sv */ {IDCLS_DISABLE_SIDCARTJOY_SV, "Inaktivera SID-insticksmodul-styrspak"},
	/* tr */ {IDCLS_DISABLE_SIDCARTJOY_TR, "SID kartu˛u joystick'ini pasifle˛tir"},
#endif
	
	/* c64/cart/sfx_soundexpander.c */
	/* en */ {IDCLS_ENABLE_SFX_SE,    N_("Enable the SFX Sound Expander cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SFX_SE_DA, "AktivÈr SFX sound Expander cartridget"},
	/* de */ {IDCLS_ENABLE_SFX_SE_DE, "SFX Soundexpander Modul aktivieren"},
	/* es */ {IDCLS_ENABLE_SFX_SE_ES, "Permitir cartucho SFX Sound Expander"},
	/* fr */ {IDCLS_ENABLE_SFX_SE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_SFX_SE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_SFX_SE_IT, "Attiva cartuccia SFX Sound Expander"},
	/* ko */ {IDCLS_ENABLE_SFX_SE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_SFX_SE_NL, "Activeer de SFX Sound Expander cartridge"},
	/* pl */ {IDCLS_ENABLE_SFX_SE_PL, "W≥±cz kartridø SFX Sound Expander"},
	/* ru */ {IDCLS_ENABLE_SFX_SE_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_SFX_SE_SV, "Aktivera SFX Sound Expander-insticksmodul"},
	/* tr */ {IDCLS_ENABLE_SFX_SE_TR, "SFX Sound Expander kartu˛unu aktif et"},
#endif
	
	/* c64/cart/sfx_soundexpander.c */
	/* en */ {IDCLS_DISABLE_SFX_SE,    N_("Disable the SFX Sound Expander cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SFX_SE_DA, "DeaktivÈr SFX Sound Expander cartridge"},
	/* de */ {IDCLS_DISABLE_SFX_SE_DE, "SFX Soundexpander Modul deaktivieren"},
	/* es */ {IDCLS_DISABLE_SFX_SE_ES, "Deshabilitar cartucho SFX Sound Expander"},
	/* fr */ {IDCLS_DISABLE_SFX_SE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_SFX_SE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_SFX_SE_IT, "Disattiva cartuccia SFX SFX Sound Expander"},
	/* ko */ {IDCLS_DISABLE_SFX_SE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SFX_SE_NL, "De SFX Sound Expander cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SFX_SE_PL, "Wy≥±cz kartridø SFX Sound Expander"},
	/* ru */ {IDCLS_DISABLE_SFX_SE_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_SFX_SE_SV, "Inaktivera SFX Sound Expander-insticksmodul"},
	/* tr */ {IDCLS_DISABLE_SFX_SE_TR, "SFX Sound Expander kartu˛unu pasifle˛tir"},
#endif
	
	/* c64/cart/sfx_soundexpander.c */
	/* en */ {IDCLS_SET_YM_CHIP_TYPE,    N_("Set YM chip type (3526 / 3812)")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_YM_CHIP_TYPE_DA, "VÊlg YM chiptype"},
	/* de */ {IDCLS_SET_YM_CHIP_TYPE_DE, "YM Chip Typ (3526 / 3812) bestimmen"},
	/* es */ {IDCLS_SET_YM_CHIP_TYPE_ES, "Seleccionar tipo chip YM (3526 / 3812)"},
	/* fr */ {IDCLS_SET_YM_CHIP_TYPE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_YM_CHIP_TYPE_HU, "YM csip tÌpus megad·sa (3526 / 3812)"},
	/* it */ {IDCLS_SET_YM_CHIP_TYPE_IT, "Imposta tipo chip YM (3526 / 3812)"},
	/* ko */ {IDCLS_SET_YM_CHIP_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_YM_CHIP_TYPE_NL, "Kies de YM chip soort (3526 / 3812)"},
	/* pl */ {IDCLS_SET_YM_CHIP_TYPE_PL, "Okre∂l typ uk≥adu YM (3526 / 3812)"},
	/* ru */ {IDCLS_SET_YM_CHIP_TYPE_RU, "Set YM chip type (3526 / 3812)"},
	/* sv */ {IDCLS_SET_YM_CHIP_TYPE_SV, "V‰lj YM-kretstyp (3526 / 3812)"},
	/* tr */ {IDCLS_SET_YM_CHIP_TYPE_TR, "YM Áip tipini ayarla (3526 / 3812)"},
#endif
	
	/* c64/cart/sfx_soundsampler.c */
	/* en */ {IDCLS_ENABLE_SFX_SS,    N_("Enable the SFX Sound Sampler cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_SFX_SS_DA, "AktivÈr SFX Sound Sampler cartridge"},
	/* de */ {IDCLS_ENABLE_SFX_SS_DE, "SFX Sound Sampler Modul aktivieren"},
	/* es */ {IDCLS_ENABLE_SFX_SS_ES, "Permitir cartucho SFX Sound Sampler"},
	/* fr */ {IDCLS_ENABLE_SFX_SS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_SFX_SS_HU, "SFX Sound Sampler engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_SFX_SS_IT, "Attiva cartuccia SFX Sound Sampler"},
	/* ko */ {IDCLS_ENABLE_SFX_SS_KO, "SFX Sound Sampler ƒ´∆Æ∏Æ¡ˆ ∏¶ ¿€µøΩ√≈≤¥Ÿ"},
	/* nl */ {IDCLS_ENABLE_SFX_SS_NL, "Activeer de SFX Sound Sampler cartridge"},
	/* pl */ {IDCLS_ENABLE_SFX_SS_PL, "W≥±cz kartridø SFX Sound Sampler"},
	/* ru */ {IDCLS_ENABLE_SFX_SS_RU, "Enable the SFX Sound Sampler cartridge"},
	/* sv */ {IDCLS_ENABLE_SFX_SS_SV, "Aktivera SFX Sound Sampler-insticksmodul"},
	/* tr */ {IDCLS_ENABLE_SFX_SS_TR, "SFX Sound Sampler kartu˛unu aktif et"},
#endif
	
	/* c64/cart/sfx_soundsampler.c */
	/* en */ {IDCLS_DISABLE_SFX_SS,    N_("Disable the SFX Sound Sampler cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_SFX_SS_DA, "DeaktivÈr SFX Sound Sampler cartridge"},
	/* de */ {IDCLS_DISABLE_SFX_SS_DE, "SFX Sound Sampler Modul  deaktivieren"},
	/* es */ {IDCLS_DISABLE_SFX_SS_ES, "Deshabilitar cartucho SFX Sound Sampler"},
	/* fr */ {IDCLS_DISABLE_SFX_SS_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_SFX_SS_HU, "SFX Sound Sampler tilt·sa"},
	/* it */ {IDCLS_DISABLE_SFX_SS_IT, "Disattiva cartuccia SFX Sound Sampler"},
	/* ko */ {IDCLS_DISABLE_SFX_SS_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_SFX_SS_NL, "De SFX Sound Sampler cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_SFX_SS_PL, "Wy≥±cz kartridø SFX Sound Sampler"},
	/* ru */ {IDCLS_DISABLE_SFX_SS_RU, "Disable the SFX Sound Sampler cartridge"},
	/* sv */ {IDCLS_DISABLE_SFX_SS_SV, "Inaktivera SFX Sound Sampler-insticksmodul"},
	/* tr */ {IDCLS_DISABLE_SFX_SS_TR, "SFX Sound Sampler kartu˛unu pasifle˛tir"},
#endif
	
	/* lightpen.c */
	/* en */ {IDCLS_ENABLE_LIGHTPEN_EMULATION,    N_("Enable lightpen emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_DA, "AktivÈr lyspen-emulering"},
	/* de */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_DE, "Lichtgriffel Emulation aktivieren"},
	/* es */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_ES, "Permitir emulaciÛn l·piz Ûptico"},
	/* fr */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_HU, "FÈnyceruza emul·ciÛ engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_IT, "Attiva emulazione della penna ottica"},
	/* ko */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_KO, "∂Û¿Ã∆Æ∆Ê ø°π∞∑πæÓ≈Õ ªÁøÎ∞°¥…ƒ… «œ±‚"},
	/* nl */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_NL, "Activeer de lichtpen emulatie"},
	/* pl */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_PL, "W≥±cz emulacjÍ piÛra ∂wietlnego"},
	/* ru */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_RU, "Enable lightpen emulation"},
	/* sv */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_SV, "Aktivera emulering av ljuspenna"},
	/* tr */ {IDCLS_ENABLE_LIGHTPEN_EMULATION_TR, "I˛˝kl˝ Kalem em¸lasyonunu aktif et"},
#endif
	
	/* lightpen.c */
	/* en */ {IDCLS_DISABLE_LIGHTPEN_EMULATION,    N_("Disable lightpen emulation")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_DA, "DeaktivÈr lyspen-emulering"},
	/* de */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_DE, "Lichtgriffel Emulation deaktivieren"},
	/* es */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_ES, "Deshabilitar emulaciÛn l·piz Ûptico"},
	/* fr */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_HU, "FÈnyceruza emul·ciÛ tilt·sa"},
	/* it */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_IT, "Disattiva emulazione della penna ottica"},
	/* ko */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_NL, "De lichtpen emulatie uitschakelen"},
	/* pl */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_PL, "Wy≥±cz emulacjÍ piÛra ∂wietlnego"},
	/* ru */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_RU, "Disable lightpen emulation"},
	/* sv */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_SV, "Inaktivera emulering ljuspenna"},
	/* tr */ {IDCLS_DISABLE_LIGHTPEN_EMULATION_TR, "I˛˝kl˝ Kalem em¸lasyonunu pasifle˛tir"},
#endif
	
	/* lightpen.c */
	/* en */ {IDCLS_SET_LIGHTPEN_TYPE,    N_("Set lightpen type")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_SET_LIGHTPEN_TYPE_DA, "Angiv lyspen-type"},
	/* de */ {IDCLS_SET_LIGHTPEN_TYPE_DE, "Lichtgriffel Type bestimmen"},
	/* es */ {IDCLS_SET_LIGHTPEN_TYPE_ES, "Seleccionar tipo l·piz Ûptico"},
	/* fr */ {IDCLS_SET_LIGHTPEN_TYPE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_SET_LIGHTPEN_TYPE_HU, "FÈnyceruza tÌpus·nak megad·sa"},
	/* it */ {IDCLS_SET_LIGHTPEN_TYPE_IT, "Imposta tipo penna ottica"},
	/* ko */ {IDCLS_SET_LIGHTPEN_TYPE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_SET_LIGHTPEN_TYPE_NL, "Geef de lichtpen soort op"},
	/* pl */ {IDCLS_SET_LIGHTPEN_TYPE_PL, "Okre∂l typ piÛra ∂wietlnego"},
	/* ru */ {IDCLS_SET_LIGHTPEN_TYPE_RU, "Set lightpen type"},
	/* sv */ {IDCLS_SET_LIGHTPEN_TYPE_SV, "V‰lj typ av ljuspenna"},
	/* tr */ {IDCLS_SET_LIGHTPEN_TYPE_TR, "I˛˝kl˝ Kalem tipini ayarla"},
#endif
	
	/* c64/cart/easyflash.c */
	/* en */ {IDCLS_ENABLE_EASYFLASH_JUMPER,    N_("Enable EasyFlash jumper")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_EASYFLASH_JUMPER_DA, "AktivÈr EasyFlash-jumper"},
	/* de */ {IDCLS_ENABLE_EASYFLASH_JUMPER_DE, "EasyFlash Jumper aktivieren"},
	/* es */ {IDCLS_ENABLE_EASYFLASH_JUMPER_ES, "Permitir puente EasyFlash"},
	/* fr */ {IDCLS_ENABLE_EASYFLASH_JUMPER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_EASYFLASH_JUMPER_HU, "EasyFlash Jumper engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_EASYFLASH_JUMPER_IT, "Attiva ponticello EasyFlash"},
	/* ko */ {IDCLS_ENABLE_EASYFLASH_JUMPER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_EASYFLASH_JUMPER_NL, "Activeer de EasyFlash jumper"},
	/* pl */ {IDCLS_ENABLE_EASYFLASH_JUMPER_PL, "W≥±cz prze≥±cznik EasyFlash"},
	/* ru */ {IDCLS_ENABLE_EASYFLASH_JUMPER_RU, "Enable EasyFlash jumper"},
	/* sv */ {IDCLS_ENABLE_EASYFLASH_JUMPER_SV, "Aktivera EasyFlash-bygel"},
	/* tr */ {IDCLS_ENABLE_EASYFLASH_JUMPER_TR, "EasyFlash jumper'˝ aktif et"},
#endif
	
	/* c64/cart/easyflash.c */
	/* en */ {IDCLS_DISABLE_EASYFLASH_JUMPER,    N_("Disable EasyFlash jumper")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_EASYFLASH_JUMPER_DA, "DeaktivÈr EasyFlash-jumper"},
	/* de */ {IDCLS_DISABLE_EASYFLASH_JUMPER_DE, "EasyFlash Jumer deaktivieren"},
	/* es */ {IDCLS_DISABLE_EASYFLASH_JUMPER_ES, "Deshabilitar puente EasyFlash"},
	/* fr */ {IDCLS_DISABLE_EASYFLASH_JUMPER_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_EASYFLASH_JUMPER_HU, "EasyFlash Jumper tilt·sa"},
	/* it */ {IDCLS_DISABLE_EASYFLASH_JUMPER_IT, "Disattiva ponticello EasyFlash"},
	/* ko */ {IDCLS_DISABLE_EASYFLASH_JUMPER_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_EASYFLASH_JUMPER_NL, "De EasyFlash jumper uitschakelen"},
	/* pl */ {IDCLS_DISABLE_EASYFLASH_JUMPER_PL, "Wy≥±cz prze≥±cznik EasyFlash"},
	/* ru */ {IDCLS_DISABLE_EASYFLASH_JUMPER_RU, "Disable EasyFlash jumper"},
	/* sv */ {IDCLS_DISABLE_EASYFLASH_JUMPER_SV, "Inaktivera EasyFlash-bygel"},
	/* tr */ {IDCLS_DISABLE_EASYFLASH_JUMPER_TR, "EasyFlash jumper'˝ pasifle˛tir"},
#endif
	
	/* c64/cart/easyflash.c */
	/* en */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING,    N_("Enable writing to EasyFlash .crt image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_DA, "Tillad skrivning til EasyFlash CRT-image"},
	/* de */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_DE, "Schreibzugriff auf EasyFlash CRT Image erlauben"},
	/* es */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_ES, "Permitir grabar imagen .crt EasyFlash"},
	/* fr */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_HU, "EasyFlash .crt kÈpm·sba Ìr·s engedÈlyezÈse"},
	/* it */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_IT, "Attiva scrittura sull'immagine .crt EasyFlash"},
	/* ko */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_NL, "Activeer schrijven naar het EasyFlash .crt bestand"},
	/* pl */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_PL, "W≥±cz zapis do obrazu .crt EasyFlash"},
	/* ru */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_RU, "Enable writing to EasyFlash .crt image"},
	/* sv */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_SV, "Aktivera skrivning till EasyFlash-.crt-avbildning."},
	/* tr */ {IDCLS_ENABLE_EASYFLASH_CRT_WRITING_TR, "EasyFlash .crt imaj˝na yazmay˝ aktif et"},
#endif
	
	/* c64/cart/easyflash.c */
	/* en */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING,    N_("Disable writing to EasyFlash .crt image")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_DA, "Forbyd skrivning til EasyFlash CRT-image"},
	/* de */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_DE, "Schreibzugriff auf EasyFlash ROM Image verhindern"},
	/* es */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_ES, "Deshabilitar grabar imagen .crt EasyFlash"},
	/* fr */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_HU, "EasyFlash .crt kÈpm·sba Ìr·s tilt·sa"},
	/* it */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_IT, "Disattiva scrittura sull'immagine .crt EasyFlash"},
	/* ko */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_NL, "Schrijven naar het EasyFlash .crt bestand uitschakelen"},
	/* pl */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_PL, "Wy≥±cz zapis do obrazu .crt EasyFlash"},
	/* ru */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_RU, "Disable writing to EasyFlash .crt image"},
	/* sv */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_SV, "Inaktivera skrivning till EasyFlash-.crt-avbildning."},
	/* tr */ {IDCLS_DISABLE_EASYFLASH_CRT_WRITING_TR, "EasyFlash .crt imaj˝na yazmay˝ pasifle˛tir"},
#endif
	
	/* c64/cart/digimax.c */
	/* en */ {IDCLS_ENABLE_DIGIMAX,    N_("Enable the DigiMAX cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DIGIMAX_DA, "AktivÈr DigiMAX cartridge"},
	/* de */ {IDCLS_ENABLE_DIGIMAX_DE, "DigiMAX Cartridge aktivieren"},
	/* es */ {IDCLS_ENABLE_DIGIMAX_ES, "Permitir cartucho DigMAX"},
	/* fr */ {IDCLS_ENABLE_DIGIMAX_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DIGIMAX_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_DIGIMAX_IT, "Attiva la cartuccia DigiMAX"},
	/* ko */ {IDCLS_ENABLE_DIGIMAX_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DIGIMAX_NL, "Activeer de DigiMAX cartridge"},
	/* pl */ {IDCLS_ENABLE_DIGIMAX_PL, "W≥±cz kartridø DigiMAX"},
	/* ru */ {IDCLS_ENABLE_DIGIMAX_RU, "Enable the DigiMAX cartridge"},
	/* sv */ {IDCLS_ENABLE_DIGIMAX_SV, "Aktivera DigiMAX-insticksmodul"},
	/* tr */ {IDCLS_ENABLE_DIGIMAX_TR, "DigiMAX kartu˛unu aktif et"},
#endif
	
	/* c64/cart/digimax.c */
	/* en */ {IDCLS_DISABLE_DIGIMAX,    N_("Disable the DigiMAX cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DIGIMAX_DA, "DeaktivÈr DigiMAX cartridge"},
	/* de */ {IDCLS_DISABLE_DIGIMAX_DE, "DigiMAX Cartridge deaktivieren"},
	/* es */ {IDCLS_DISABLE_DIGIMAX_ES, "Deshabilitar cartucho DigMAX"},
	/* fr */ {IDCLS_DISABLE_DIGIMAX_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DIGIMAX_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_DIGIMAX_IT, "Disattiva la cartuccia DigiMAX"},
	/* ko */ {IDCLS_DISABLE_DIGIMAX_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DIGIMAX_NL, "De DigiMAX cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DIGIMAX_PL, "Wy≥±cz kartridø DigiMAX"},
	/* ru */ {IDCLS_DISABLE_DIGIMAX_RU, "Disable the DigiMAX cartridge"},
	/* sv */ {IDCLS_DISABLE_DIGIMAX_SV, "Inaktivera DigiMAX-insticksmodul"},
	/* tr */ {IDCLS_DISABLE_DIGIMAX_TR, "DigiMAX kartu˛unu pasifle˛tir"},
#endif
	
	/* c64/cart/digimax.c */
	/* en */ {IDCLS_DIGIMAX_BASE,    N_("Base address of the DigiMAX cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DIGIMAX_BASE_DA, "Baseadresse for DigiMAX cartridge"},
	/* de */ {IDCLS_DIGIMAX_BASE_DE, "Basis Adresse f¸r DigiMAX Erweiterung"},
	/* es */ {IDCLS_DIGIMAX_BASE_ES, "DirecciÛn base para cartucho DigMAX"},
	/* fr */ {IDCLS_DIGIMAX_BASE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DIGIMAX_BASE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DIGIMAX_BASE_IT, "Indirizzo base della cartuccia DigiMAX"},
	/* ko */ {IDCLS_DIGIMAX_BASE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DIGIMAX_BASE_NL, "Basisadres van de DigiMAX cartridge"},
	/* pl */ {IDCLS_DIGIMAX_BASE_PL, "Adres bazowy kartridøa DigiMAX"},
	/* ru */ {IDCLS_DIGIMAX_BASE_RU, "Base address of the DigiMAX cartridge"},
	/* sv */ {IDCLS_DIGIMAX_BASE_SV, "Basadress fˆr DigiMAC-insticksmodulen"},
	/* tr */ {IDCLS_DIGIMAX_BASE_TR, "DigiMAX kartu˛unun taban adresi"},
#endif
	
	/* c64/cart/ds12c887rtc.c */
	/* en */ {IDCLS_ENABLE_DS12C887RTC,    N_("Enable the DS12C887 RTC cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_ENABLE_DS12C887RTC_DA, "AktivÈr DS12C887 RTC-cartridge"},
	/* de */ {IDCLS_ENABLE_DS12C887RTC_DE, "DS12C887 RTC Modul aktivieren"},
	/* es */ {IDCLS_ENABLE_DS12C887RTC_ES, "Permitir cartucho DS12C887 RTC"},
	/* fr */ {IDCLS_ENABLE_DS12C887RTC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_ENABLE_DS12C887RTC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_ENABLE_DS12C887RTC_IT, "Attiva la cartuccia DS12C887 RTC"},
	/* ko */ {IDCLS_ENABLE_DS12C887RTC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_ENABLE_DS12C887RTC_NL, "Activeer de DS12C887 RTC cartridge"},
	/* pl */ {IDCLS_ENABLE_DS12C887RTC_PL, "W≥±cz kartridø DS12C887 RTC"},
	/* ru */ {IDCLS_ENABLE_DS12C887RTC_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_ENABLE_DS12C887RTC_SV, "Aktivera DS12C887 RTC-insticksmodul"},
	/* tr */ {IDCLS_ENABLE_DS12C887RTC_TR, "DS12C887 RTC kartu˛unu aktif et"},
#endif
	
	/* c64/cart/ds12c887rtc.c */
	/* en */ {IDCLS_DISABLE_DS12C887RTC,    N_("Disable the DS12C887 RTC cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DISABLE_DS12C887RTC_DA, "DeaktivÈr DS12C887 RTC-cartridge"},
	/* de */ {IDCLS_DISABLE_DS12C887RTC_DE, "DS12C887 RTC Modul deaktivieren"},
	/* es */ {IDCLS_DISABLE_DS12C887RTC_ES, "Deshabilitar cartucho DS12C887 RTC"},
	/* fr */ {IDCLS_DISABLE_DS12C887RTC_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DISABLE_DS12C887RTC_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DISABLE_DS12C887RTC_IT, "Disattiva la cartuccia DS12C887 RTC"},
	/* ko */ {IDCLS_DISABLE_DS12C887RTC_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DISABLE_DS12C887RTC_NL, "De DS12C887 RTC cartridge uitschakelen"},
	/* pl */ {IDCLS_DISABLE_DS12C887RTC_PL, "Wy≥±cz kartridø DS12C887 RTC"},
	/* ru */ {IDCLS_DISABLE_DS12C887RTC_RU, ""},  /* fuzzy */
	/* sv */ {IDCLS_DISABLE_DS12C887RTC_SV, "Inaktivera DS12C887 RTC-insticksmodul"},
	/* tr */ {IDCLS_DISABLE_DS12C887RTC_TR, "DS12C887 RTC kartu˛unu pasifle˛tir"},
#endif
	
	/* c64/cart/ds12c887rtc.c */
	/* en */ {IDCLS_DS12C887RTC_BASE,    N_("Base address of the DS12C887 RTC cartridge")},
#ifdef HAS_TRANSLATION
	/* da */ {IDCLS_DS12C887RTC_BASE_DA, "Baseadresse for DS12C887 RTC-cartridge"},
	/* de */ {IDCLS_DS12C887RTC_BASE_DE, "Basis Adresse f¸r DS12C887 RTC Modul"},
	/* es */ {IDCLS_DS12C887RTC_BASE_ES, "DirecciÛn base para cartucho DS12C887 RTC"},
	/* fr */ {IDCLS_DS12C887RTC_BASE_FR, ""},  /* fuzzy */
	/* hu */ {IDCLS_DS12C887RTC_BASE_HU, ""},  /* fuzzy */
	/* it */ {IDCLS_DS12C887RTC_BASE_IT, "Indirizzo base della cartuccia DS12C887 RTC"},
	/* ko */ {IDCLS_DS12C887RTC_BASE_KO, ""},  /* fuzzy */
	/* nl */ {IDCLS_DS12C887RTC_BASE_NL, "Basisadres van de DS12C887 RTC cartridge"},
	/* pl */ {IDCLS_DS12C887RTC_BASE_PL, "Adres bazowy kartridøa DS12C887 RTC"},
	/* ru */ {IDCLS_DS12C887RTC_BASE_RU, "Base address of the DS12C887 RTC cartridge"},
	/* sv */ {IDCLS_DS12C887RTC_BASE_SV, "Basadress fˆr DS12C887 RTC-insticksmodulen"},
	/* tr */ {IDCLS_DS12C887RTC_BASE_TR, "DS12C887 RTC kartu˛unun taban adresi"},
#endif
	
};


//////

/* --------------------------------------------------------------------- */

static char *get_string_by_id(int id)
{
  unsigned int k;

  for (k = 0; k < countof(string_table); k++)
  {
    if (string_table[k].resource_id==id)
      return string_table[k].text;
  }
  return NULL;
}

static char *sid_return = NULL;

/* special case translation, this command-line option normally
   produces alot of lines (which only differ slightly) for the
   translators to translate, this function builds up the total
   command-line option from smaller translation pieces.
 */
static char *translate_and_build_sid_cmdline_option(int en_resource)
{
    char *old, *new;

    /* check if sid_return is already built */
    if (sid_return != NULL) {
        lib_free(sid_return);
    }

    /* start building up the command-line */
    old = lib_stralloc("Specify SID engine and model (");

    /* add fast sid options */
    new = util_concat(old, translate_text(IDCLS_FASTSID_ENGINE_MODEL), NULL);
    lib_free(old);
    old = new;


#ifdef HAVE_RESID
    /* add resid options if available */
    if (en_resource != IDCLS_SPECIFY_SIDCART_ENGINE_MODEL) {
        new = util_concat(old, ", ", translate_text(IDCLS_RESID_ENGINE_MODEL), NULL);
        lib_free(old);
        old = new;
    }

    /* add residdtv options if available */
    if (en_resource == IDCLS_SPECIFY_SIDDTV_ENGINE_MODEL) {
        new = util_concat(old, ", ", translate_text(IDCLS_RESIDDTV_ENGINE_MODEL), NULL);
        lib_free(old);
        old = new;
    }
#endif

#ifdef HAVE_CATWEASELMKIII
    /* add catweasel options if available */
    new = util_concat(old, ", ", translate_text(IDCLS_CATWEASELMKIII_ENGINE_MODEL), NULL);
    lib_free(old);
    old = new;
#endif

#ifdef HAVE_HARDSID
    /* add hardsid options if available */
    new = util_concat(old, ", ", translate_text(IDCLS_HARDSID_ENGINE_MODEL), NULL);
    lib_free(old);
    old = new;
#endif

#ifdef HAVE_PARSID
    /* add parsid options if available */
    new = util_concat(old, ", ", translate_text(IDCLS_PARSID_ENGINE_MODEL), NULL);
    lib_free(old);
    old = new;
#endif

#ifdef HAVE_RESID_FP
    /* add resid-fp options if available */
    if (en_resource != IDCLS_SPECIFY_SIDCART_ENGINE_MODEL) {
        new = util_concat(old, ", ", translate_text(IDCLS_RESIDFP_ENGINE_MODEL), NULL);
        lib_free(old);
        old = new;
    }
#endif

    /* add ending bracket */
    new = util_concat(old, ")", NULL);
    lib_free(old);

    sid_return = new;

    return sid_return;
}

#ifdef HAS_TRANSLATION
#include "translate_table.h"

static char *text_table[countof(translate_text_table)][countof(language_table)];

static void translate_text_init(void)
{
  unsigned int i,j;
  char *temp;

  for (i = 0; i < countof(language_table); i++)
  {
    for (j = 0; j < countof(translate_text_table); j++)
    {
      if (translate_text_table[j][i]==0)
        text_table[j][i]=NULL;
      else
      {
        temp=get_string_by_id(translate_text_table[j][i]);
        text_table[j][i]=intl_convert_cp(temp, language_cp_table[i]);
      }
    }
  }
}

char translate_id_error_text[30];

char *translate_text(int en_resource)
{
  unsigned int i;
  char *retval = NULL;

  if (en_resource == IDCLS_UNUSED)
      return NULL;

  if (en_resource == 0)
  {
    log_error(LOG_DEFAULT, "TRANSLATE ERROR: ID 0 was requested.");
    return "ID 0 translate error";
  }

  /* handle sid cmdline special case translations */
  if (en_resource == IDCLS_SPECIFY_SIDCART_ENGINE_MODEL ||
      en_resource == IDCLS_SPECIFY_SID_ENGINE_MODEL ||
      en_resource == IDCLS_SPECIFY_SIDDTV_ENGINE_MODEL) {
      return translate_and_build_sid_cmdline_option(en_resource);
  }

  if (en_resource < 0x10000)
  {
    retval = intl_translate_text(en_resource);
  }
  else
  {
    for (i = 0; i < countof(translate_text_table); i++)
    {
      if (translate_text_table[i][0] == en_resource)
      {
        if (translate_text_table[i][current_language_index]!=0 &&
            text_table[i][current_language_index]!=NULL &&
            strlen(text_table[i][current_language_index])!=0)
          retval = text_table[i][current_language_index];
        else
          retval = text_table[i][0];
      }
    }
  }

  if (retval == NULL)
  {
    log_error(LOG_DEFAULT, "TRANSLATE ERROR: ID %d was requested, and would be returning NULL.",en_resource);
    sprintf(translate_id_error_text,"ID %d translate error",en_resource);
    retval = translate_id_error_text;
  }

  return retval;
}

int translate_res(int en_resource)
{
  return intl_translate_res(en_resource);
}

/* --------------------------------------------------------------------- */

static int set_current_language(const char *lang, void *param)
{
    unsigned int i;

    util_string_set(&current_language, "en");
    current_language_index = 0;

    if (strlen(lang) != 2)
        return 0;

    for (i = 0; i < countof(language_table); i++) {
        if (!strcasecmp(lang,language_table[i])) {
            current_language_index=i;
            util_string_set(&current_language, language_table[i]);
            intl_update_ui();
            return 0;
        }
    }

    return 0;
}

static const resource_string_t resources_string[] = {
    { "Language", "en", RES_EVENT_NO, NULL,
      &current_language, set_current_language, NULL },
    { NULL }
};

int translate_resources_init(void)
{
  intl_init();
  translate_text_init();

  return resources_register_string(resources_string);
}

void translate_resources_shutdown(void)
{
  unsigned int i,j;

  for (i = 0; i < countof(language_table); i++)
  {
    for (j = 0; j < countof(translate_text_table); j++)
    {
      lib_free(text_table[j][i]);
    }
  }
  intl_shutdown();
  lib_free(current_language);

  /* check if sid_return is already built */
  if (sid_return != NULL) {
      lib_free(sid_return);
  }
}

static const cmdline_option_t cmdline_options[] =
{
    { "-lang", SET_RESOURCE, 1,
      NULL, NULL, "Language", NULL,
      USE_PARAM_ID, USE_DESCRIPTION_ID,
      IDCLS_P_ISO_LANGUAGE_CODE, IDCLS_SPECIFY_ISO_LANG_CODE,
      NULL, NULL },
    { NULL }
};

int translate_cmdline_options_init(void)
{
    return cmdline_register_options(cmdline_options);
}

void translate_arch_language_init(void)
{
  char *lang;

  lang=intl_arch_language_init();
  set_current_language(lang, "");
}
#else

char *translate_text(int en_resource)
{
  if (en_resource == IDCLS_UNUSED)
      return NULL;

  if (en_resource == 0)
  {
    log_error(LOG_DEFAULT, "TRANSLATE ERROR: ID 0 was requested.");
    return "ID 0 translate error";
  }

  /* handle sid cmdline special case translations */
  if (en_resource == IDCLS_SPECIFY_SIDCART_ENGINE_MODEL ||
      en_resource == IDCLS_SPECIFY_SID_ENGINE_MODEL ||
      en_resource == IDCLS_SPECIFY_SIDDTV_ENGINE_MODEL) {
      return translate_and_build_sid_cmdline_option(en_resource);
  }

  return _(get_string_by_id(en_resource));
}
#endif
