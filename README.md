# Running kaon analysis with CAFana

## Setup
You will need to be in a container with `setup_sbnd.sh` loaded.
```
bash
. init.sh
```

## Running the analysis
```
bash
cafe -b -q KaonEvents.C
```

## What else
This produces a root file with a TTree in it. It will be stored with whatever you set `const TString saveName` to in the `KaonEvents.C` file.

## What if I want to change something?
The headers in `headers/` contain the definitions of the variables you want to fill. You will need to add

- The variable to save in the relevant `.h` file.
- The variable to save in the in the `KaonEvents.C` file.
- The branch to save in the `TTree` in the `KaonEvents.C` file.
- You will need to push the changes to the TTree in the `KaonEvents.C` file.

