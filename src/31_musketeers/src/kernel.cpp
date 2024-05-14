extern "C"{
    #include "libc/stdint.h"
    #include "libc/stddef.h"
    #include "libc/stdbool.h"
    #include "libc/limits.h"
    #include "libc/system.h"
    #include "common.h"
    #include "descriptor_tables.h"
    #include "input.h"
    #include "monitor.h"
    #include "isr.h"
    #include <kernel/memory.h>
    #include <kernel/pit.h>
    #include "songstuff/song.h"
}


// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}


extern "C" int kernel_main(void);
int kernel_main(){

    // Allocate some memory using the kernel memory manager
		// THIS IS PART OF THE ASSIGNMENT
    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();
    int counter = 0;



// How to play music
Song* songs[] = {
	new Song({music_1, sizeof(music_1) / sizeof(Note)}),
    new Song({starwars_theme, sizeof(starwars_theme)  / sizeof(Note)}),
    new Song({battlefield_1942_theme, sizeof(battlefield_1942_theme)  / sizeof(Note)})
};
uint32_t n_songs = sizeof(songs) / sizeof(Song*);

SongPlayer* player = create_song_player();


while(true){
  for(uint32_t i =0; i < n_songs; i++){
      printf("Playing Song...\n");
      player->play_song(songs[i]);
      printf("Finished playing the song.\n");
  }

    printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
    sleep_busy(10000);
    printf("[%d]: Slept using busy-waiting.\n", counter++);

    printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
    sleep_interrupt(10000);
    printf("[%d]: Slept using interrupts.\n", counter++);
  }

}