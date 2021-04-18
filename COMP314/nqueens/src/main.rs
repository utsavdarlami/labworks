use std::env;
use std::process;

struct Board {
    n : usize,
    board : Vec<Vec<char>>,
}

impl Board {
    fn initialize(n:usize)->Board{
        let mut board:Vec<Vec<char>> = Vec::new();
        for _ in 0..n{
            let mut row:Vec<char> = Vec::new();
            for _ in 0..n{
                row.push('_');
            }
            board.push(row);
        }
        Board{
            n,
            board,
        }
    }

    fn place_n_queens(&mut self,row_pos:usize) -> bool{
        //println!("Find N queens This is a recursive function");
        if row_pos == self.n{
            return true
        }
        for col_pos in 0..self.n{
            if self.is_board_safe(row_pos,col_pos){
                self.board[row_pos][col_pos] = 'q';
                if self.place_n_queens(row_pos+1){
                   return true
                }
                self.board[row_pos][col_pos] = '_';
            }
        }
        false 
    }
    
    fn is_board_safe(&mut self,row_pos:usize,col_pos:usize)->bool{
        for row in 0..self.n{
            for col in 0..self.n{
                if self.board[row][col]=='q'{
                    if row_pos==row && col_pos!=col{
                        return false 
                    }
                    else if row_pos!=row && col_pos==col{
                        return false 
                    }
                    else if row_pos as i32 + col_pos as i32 == row as i32 + col as i32 || 
                            row_pos as i32 - col_pos as i32 == row as i32 - col as i32 {
                        return false 
                    }
                }
            } 
        } 
        true
    }

    fn display_board(&self){
        let board = &self.board;
        for row in 0..self.n{
            for col in 0..self.n{
                print!("{}",board[row][col]);
            }
            println!()
        }
    }
}

fn help(){
    println!("
             Usage: 
                ./nqueens n [default=8] -> n = [4,inf) ,Finding placement for n queens 
    ");
}

fn main() {
    let args:Vec<String> = env::args().collect();

    let mut n_queens:usize=8;

    match args.len(){
        1 => {
            help();
            println!("Selecting default N as {}",n_queens);
            //let n:usize = 8;
            //8
        },
        2 => {
            let num = &args[1];
            n_queens = match num.parse(){
                Ok(n)=>{
                    //let n:usize=user_n;
                    n
                },
                Err(_) => {
                    help();
                    return 
                }
            };
            //let n:usize = number;
            //n_queens = number;
            println!("Selecting N as {}",n_queens);
        },
        _ => {
            eprintln!("\nerror : To many arguments where given");
            help();
            process::exit(1);
        },
    };

    //let n:usize = 8;
    

    let mut new_board = Board::initialize(n_queens);

    new_board.display_board();
    
    let final_state:bool = new_board.place_n_queens(0);
    
    println!("\n...Final Solution ...\n");
    if final_state{
        new_board.display_board();
    }
    else{
        println!("Could not find the solution, check n value");
    }
    println!();
}
