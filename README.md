## SharkSH

![Screenshot from 2019-05-29 07-52-08](https://user-images.githubusercontent.com/44285344/58533473-eec82280-81e8-11e9-9074-96af1fe0d9b1.png)

All features:  

- Variables:  
    - Local: set, unset, $?, $$, $PATH, .....   
    - Environment: setenv, unsetenv, env  
- errors and return value  
- redirections ('<', '>', '<<', '>>')  
- pipes ('|')  
- separators (';', '&&', '||')  
- inhibitors ('\')  
- globbings ('*', '?', '[', ']')  
- quotes ('' "")  
- parentheses ('(' and ')')  
- history ('!')  
- alias (alias, unalias)  
- Line edition:  
    - Shortcuts:  
      - Arrow Left, Right: Move left / right  
      - Arrow Up, Down: History Up / Down  
      - CTRL+F: move right  
      - CTRL+K: cut line after cursor  
      - CTRL+W: cut line before cursor  
      - CTRL+T: transpose character  
      - CTRL+A: move cursor to the beginning of the line  
      - CTRL+E: move cursor to the end of the line  
      - CTRL+J: new line  
      - CTRL+U: clear line  
      - CTRL+C: exit  
      - CTRL+L: clear screen  
      - CTRL+V: paste  
      - Tab: autocompletion  

Basic builtins:   
- cd, echo, exit, sharksh, alias, unalias, which/where, repeat, history.  
- set, unset, setenv, unsetenv, printenv, env  

## Getting started  

1) Download this repository.  
2) ```make re```    
3) ```./sharksh```  

## Author  

* **Théo CERUTTI** - [Github](https://github.com/theocerutti)
* **Antoine MAILLARD** - [Github](https://github.com/AntoineMaillard06)
* **Shiranuit** [Github](https://github.com/Shiranuit/)
* **Mathilde COUSTON** - [Github](https://github.com/MathildeCouston)
* **Cyril BEGARD** [Github](https://github.com/cyrilbegard/)

## Tests

Pour faire un shell il nous faut énormement de tests, du coup on a crée un système de tests, +300 tests.

![ezgif com-video-to-gif](https://user-images.githubusercontent.com/44285344/58534049-78c4bb00-81ea-11e9-9677-1018d904225a.gif)

## View

Autocompletion:

![Screenshot from 2019-05-29 07-52-18](https://user-images.githubusercontent.com/44285344/58533471-ee2f8c00-81e8-11e9-8910-66b0629b2819.png)
