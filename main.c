#include "main.h"

ht *init_ht(unsigned long int size)
{
	unsigned long int i = 0;
	ht *new_ht = malloc(sizeof(ht));
	if (new_ht == NULL)
		return (NULL);
	new_ht->size = size;
	new_ht->array = malloc(sizeof(hn) * size);
	if (new_ht->array == NULL)
		return (NULL);
	while (i < size)
	{
		new_ht->array[i] = NULL;
		i++;
	}
	return (new_ht);
}

void print_ht(ht *my_ht)
{
	unsigned long int i = 0;
	hn *my_hn;
	if (my_ht == NULL || my_ht->size == 0)
		return;
	printf("---Start Printing Hash Table (size: %lu)---\n", my_ht->size);

	while (i < my_ht->size)
	{
		printf("%d: ", i);
		if (my_ht->array[i] == NULL)
			printf("---NULL---\n");
		else
		{
			if (my_ht->array[i]->next == NULL)
			{
				printf("%s: %s -> %p\n", my_ht->array[i]->key,
					my_ht->array[i]->value, my_ht->array[i]->next);
			}
			else
			{
				my_hn = my_ht->array[i];
				while (my_hn != NULL)
				{
					printf("\t%s: %s -> %p\n", my_hn->key,
						my_hn->value, my_hn->next);
					my_hn = my_hn->next;
				}
			}
		}
		i++;
	}

	printf("---Finished Printing Hash Table---\n");
}

unsigned long int hash(char *key, unsigned long int size)
{
	unsigned long int i = 0, j = 0;
	for (j = 0; j < strlen(key); j++)
	{
		i += key[j];
	}
	return (i % size);
}

hn *pair_hn(char *key, char *value)
{
	hn *new_hn = malloc(sizeof(hn));
	if (new_hn == NULL)
		return (NULL);
	new_hn->key = key;
	new_hn->value = value;
	new_hn->next = NULL;
	return (new_hn);
}

int set_hn(ht *my_ht, char *key, char *value)
{
	unsigned long int array_index = hash(key, TABLE_SIZE);
	hn *my_hn = my_ht->array[array_index], *prev = NULL;
	if (my_hn == NULL)
	{
		my_hn = pair_hn(key, value);
		if (my_hn == NULL)
			return (0);
		my_ht->array[array_index] = my_hn;
		return (1);
	}
	while (my_hn != NULL)
	{
		// A key is found: Replace value
		if (my_hn->key == key)
		{
			my_hn->value = value;
			return (1);
		}
		prev = my_hn;
		my_hn = my_hn->next;
	}
	my_hn = pair_hn(key, value);
	if (my_hn == NULL)
		return (0);
	prev->next = my_hn;
	return (1);
}

int main(int argc, char const *argv[])
{
	ht *my_ht = init_ht(TABLE_SIZE);
	int set_status = 0;
	print_ht(my_ht);
	printf("\n");
	set_status = set_hn(my_ht, "Avatar", "Aang");
	printf("Set Status: %d\n", set_status);
	set_status = set_hn(my_ht, "Avater", "Korra");
	printf("Set Status: %d\n", set_status);
	set_status = set_hn(my_ht, "Hokage", "Naruto");
	printf("Set Status: %d\n", set_status);
	printf("\n");
	print_ht(my_ht);
	/* code */
	/* printf("Hash: %lu\n", hash("Hash", TABLE_SIZE)); */
	return 0;
}