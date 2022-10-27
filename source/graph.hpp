/**
 * \file
 * \brief Graphical dump module header
*/


/**
 * \brief Generated text file for dot
 * \param [in]  list Allocated verified list
 * \param [out] file File for output (must be in write mode)
 * \return Non zero value means error
*/
int generate_file(List *list, FILE *file);


/**
 * \brief Generates graph image using system call
 * \param [in]  input Path to file with text for dot
 * \param [out] output Path for created image
 * \return Non zero value means error
*/
int generate_image(const char *input, const char *output);


/**
 * \brief Opens selected file viewer using system call
 * \param [in] filepath Command "start (filepath)" will be called
 * \return Non zero value means error
*/
int show_image(const char *filepath);
