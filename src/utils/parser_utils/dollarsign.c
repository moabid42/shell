#include <stdbool.h>
#include <stdlib.h> 
#include <stdio.h> 

#include <string.h>

bool	is_alphanumeric(char c){
	if('0' <= c && c <= '9' ||
		'a' <= c && c <= 'z' ||
		'A' <= c && c <= 'Z')
		return (true);
	return (false);
}



char *string_dollar_sign(char *tmp)
{
	int		i;
	int		j;
	bool	open;
	char	quotes_type;
	char	*ret_string;
	char	*string = (char *)"$lala$lala";

	i = 0;
	open = false;
	ret_string = malloc(100000);
	ret_string[100000 - 1] = '\0';
	j = 0;
	//printf("%s", string);
	while(string[i]){
		if((string[i] == '\'' || string[i] == '"') && open == false){
			open = true;
			quotes_type = string[i];
		}
		else if(open == true && string[i] == '$'){
			ret_string[j++] = quotes_type;
			ret_string[j++] = '"';
			if(string[i + 1])
				ret_string[j++] = string[i++];
			while(string[i] && is_alphanumeric(string[i]) == true && string[i] != '$'){
				ret_string[j] = string[i];
				i++;
				j++;
			}
			ret_string[j++] = '"';
			ret_string[j++] = quotes_type;
		}
		else if(open == false && string[i] == '$'){
			ret_string[j++] = '"';
			if(string[i + 1])
				ret_string[j++] = string[i++];
			while(string[i] && is_alphanumeric(string[i]) == true && string[i] != '$'){
				ret_string[j] = string[i];
				i++;
				j++;
			}
			ret_string[j++] = '"';
		}
		else if (string[i] == quotes_type && open == true)
			open = false;
		printf("diocane?: %s\n", ret_string);
		if (string[i])
			ret_string[j] = string[i];
		i++;
		j++;
	}
	ret_string[j] = '\0';
	return (ret_string);

}

int main (void){

	printf("%s", string_dollar_sign("example"));
}