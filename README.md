# **Scheme Tokenizer in C**

This is a tokenizer I created for the Scheme programming language, marking my first significant C project after six months of learning. It's designed to read Scheme code from standard input and output a list of tokens with their corresponding types. I'm excited to share it with the community and welcome collaboration.

## **Core Functionality**

My tokenizer handles a variety of token types, including:

* boolean  
* integer  
* float  
* string  
* symbol  
* open (()  
* close ())

A key feature is its ability to ignore comments, which begin with a semicolon (;). It's also built to handle bad input gracefully, printing an error message and exiting cleanly without crashing.

## **Testing and Use Cases**

You can test the tokenizer by redirecting a file containing Scheme code to standard input.

To compile the project, run:

make

### **Example Usage**

Here is a sample input file (token-test.input.1) and the output my tokenizer produces:

**token-test.input.1**

(+x2 (+ ( quote x ) "foo;; still a string" 323\) now it's a comment\!

**Output:**

(:open  
\+:symbol  
x2:symbol  
(:open  
\+:symbol  
(:open  
quote:symbol  
x:symbol  
):close  
"foo;; still a string":string  
323:integer  
):close

### **Automated Testing**

To see if the output matches a predefined standard, you can use diff. If the command below produces no output, your code is working as expected.

./tokenizer \< tokenizer-test.input.XX | diff \- tokenizer-test.output.XX

### **Memory and Error Checking**

To ensure there are no memory leaks, you can use the provided valgrind.sh script:

./valgrind.sh \< tokenizer-test.input.XX

## **How to Contribute**

I'd be thrilled if you'd like to help me improve this project. Feel free to fork the repository, make changes, and submit a pull request. I'm especially interested in feedback on:

* **Robustness:** How does the tokenizer handle more complex or unusual Scheme syntax?  
* **Error Handling:** Are the error messages clear and helpful?  
* **Efficiency:** Can the code be optimized for better performance?

Any suggestions or contributions are welcome. Thank you for taking the time to review my work\!