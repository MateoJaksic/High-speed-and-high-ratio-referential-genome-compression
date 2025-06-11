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
./run_evaluate.sh -t target_genome -d decompressed_genome -o output_file
```

4. Run scripts with simple data

```bash
./run_compress.sh -r data/simple_reference.fna -t data/simple_target.fna -o outputs/simple_compress_output.txt
./run_decompress.sh -r data/simple_reference.fna -c outputs/simple_compress_output.txt -o outputs/simple_decompress_output.txt
./run_evaluate.sh -t data/simple_target.fna -d outputs/simple_decompress_output.txt -o outputs/simple_evaluate_output.txt
```

5. Run scripts with real data 

5.1. Example using ASM1038v1 target genome

```bash
./run_compress.sh -r data/reference.fna -t data/target_ASM1038v1.fna -o outputs/ASM1038v1_compress_output.txt
./run_decompress.sh -r data/reference.fna -c outputs/ASM1038v1_compress_output.txt -o outputs/ASM1038v1_decompress_output.txt
./run_evaluate.sh -t data/target_ASM1038v1.fna -d outputs/ASM1038v1_decompress_output.txt -o outputs/ASM1038v1_evaluate_output.txt
```

5.2. Example using ASM1326v1 target genome

```bash
./run_compress.sh -r data/reference.fna -t data/target_ASM1326v1.fna -o outputs/ASM1326v1_compress_output.txt
./run_decompress.sh -r data/reference.fna -c outputs/ASM1326v1_compress_output.txt -o outputs/ASM1326v1_decompress_output.txt
./run_evaluate.sh -t data/target_ASM1326v1.fna -d outputs/ASM1326v1_decompress_output.txt -o outputs/ASM1326v1_evaluate_output.txt
```

5.3. Example using ASM21047v1 target genome

```bash
./run_compress.sh -r data/reference.fna -t data/target_ASM21047v1.fna -o outputs/ASM21047v1_compress_output.txt
./run_decompress.sh -r data/reference.fna -c outputs/ASM21047v1_compress_output.txt -o outputs/ASM21047v1_decompress_output.txt
./run_evaluate.sh -t data/target_ASM21047v1.fna -d outputs/ASM21047v1_decompress_output.txt -o outputs/ASM21047v1_evaluate_output.txt
```

5.4. Example using ASM285371v1 target genome

```bash
./run_compress.sh -r data/reference.fna -t data/target_ASM285371v1.fna -o outputs/ASM285371v1_compress_output.txt
./run_decompress.sh -r data/reference.fna -c outputs/ASM285371v1_compress_output.txt -o outputs/ASM285371v1_decompress_output.txt
./run_evaluate.sh -t data/target_ASM285371v1.fna -d outputs/ASM285371v1_decompress_output.txt -o outputs/ASM285371v1_evaluate_output.txt
```

5.5. Example using ASM369716v2 target genome

```bash
./run_compress.sh -r data/reference.fna -t data/target_ASM369716v2.fna -o outputs/ASM369716v2_compress_output.txt
./run_decompress.sh -r data/reference.fna -c outputs/ASM369716v2_compress_output.txt -o outputs/ASM369716v2_decompress_output.txt
./run_evaluate.sh -t data/target_ASM369716v2.fna -d outputs/ASM369716v2_decompress_output.txt -o outputs/ASM369716v2_evaluate_output.txt
```

## License

This project is licensed under the [MIT License](./LICENSE).