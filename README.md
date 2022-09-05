# NASA-libcurl-CLI

An interactive CLI program that fetches [NASA API's](https://api.nasa.gov/) and outputs them in prettified JSON format (`.json` file and in terminal).

Written in C++ using the [libcurl API](https://curl.se/libcurl/) and [nlohmann json parser](https://github.com/nlohmann/json). My library [TermStylist](https://github.com/alexwkleung/TermStylist) was also used for terminal colours.

WIP.

# Installation 

Clone the repository.

```bash
git clone <SSH/HTTPS URL>
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

Build program

```bash
make build
```

# Options Menu

Typing `apod` will call the function for the Astronomy Picture of the day (APOD) API.

Typing `neo-feed` will call the function for the Asteroids - NeoW Feed (Neo Feed) API.

Typing `donki-sep` will call the function for the DONKI Solar Energetic Particle (SEP) API.

Typing `insight` will call the function for the InSight: Mars Weather Service API.

When you enter an option, some will ask you to enter required fields to specify the API query before it fetches the data string so that nlohmann json can parse it. For the ones that don't, it will go straight to fetching the data string.

Here are the steps that will be executed in order: 

1) Choose an option (apod, neo-feed, donki-sep, insight, etc)

2) Enter the required fields to specifiy the API query if applicable.

3) The JSON string will be fetched by libcurl, nlohmann json will parse that string, and then prettifies the formatting for viewing pleasure. 

4) The output of the prettified JSON will be present in the `json-out` directory, with file containing the naming scheme of `<api name>.json`. The prettified JSON is also outputted to the terminal.
