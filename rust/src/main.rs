// This is an exercise for my Computer Science classes: to create a simple command-line application using Rust.
// References:
//      https://people.gnome.org/~federico/blog/writing-a-command-line-program-in-rust.html
//      https://docs.rs/structopt/0.3.17/structopt/

use structopt::StructOpt;
use regex::Regex;
use std::convert::TryInto;


#[derive(StructOpt, Debug)]
#[structopt(name = "Rust Command-line Demo", about = "Command-line demo code for my classes.")]
struct Opt {
    #[structopt(short = "-l",
        long = "-line",
        default_value = "0",
        help = "Display a specific line from file contents if option `-l` is not set.")]
    line_number: u16,
    #[structopt(short = "-c",
        long = "-content",
        help = "Display file contents.")]
    c: bool,
    #[structopt(short = "-w",
        long = "-words",
        help = "Count the number of words in a file.")]
    w: bool,
    #[structopt(help = "Input file to be read.",
        parse(from_os_str))]
    input_file: std::path::PathBuf,
}


fn main() {
    let opt = Opt::from_args();

    let file_content = std::fs::read_to_string(&opt.input_file)
        .expect("Could not read file!");

    println!("\n -> Reading file: '{}'", opt.input_file.into_os_string().into_string().unwrap());
    // println!("{}", file_content);

    if opt.w {
        let re = Regex::new(r"\w*").unwrap();
        // Contador de palavras com tamanho de 32-bits (inteiro sem sinal): é mais que o suficiente para contar todas as palavras
        // de um livro de 10k páginas. Em média, um livro de 400 páginas contem entre 55k e 110k palavras.
        let word_count: u32 = re.find_iter(&file_content).count().try_into().unwrap();
        println!("* Total number of words: {}", word_count);
    }

    if opt.line_number > 0 {
        // Contador do número de linhas com tamanho unsigned int de 16-bits é mais que o suficiente para ler um
        // arquivo de texto com tamanho razoável. Por exemplo, um livro tem em média 25 linhas por página.
        let mut n: u16 = 1;
        for line in file_content.lines() {
            if n == opt.line_number {
                println!("* displaying line ({}): {}", n, line);
                break;
            }
            n = n + 1;
        }
    } else if opt.c {
        println!("* displaying file contents: \n");
        println!("{}", file_content);
    }
    println!("\n");
}