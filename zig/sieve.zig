const std = @import("std");
const m_calculate_upper_limit: u64 = 1_000_000_000;
const m_required_bits: u64 = m_calculate_upper_limit / 2;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    defer _ = gpa.deinit();

    var bits = try std.DynamicBitSet.initFull(allocator, m_required_bits);
    defer bits.deinit();

    var i: u64 = 0;
    while (true) {
        const n: u64 = i * 2 + 3;
        if (n * n >= m_calculate_upper_limit) break;

        if (bits.isSet(i)) {
            var j: u64 = n * n;
            var arrIdx: u64 = (j - 3) / 2;
            while (j < m_calculate_upper_limit) : ({
                j += 2 * n;
                arrIdx += n;
            }) {
                bits.unset(arrIdx);
            }
        }

        i += 1;
    }

    // for (0..m_required_bits) |ix| {
    //     if (bits.isSet(ix)) {
    //         std.debug.print("PRIME {d} \n", .{convertToRegular(ix)});
    //     } else {
    //         std.debug.print("NOT PRIME {d}\n", .{convertToRegular(ix)});
    //     }
    // }
}

fn convertToRegular(num: u64) u64 {
    return num * 2 + 3;
}
