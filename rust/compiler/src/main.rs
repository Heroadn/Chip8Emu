use std::collections::HashMap;
use std::iter::FromIterator;
use std::str::Chars;

pub struct scheme {
    pub lookahead: String,
    pub input: Vec<String>,
}

pub struct table {
    pub words: HashMap<String, String>,
}

pub struct Token {
    token_type: TokenType,
    val: Option<String>,
}

impl scheme {
    pub fn expr(&mut self) {
        self.term();
        self.rest();
    }

    pub fn term(&mut self) {
        match self.lookahead.parse::<i32>() {
            Ok(num) => {
                self.lookahead = num.to_string();
                self.check(num.to_string());
                print!("{}", num);
            }
            Err(_e) => print!("Syntax error"),
        }
    }

    pub fn rest(&mut self) {
        match &self.lookahead[..] {
            "+" => {
                self.check(String::from("+"));
                self.term();
                print!("+");
                self.rest()
            }
            "-" => {
                self.check(String::from("-"));
                self.term();
                print!("-");
                self.rest()
            }
            _ => {}
        }
    }

    pub fn check(&mut self, token: String) {
        if token == self.lookahead {
            self.lookahead = self.input.pop().unwrap_or("Syntax error".to_string());
        } else {
            panic!("syntax error");
        }
    }
}

impl table {
    fn reserve(&mut self, keyword: String) {
        self.words.insert(String::from(&keyword), keyword);
    }
}

enum TokenType {
    ID,
    LPARAM,
    RPARAM,
    SEMICOLON,
    PLUS,
    SUB,
    MULT,
    DIV,
    CMP_GREATER,
    CMP_GREATER_EQUAL,
    CMP_LESS,
    CMP_LESS_EQUAL,
    CMP_EQUAL,
    NUM,
    UNKNOW,
}

fn compose_number(chars: &mut Chars) -> u32 {
    let mut num = 0;

    while let Some(ch) = chars.next() {
        //cheking if is a number
        if let Some(number) = ch.to_digit(10) {
            num = (num * 10) + number;
        } else {
            break;
        }
    }

    return num;
}

fn string_to_number(word: String) -> i32 {
    let num: i32;

    for ch in word.chars() {
        if let Some(digit) = ch.to_digit(10) {
            num = (num * 10) + digit;
        } else {
            break;
        }
    }

    return num;
    /*
    while let Some(ch) = chars.next() {
        //cheking if is a number
        if let Some(number) = ch.to_digit(10) {
            num = (num * 10) + number;
        } else {
            break;
        }
    }
    */
}

fn main() {
    /*
    let input = "9 - 5 + 2";
    let mut input = Vec::from_iter(input.split(" ").map(String::from));
    input.reverse();

    let mut s = scheme
    {
        lookahead: input.pop().unwrap_or(String::from("Syntax error")),
        input: input
    };

    s.expr();*/

    let mut tokens: Vec<Token> = Vec::new();
    let mut words: HashMap<String, String> = HashMap::new();
    let mut lexeme: String = String::from("");
    //let input = "count = count + increment;";
    let input = "for(i; a > 123; b);";

    // getting identifiers
    let mut chars = input.chars();
    while let Some(c) = chars.next() {
        /*
        //searching for identifiers
        if c.is_alphabetic() {
            lexeme.push(c);

            while let Some(letter) = chars.next() {
                if !letter.is_alphabetic() {
                    break;
                }
                lexeme.push(letter);
            }
        }

        if !c.is_whitespace() && !lexeme.is_empty() {
            println!("{}", lexeme);
            lexeme.clear();
        }

        */
        //searching not identifiers
        if c.is_alphabetic() {
            let token_type = match c.to_ascii_lowercase() {
                '(' => TokenType::LPARAM,
                ')' => TokenType::RPARAM,
                ';' => TokenType::SEMICOLON,
                '+' => TokenType::PLUS,
                '-' => TokenType::SUB,
                '*' => TokenType::MULT,
                '/' => TokenType::DIV,
                'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm'
                | 'n' | 'o' | 'p' | 'q' | 'r' | 't' | 'u' | 'v' | 'x' | 'y' | 'z' => {
                    let mut identifier: String = String::from("");
                    identifier.push(c);

                    while let Some(ch) = chars.next() {
                        //cheking if is a word
                        if !ch.is_alphabetic() {
                            break;
                        }

                        identifier.push(ch);
                    }

                    println!("{}", identifier);
                    TokenType::ID
                }

                '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' => {
                    let mut number: String = String::from("");
                    number.push(c);

                    while let Some(ch) = chars.next() {
                        //cheking if is a number
                        if !ch.is_digit(10) {
                            break;
                        }

                        number.push(ch);
                    }
 
                    println!("{}", number);
                    println!("{}", string_to_number(identifier));
                    TokenType::NUM
                }
                _ => TokenType::UNKNOW,
            };

            //lexeme.push(token);
        }

        if !lexeme.is_empty() {
            println!("{}", lexeme);
            lexeme.clear();
        }
    }
}
