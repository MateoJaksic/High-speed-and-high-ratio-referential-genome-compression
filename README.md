# High-speed and high-ratio referential genome compression

## About the Project

Authors: Karla Budimir and Mateo Jakšić

This project was developed as part of the **[Bioinformatics 1](https://www.fer.unizg.hr/predmet/bio1)** course.  

The main reference for the project is the following scientific article:

> Yuansheng Liu, Hui Peng, Limsoon Wong, Jinyan Li, High-speed and high-ratio referential genome compression, Bioinformatics, Volume 33, Issue 21, November 012017, Pages 3364–3372, 
> [Link to the article](https://academic.oup.com/bioinformatics/article/33/21/3364/3885699?login=true) 

## How to run

1. Clone the repository

```bash
git clone https://github.com/MateoJaksic/High-speed-and-high-ratio-referential-genome-compression.git
cd High-speed-and-high-ratio-referential-genome-compression
```

2. Give execution permissions

```bash
chmod +x run_compress.sh
chmod +x run_decompress.sh
```

3. Run scripts

```bash
./run_compress.sh -r reference_file -t target_file -o output_file
./run_decompress.sh -r reference_file -c compressed_file -o output_file
```

4. Run scripts with real data (using ASM1038v1 target genome)

```bash
./run_compress.sh -r data/reference.fna -t data/target_ASM1038v1.fna -o compress_output.txt
./run_decompress.sh -r data/reference.fna -c compress_output.txt -o decompress_output.txt
```

## License

This project is licensed under the [MIT License](./LICENSE).