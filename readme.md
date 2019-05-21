# pa3 README questions

## Question 1
Hypothesis: If we were to compress a file before encrypting it, then the
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

