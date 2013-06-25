#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LCS_MATCH       2
#define LCS_MISMATCH   -1
#define NSEQ            7


void LCS_length(const char *X, const char *Y, int ***c_out, char ***b_out)
{
    int m;          // row
    int n;          // column
    int **c;        // length matrix
    char **b;       // arrow matrix
    int i, j;

    m = strlen(X);
    n = strlen(Y);
    c = malloc((m+1)*sizeof(int *));
    b = malloc((m+1)*sizeof(char *));
    for (i = 0; i <= m; i++) {
        c[i] = calloc(n+1, sizeof(int));
        b[i] = calloc(n+1, sizeof(char));
    }

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + LCS_MATCH;
                b[i][j] = '\\';
            // TODO: smith-waterman
            } else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j] + LCS_MISMATCH;
                b[i][j] = '|';
            } else {
                c[i][j] = c[i][j-1] + LCS_MISMATCH;
                b[i][j] = '_';
            }

            //c[i][j] = abs(c[i][j]);     // no zero value
        }
    }

    *c_out = c;
    *b_out = b;
}

void LCS_print_X(char **b, const char *X, int i, int j)
{
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == '\\') {
        LCS_print_X(b, X, i-1, j-1);
        printf("%c", X[i-1]);
    } else if (b[i][j] == '|') {
        LCS_print_X(b, X, i-1, j);
        printf("%c", X[i-1]);
    } else {
        LCS_print_X(b, X, i, j-1);
        printf("_");

    }
}

void LCS_print_Y(char **b, const char *Y, int i, int j)
{
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == '\\') {
        LCS_print_Y(b, Y, i-1, j-1);
        printf("%c", Y[j-1]);
    } else if (b[i][j] == '|') {
        LCS_print_Y(b, Y, i-1, j);
        printf("_");
    } else {
        LCS_print_Y(b, Y, i, j-1);
        printf("%c", Y[j-1]);
    }
}

void LCS_c_print(int **c, int m, int n)
{
    int i, j;
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++)
            printf("%2d ", c[i][j]);
        printf("\n");
    }
}

void LCS_b_print(const char X[], const char Y[], char **b, int m, int n)
{
    int i, j;
    printf(" ");
    for (i = 1; i <= n; i++)
        printf(" %c", Y[i-1]);
    printf("\n");
    for (i = 1; i <= m; i++) {
        printf("%c", X[i-1]);
        for (j = 1; j <= n; j++) {
            printf(" %c", b[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    const char S[NSEQ][160] = {
        "MVLSAADKTNVKAAWSKVGGHAGEYGAEALERMFLGFPTTKTYFPHFDLSHGSAQVKAHGKKVGDALTLAVGHLDDLPGALSNLSDLHAHKLRVDPVNFKLLSHCLLSTLAVHLPNDFTPAVHASLDKFLSSVSTVLTSKYR",       // HBA_HORSE
        "VQLSGEEKAAVLALWDKVNEEEVGGEALGRLLVVYPWTQRFFDSFGDLSNPGAVMGNPKVKAHGKKVLHSFGEGVHHLDNLKGTFAALSELHCDKLHVDPENFRLLGNVLVVVLARHFGKDFTPELQASYQKVVAGVANALAHKYH",   // HBB_HORSE
        "MVLSPADKTNVKAAWGKVGAHAGEYGAEALERMFLSFPTTKTYFPHFDLSHGSAQVKGHGKKVADALTNAVAHVDDMPNALSALSDLHAHKLRVDPVNFKLLSHCLLVTLAAHLPAEFTPAVHASLDKFLASVSTVLTSKYR",       // HBA_HUMAN
        "MVHLTPEEKSAVTALWGKVNVDEVGGEALGRLLVVYPWTQRFFESFGDLSTPDAVMGNPKVKAHGKKVLGAFSDGLAHLDNLKGTFATLSELHCDKLHVDPENFRLLGNVLVCVLAHHFGKEFTPPVQAAYQKVVAGVANALAHKYH",  // HBB_HUMAN
        "MVLSEGEWQLVLHVWAKVEADVAGHGQDILIRLFKSHPETLEKFDRFKHLKTEAEMKASEDLKKHGVTVLTALGAILKKKGHHEAELKPLAQSHATKHKIPIKYLEFISEAIIHVLHSRHPGDFGADAQGAMNKALELFRKDIAAKYKELGYQG",   // MYG_PHYMC
        "MPIVDTGSVAPLSAAEKTKIRSAWAPVYSTYETSGVDILVKFFTSTPAAQEFFPKFKGLTTADQLKKSADVRWHAERIINAVNDAVASMDDTEKMSMKLRDLSGKHAKSFQVDPQYFKVLAAVIADTVAAGDAGFEKLMSMICILLRSAY",       // GLB5_PETMA
        "MGALTESQAALVKSSWEEFNANIPKHTHRFFILVLEIAPAAKDLFSFLKGTSEVPQNNPELQAHAGKVFKLVYEAAIQLQVTGVVVTDATLKNLGSVHVSKGVADAHFPVVKEAILKTIKEVVGAKWSEELNSAWTIAYDELAIVIKKEMNDAA"    // LGB2_LUPLU
    };
    int **c;
    char **b;
    int m, n;

    int D[NSEQ][NSEQ] = {{0}};

    for (i = 0; i < NSEQ; i++)
        for (j = 0

    m = strlen(S[0]);
    n = strlen(S[1]);



    LCS_length(S[0], S[1], &c, &b);

    // print LCS
    LCS_print_X(b, S[0], m, n); printf("\n");
    LCS_print_Y(b, S[1], m, n); printf("\n");
    printf("Score: %d\n", c[m][n]);

    //LCS_c_print(c, m, n); printf("\n");
    //LCS_b_print(X, Y, b, m, n); printf("\n");

    return 0;
}


