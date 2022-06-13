#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

unsigned char otocByte(unsigned char byte)
{
	unsigned char res = 0;
	for (int i = 0; i < 8; i++)
	{
		res <<= 1;
		res += byte % 2;
		byte >>= 1;
	}
	return res;
}

int pocetNulovychBitu(unsigned char* hash)
{
	int res = 0;
	while (*hash == 0)
	{
		res += 8;
		hash++;
	}
	unsigned char otoceno = otocByte(*hash);
	while (otoceno)
	{
		if (otoceno % 2 == 0)
		{
			res++;
			otoceno /= 2;
		}
		else
			break;
	}
	return res;
}

int main (int argc, char * argv[]) {
	if (argc != 2)
	{
		printf("Nespravny pocet argumentu.\n");
		return 1;
	}
	int pozadovanoBitu;
	if (sscanf(argv[1], "%d", &pozadovanoBitu) != 1)
	{
		printf("Argument musi byt cislo.\n");
		return 1;
	}

	char text[] = "Text pro hash.";
	char hashFunction[] = "sha1";  // zvolena hashovaci funkce ("sha1", "md5", ...)

	EVP_MD_CTX * ctx;  // struktura kontextu
	const EVP_MD * type; // typ pouzite hashovaci funkce
	unsigned char hash[EVP_MAX_MD_SIZE]; // char pole pro hash - 64 bytu (max pro sha 512)
	unsigned int length;  // vysledna delka hashe

	/* Inicializace OpenSSL hash funkci */
	OpenSSL_add_all_digests();
	/* Zjisteni, jaka hashovaci funkce ma byt pouzita */
	type = EVP_get_digestbyname(hashFunction);

	/* Pokud predchozi prirazeni vratilo -1, tak nebyla zadana spravne hashovaci funkce */
	if (!type) {
		printf("Hash %s neexistuje.\n", hashFunction);
		return 1;
	}

	ctx = EVP_MD_CTX_new(); // create context for hashing
	if (ctx == NULL)
		return 2;

	/* Hash the text */
	if (!EVP_DigestInit_ex(ctx, type, NULL)) // context setup for our hash type
		return 3;

	long long int i = 0;
	while (true)
	{
		sprintf(text, "%lld", i);
		if (!EVP_DigestUpdate(ctx, text, strlen(text))) // feed the message in
			return 4;

		if (!EVP_DigestFinal_ex(ctx, hash, &length)) // get the hash
			return 5;
		
		if (pocetNulovychBitu(hash) >= pozadovanoBitu)
		{
			/* Vypsani vysledneho hashe */
			printf("Hash textu \"%s\" je: ", text);
			for (unsigned int i = 0; i < length; i++)
				printf("%02x", hash[i]);
			printf("\n");
			break;
		}
		i++;
	}


	EVP_MD_CTX_free(ctx); // destroy the context
	return 0;
}