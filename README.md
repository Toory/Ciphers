# Ciphers
C implementation of the Caesar cipher and the Vigenère cipher

# Caesar Cipher

## Description

The Caesar cipher, also known as a shift cipher, is one of the simplest forms of encryption. It is a substitution cipher where each letter in the original message (called the plaintext) is replaced with a letter corresponding to a certain number of letters up or down in the alphabet.
  
## Installation
  
  Write the text you want to encrypt/decrypt in a text file (in.dat)
  
  	cd ~/caesar-cipher
   	make
    ./caesar <shift> [-e | -d]  [-i] <input_file> [-o] <output_file>
    if the shift value it's not known you can try to decrypt the text by using the BruteForce function, as follows:
    ./caesar <shift> [-b]  [-i] <input_file> [-o] <output_file>

 # Vigenère Cipher
 
 ## Description
 
 The Vigenère cipher is a method of encrypting alphabetic text by using a series of interwoven Caesar ciphers based on the letters of a keyword. It is a form of polyalphabetic substitution.
 
 ## Installation
 
   Write the text you want to encrypt/decrypt in a text file (in.dat)
   
      cd ~/vigenere-cipher
   	  make
      ./vigenere <keyword> [-e | -d]  [-i] <input_file> [-o] <output_file>
   
  
  

  
  
  


