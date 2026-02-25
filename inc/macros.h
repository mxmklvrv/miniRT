#ifndef MACROS_H
# define MACROS_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define FAILURE -1
# define SUCCESS 0
# define WIDTH 1920
# define HEIGHT 1080

# define ERR_MSG "Error"
# define ERR_AC "Usage: ./miniRT file.rt"
# define ERR_EXT "Wrong file extension, should be file.rt"
# define ERR_ALLOC "Memory allocation failed"

# define ESCAPE 0xFF1B
# define ON_DESTROY 17

# define EPSILON 0.001

#define MOVE_SPEED 0.5f
#define ROTATE_SPEED 0.1f
#define RESIZE_SPEED 0.2f

#define KEY_W 119       // forward
#define KEY_A 97        // left
#define KEY_S 115       // back
#define KEY_D 100       // right
#define KEY_Q 113       // up
#define KEY_E 101       // down
#define KEY_C 99        // cam
#define KEY_TAB 65289   // switch obj
#define KEY_LEFT 65361  // rotate left
#define KEY_RIGHT 65363 // rotate right
#define KEY_UP 65362    // rotate up
#define KEY_DOWN 65364  // rotate down
#define KEY_PLUS 61     // resize up
#define KEY_MINUS 45    // resize down
#define KEY_ESC 65307   // esc
#define KEY_H 104       // height up
#define KEY_J 106       // height down

// to pass as value pressed or no
#define KEY_ON 1
#define KEY_OFF 0

#endif
