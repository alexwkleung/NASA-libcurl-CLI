# NASA-libcurl-CLI

![example](/img/example.png)
![example2](/img/example2.png)

A CLI program that fetches [NASA API's](https://api.nasa.gov/) and outputs them in prettified JSON format.

Written in C++ using the [libcurl API](https://curl.se/libcurl/) and [nlohmann json parser](https://github.com/nlohmann/json). My library [TermStylist](https://github.com/alexwkleung/TermStylist) was also used for terminal colours.

**References:**

1. https://curl.se/libcurl/c/getinmemory.html

2. https://curl.se/libcurl/c/simple.html

3. https://json.nlohmann.me/api/basic_json/parse/

4. https://json.nlohmann.me/api/basic_json/dump/

# Installation 

Clone the repository.

```bash
git clone <SSH/HTTPS URL>
```

Change directory.

```bash
cd NASA-libcurl-CLI
```

Install cURL.

```bash
# homebrew
brew install curl

# apt
sudo apt install curl

# you will probably need to add cURL to your path to override system cURL. 
# this should be specified by your package manager after installation.
```

Change `CPPFLAGS` value to your cURL include directory if necessary.

```bash 
# check library include directory

curl-config --cflags
```

```make
# makefile 

CPPFLAGS = -std=c++17 -Wall -Wextra -g <include directory>
```

Change `LDFLAGS` value to your cURL lib directory if necessary.

```bash
# check library link directory

curl-config --libs
```

```make
# makefile 

LDFLAGS = <library directory from curl-config --libs>
```

Create a text file to hold NASA API key. Get your key [here](https://api.nasa.gov/).

```bash
# this directory (src/key.txt) is gitignored
touch src/key.txt
```

Add key to text file.

```txt
<your NASA API key>
```

Build program.

```bash
make build
```

Run command line argument. 

```bash
./src/a.o --<command line arg>
```

# Options

**Command line arguments:**

`--apod` will call the function to fetch the Astronomy Picture of the day (APOD) API.

`--neo-feed` will call the function to fetch the Asteroids - NeoW Feed (Neo Feed) API.

`donki-sep` will call the function to fetch the DONKI Solar Energetic Particle (SEP) API.

`--insight` will call the function to fetch the InSight: Mars Weather Service API.

`--options` will call the function to take you to the options menu (selection prompt).

**Options menu (selection prompt):**

Typing `apod` will call the function to fetch the Astronomy Picture of the day (APOD) API.

Typing `neo-feed` will call the function to fetch the Asteroids - NeoW Feed (Neo Feed) API.

Typing `donki-sep` will call the function to fetch the DONKI Solar Energetic Particle (SEP) API.

Typing `insight` will call the function to fetch the InSight: Mars Weather Service API.

When you enter an option from either the menu or command line arguments, you might be asked to enter required fields to specify the API query before it fetches the JSON data string so that nlohmann json can parse it. For the ones that don't, it will go straight to fetching the JSON data string.

Here are the steps that will be executed in order: 

1) Choose an option (apod, neo-feed, donki-sep, insight, etc).

2) Enter the required fields to specifiy the API query if applicable.

3) The JSON data string will be fetched by libcurl, then nlohmann json will parse that string and prettify the formatting for viewing pleasure. 

4) The output of the prettified JSON will be present in the `json-out` directory, with file containing the naming scheme of `<api name>.json`. The prettified JSON is also outputted to the terminal.

# Issues

DONKI Solar Engergetic Particle (SEP) API may have problems fetching data.
