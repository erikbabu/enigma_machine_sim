# Enigma Machine Simulator
Enigma coding machine, simulated in C++.

To run program:

run makefile: type 'make' into terminal


invoke program:
./enigma [rotor_configs]* plugboard_config reflector_config

example invocation:
./enigma rotor_files/enigma_I.rotor rotor_files/enigma_II.rotor plugboard_files/II_pb.plugboard reflector_files/A.ref

Note: Just as with the original enigma machine, the same rotor can not be used more than once per encryption. 

Usage:
After entering the program arguments you will be prompted for rotor notch configurations. These start each rotor at the letter you input. Enter a configuration for each rotor. e.g. if there are 3 rotors, enter something like ABC or XYZ or EBE. If you would like to keep the notch configuration as a default, just enter A for each rotor.

When prompted, type the message you would like to encrypt, followed by ctrl + d. Afterwards, the encrypted message should appear on your terminal (in groups of 5). If you would like to decrypt the message, set up the enigma machine with the same settings you used to encrypt the message, enter the cipher text and the result will be the decrypted message. 

Sample rotor and reflector configurations from real enigma machines have been provided in the reflector_files and rotor_files folders respectively. Feel free to create your own custom rotor/reflector files. Just ensure that every letter is used once and stored in uppercase. If you do not want to use rotors for encryption/decryption, do not include them when invoking the program. Sample plugboard files have been provided. If you would like to create your own, just ensure there are an even number of mappings and no letter is mapped more than once. If you do not want plugboard mappings, invoke the program with empty.plugboard in the plugboard argument location.

Rotor config files source: https://en.wikipedia.org/wiki/Enigma_rotor_details

