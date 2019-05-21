# pa3 README questions

## Question 1
__Hypothesis:__ If we were to compress a file before encrypting it, then the
            resulting file would most likely be of a smaller size than the file
            resulting from encryption followed by compression. This is because
            we are using an encryption method that attempts to suppress the
            existence of patterns/character frequencies. Most compression
            algorithms rely on patterns in the data to compress but if the
            encryption hid any patterns, the compression will most likely fail
            to shrink the file much at all.

## Question 2
__compression BEFORE encryption file size:__ 1.870872 MB  
__compression AFTER  encryption file size:__ 3.289314 MB

These results __do__ agree with my initial hypothesis

## Question 3
If we XOR encrypted a file and then compressed it, the resulting file size would
be less than the file resulting from GPG encryption followed by compression
because XOR encryption does not try to supress the existence of patterns in the
file contents, unlike GPG encryption.

## Question 4
It would compress the same as the original because the frequencies of the
unencrypted bytes and their corresponding encrypted bytes will be the same,
since each equivalent unencrypted byte will have the same resulting byte from
encryption.

## Question 5
The shannon entropy would be the same as the original unencrypted file for the
same reason as question 4, the frequency of each encrypted byte will be the same
as the frequency of each of their corresponding unencrypted bytes, so the
calculation of entropy for the encrypted file and the unencrypted file stay the
same.
