#include "../include/common.h"
#include "../include/execute.h"
#include "../include/handlers.h"
#include "../include/pipeline.h"
#include "../include/redirection.h"
#include "../include/types.h"

void exec_pipeline(pipeline p) {
    for (int cmd = 0; cmd < p.cmdc; cmd++) {
        command c = p.cmdv[cmd];
        redirect(c.input, c.output, c.append);

        if (c.argc > 0) {
            int handler_id = string_to_handler_id(c.argv[0]);
            if (handler_id < 0) {
                execute(c);
            } else {
                handlers[handler_id](c);
            }
        }

        restore_redirect();
    }
}
